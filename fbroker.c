#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.c"
//LEER CSV LINEA X LINEA
//GENERAR WORKERS


//Entradas: entero que representa el numero maximo a generar
//Salida: Un entero
//Descripcion: Entrega un numero aleatorio entre 0 y el numero ingresado

int myRandom(int n){
    return rand() % n;
}

//Entradas: string
//Salidas: float
//Descripcion: separa un string hasta obtener el dato que representa el precio
float getPrice(char * string){
    char string2[150];
    strcpy(string2,string);
    char separacion[2] = ",";
    char * pedacito;
    float price;
    pedacito = strtok(string2,separacion);//980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    for (int i = 0; i<3;i++){
        pedacito = strtok(NULL,separacion);
    }
    price = atof(pedacito);
    return price;
}


// Entradas: char* (que es la salida de un worker) x int
// Salidas: char*
// Descripción: realiza strtok una cantida N de veces para obtener un dato de la salida
char * getGenerico(char * string, int posicion){
    //year nombrecaro preciocaro nombrebarato preciobarato gratis1,gratis2....,gratisN windows mac linux gamesYear acum
    // 0      1           2          3              4              5                    6      7     8     9        10
    char string2[250];
    strcpy(string2,string);
    char separacion[2] = "*";
    char * pedacito;
    pedacito = strtok(string2,separacion);
    for (int i = 0; i<posicion;i++){
        pedacito = strtok(NULL,separacion);
    }
    return pedacito;
}
//Entradas hash, pipes, int cantidad de workers, int min year
//Salida void
//Descripcion lee los N pipes, almacenando los resultados en la hash entregada.
void recolectarDatos(year ** tabla, int fd[][2],int workers, int min_year){
    //year nombrecaro preciocaro nombrebarato preciobarato gratis1,gratis2....,gratisN windows mac linux gamesYear acum
    // 0      1           2          3              4              5                    6      7   8    9           10
    int cantFin2=0;
    int i;
    char string[1000];
    int yearActual;
    int posicion;
    float priceEX;//precio caro
    float priceCH;//precio barato
    float w,m,l,ac;
    int gy;
    int lectura;
    int ciclo=0;
    int * flag = (int*)malloc(sizeof(int)*workers);
    for(i=0;i<workers;i++){
        flag[i]=0;
    }
    while(cantFin2!=workers){
        for(i=0;i<workers;i++){
            if(flag[i]){
                continue;
            }else{
                lectura = read(fd[i][0], string, sizeof(string));
                if ((strcmp(string, "FIN2") != 0) && (lectura != 0) && (strcmp(string, "ND") != 0)) {
                    //obtengo el year y la posicion correspondiente
                    yearActual = atoi(getGenerico(string, 0));
                    posicion = hashFunction(yearActual, min_year);

                    //obtengo los precios del mas barato y mas caro
                    priceEX = atof(getGenerico(string, 2));
                    priceCH = atof(getGenerico(string, 4));

                    if (tabla[posicion]->access == 0) {//si no habia entrado en esta posicion relleno con estos datos
                        tabla[posicion]->access =1;
                        tabla[posicion]->year = yearActual;
                        tabla[posicion]->priceEx = priceEX;
                        tabla[posicion]->priceCh = priceEX;
                    }

                    //obtengo la cantidad de juegos por cada SO y la cantidad de juegos procesador en el year
                    w = atof(getGenerico(string, 6));
                    m = atof(getGenerico(string, 7));
                    l = atof(getGenerico(string, 8));
                    gy = atoi(getGenerico(string, 9));
                    ac = atof(getGenerico(string, 10));
                    //ahora modificamos los datos almacenados en la tabla para este year
                    //si tengo un juego mas caro que el anterior
                    if (tabla[posicion]->priceEx <= priceEX) {
                        //reemplazo el nombre
                        strcpy(tabla[posicion]->moreExpensive, getGenerico(string, 1));
                        //reemplazo el precio
                        tabla[posicion]->priceEx = priceEX;
                    }
                    //si tengo un juego mas barato que el anterior
                    if (tabla[posicion]->priceCh >= priceCH) {
                        //reemplazo el nombre
                        strcpy(tabla[posicion]->cheaper, getGenerico(string, 3));
                        //reemplazo el precio
                        tabla[posicion]->priceCh = priceCH;
                    }
                    //agrego la nueva lista de gratis
                    if (strcmp(getGenerico(string, 5), "@") != 0) {//hay juegos que agregar
                        if(strcmp(tabla[posicion]->free,"")!=0){
                            strcat(tabla[posicion]->free,"\n");
                        }
                        strcat(tabla[posicion]->free, getGenerico(string, 5));
                    }
                    //aumento la cantidad de juegos por cada SO y por el year
                    tabla[posicion]->lix = tabla[posicion]->lix + l;
                    tabla[posicion]->win = tabla[posicion]->win + w;
                    tabla[posicion]->mac = tabla[posicion]->mac + m;
                    tabla[posicion]->totalGamesYear = tabla[posicion]->totalGamesYear + gy;
                    tabla[posicion]->acum=tabla[posicion]->acum + ac;
                } else {
                    if (strcmp(string, "FIN2") == 0) {
                        flag[i]=1;
                        cantFin2++;
                    }
                }
            }
        }
        ciclo++;

    }
}
//Entradas year, string
//Salida void
//Descripcion convierte una estructura year en un string entendible
void toString(year* anio,char string[1500]){
    char string2[13];
    strcpy(string,"");
    sprintf(string,"Año %d", anio->year);
    strcat(string,":\nJuego mas caro: ");
    strcat(string,anio->moreExpensive);
    strcat(string," ");
    gcvt(anio->priceEx,5,string2);
    strcat(string,string2);
    strcat(string,"\nJuego mas barato: ");
    strcat(string, anio->cheaper);
    strcat(string," ");
    gcvt(anio->priceCh,5,string2);
    strcat(string,string2);
    strcat(string, "\nPromedio de precios: ");
    gcvt(anio->acum,7,string2);
    strcat(string,string2);
    strcat(string,"\nWindows: ");
    gcvt(anio->win,7,string2);
    strcat(string,string2);
    strcat(string,"% Mac: ");
    gcvt(anio->mac,7,string2);
    strcat(string,string2);
    strcat(string,"% Linux: ");
    gcvt(anio->lix,7,string2);
    strcat(string,string2);
    strcat(string,"%\nJuegos gratis:\n");
    strcat(string,anio->free);

}
//Entradas hash, anio minimo, nombreSalida y flag
//Salidas void
//Descripcion Crea el archivo de salida y le agrega los datos correspondientes
void crearSalida(year** tabla,int min_year, char output[30], int flag){
    int len= getSize(min_year);
    int i;
    char string[1500];
    float totalGames;
    FILE * fp = fopen(output,"w");//salida
    for(i=0;i<len;i++){//actualizamos los datos a su forma porcentual
        if(tabla[i]->access==0){
            continue;
        }

        totalGames=tabla[i]->totalGamesYear;

        tabla[i]->win=((tabla[i]->win)/totalGames)*100;
        tabla[i]->lix=((tabla[i]->lix)/totalGames)*100;
        tabla[i]->mac=((tabla[i]->mac)/totalGames)*100;
        tabla[i]->acum=(tabla[i]->acum)/totalGames;
       // printf("total juegos en año %f %d\nw %f l%f m%f\n",totalGames,tabla[i]->year,tabla[i]->win,tabla[i]->lix,tabla[i]->mac);

        toString(tabla[i],string);
        fprintf(fp,"%s",string);
        if(flag)
            printf("%s",string);
    }
    fclose(fp);
}