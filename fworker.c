//
// Created by jovan on 9/13/2022.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>//para armar la entrega
#include "hash.c"

// Entradas: char* (que representa un juego) x int
// Salidas: char*
// Descripción: realiza strtok una cantida N de veces para obtener un dato del juego
char * getGenerico(char string[250], int posicion){
    char string2[250];
    strcpy(string2,string);
    char separacion[2] = ",";
    char * pedacito;
    pedacito = strtok(string2,separacion);//980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    for (int i = 0; i<posicion;i++){
        pedacito = strtok(NULL,separacion);
    }
    return pedacito;
}

// Entradas: char*
// Salidas: int
// Descripción: transforma un char* a bool(int 0 o 1)
int convertirBool(char string[10]) {
    //True,False,Yes,No
    if((strcmp(string,"True")==0)||(strcmp(string,"Yes")==0)||(strcmp(string,"Yes\n")==0)){
        return 1;
    }if((strcmp(string,"False")==0)||(strcmp(string,"No")==0)||(strcmp(string,"No\n")==0)){
        return 0;
    }
    return -1;
}

// Entradas: hash, string, anio minimo
// Salidas: void
// Descripción: trabaja un char* del tipo juego, para agregarlo a la tabla hash en la posicion correspondiente
void trabajarLinea(year ** tabla, char linea[250], int min_year){
    //980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    //ID=0, Nombre=1, Rest=2, Price=3, year=5, Free=6, Win=7, Mac=8, Linux = 9
    int year = atoi(getGenerico(linea,5));
    //printf("%s\nproceso %d year %d\n",linea,getpid(),year);
    int position = hashFunction(year,min_year);
    char string[250];
    if(tabla[position]->access != 1) {
        tabla[position]->access = 1;
        tabla[position]->year = year;
        strcpy(string, getGenerico(linea, 1));
        strcat(string, "*");
        strcat(string, getGenerico(linea, 3));
        strcpy(tabla[position]->moreExpensive, string);
        strcpy(tabla[position]->cheaper, string);
        tabla[position]->priceEx = atof(getGenerico(linea, 3));
        tabla[position]->priceCh = tabla[position]->priceEx;
    }else{
        //printf("voy\n");
        //Se guarda nombre y precio en un string
        strcpy(string, getGenerico(linea,1));
        strcat(string,"*");
        strcat(string, getGenerico(linea,3));
        //Ve si el juego es mas caro
        if(tabla[position]->priceEx < atof(getGenerico(linea,3))){
            strcpy(tabla[position]->moreExpensive,string);
            tabla[position]->priceEx = atof(getGenerico(linea,3));

        }//Ve si es el juego es mas barato
        else if(tabla[position]->priceCh > atof(getGenerico(linea,3))){
            strcpy(tabla[position]->cheaper,string);
            tabla[position]->priceCh = atof(getGenerico(linea,3));
        }
        //year nombrecaro preciocaro nombrebarato preciobarato gratis1,gratis2....,gratisN windows mac linux gamesYear
        // 1      2           3          4              5              6                    7       8    9       10
    }
    //aumenta la cantidad de juegos procesados
    tabla[position]->totalGamesYear=tabla[position]->totalGamesYear+1;
    tabla[position]->acum+= atof(getGenerico(linea,3));
    //Verifica si esta para windows
    if(convertirBool(getGenerico(linea,7))){
        tabla[position]->win ++;
    }
    //Verifica si esta para mac
    if(convertirBool(getGenerico(linea,8))){
        tabla[position]->mac ++;
    }
    //Verifica si esta para linux
    if(convertirBool(getGenerico(linea,9))){
        tabla[position]->lix ++;
    }
    //Verifica si esta gratis
    if(convertirBool(getGenerico(linea,6))){
        if(strcmp(tabla[position]->free,"")!=0){
            strcat(tabla[position]->free, "\n");
        }
        strcat(tabla[position]->free, getGenerico(linea,1));
    }
//    //printf("%d %d %s\n",getpid(), year,tabla[position]->moreExpensive);
}

//Entradas year, string
//Salida void
//Descripcion convierte una estructura year en un string entendible
void toString(year * anio,char string[1000]){
    char string2[13];
    strcpy(string,"");
    if(anio->access!=0){
        sprintf(string,"%d", anio->year);
        strcat(string,"*");
        strcat(string,anio->moreExpensive);
        strcat(string,"*");
        strcat(string, anio->cheaper);
        strcat(string, "*");
        if(strcmp(anio->free,"")==0)
            strcat(string,"@");
        strcat(string, anio->free);
        strcat(string, "*");
        gcvt(anio->win,5,string2);
        strcat(string,string2);
        strcat(string, "*");
        gcvt(anio->mac,5,string2);
        strcat(string,string2);
        strcat(string, "*");
        gcvt(anio->lix,5,string2);
        strcat(string,string2);
        strcat(string, "*");
        sprintf(string2,"%d", anio->totalGamesYear);
        strcat(string, string2);
        strcat(string, "*");
        gcvt(anio->acum,5,string2);
        strcat(string, string2);
    }else
        strcat(string,"ND");
}