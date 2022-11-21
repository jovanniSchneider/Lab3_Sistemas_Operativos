#include <unistd.h>
#include "functions.c"
#include <stdio.h>
#include "hash.c"
#include <pthread.h>


//Se declara el archivo de entrada de  manera global
FILE * archivoEntrada;
//Mutex global para dar acceso exclusivo al archivo
pthread_mutex_t mutex;
//Se declara la estructura global donde trabajaran las hebras
year ** tablaHash;
//Se declara de manera global el anio minimo para buscar
int min_year;
float min_price;


void * procesar(void * arg){
    int * xunk = (int *) arg;
    printf(" ");
    int lineas;
    game * lineasLeidas = (game*)malloc(sizeof(game)*(*xunk));
    for (int i = 0; i < *xunk; ++i) {
        game juego;
        lineasLeidas[i] = juego;
    }
    lineas = 1;
    while (lineas > 0)
    {
        pthread_mutex_lock(&mutex);
        lineas = leerCSV(archivoEntrada, *xunk, lineasLeidas);
        pthread_mutex_unlock(&mutex);
        //trabajar lineas chunk
        for (int i = 0; i < lineas; ++i) {
            int pos = hashFunction(lineasLeidas[i].year,min_year);
            if((lineasLeidas[i].price>=min_price)&&(lineasLeidas[i].year>=min_year)){
                if(tablaHash[pos]->access){//access 1
                    if(tablaHash[pos]->priceEx<lineasLeidas[i].price){//reviso caro
                        setMoreExpensive(tablaHash[pos],lineasLeidas[i].name,lineasLeidas[i].price);
                    }
                    if(tablaHash[pos]->priceCh>lineasLeidas[i].price){//revisar barato
                        setCheaper(tablaHash[pos],lineasLeidas[i].name,lineasLeidas[i].price);
                    }
                    setOthers(tablaHash[pos],lineasLeidas[i].win,lineasLeidas[i].mac,lineasLeidas[i].lix,lineasLeidas[i].price);
                }else{ //access 0
                    setAll(tablaHash[pos],&lineasLeidas[i]);
                }
            }
            if((lineasLeidas[i].price==0)&&(lineasLeidas[i].free==1)){//reviso si es gratis
                addFree(tablaHash[pos],lineasLeidas[i].name);
            }
        }
    }

}

int main(int argc, char * argv[]) {
    char input[30] = "datos_juegos_1000.csv";
    char output[30] = "output.txt";
    int flag = 0;
    int threads;
    int c;
    pthread_t * hebras;
    //Se valida utilizando getopt
    if(validate(argc,argv,input,output,&min_year,&flag,&threads,&min_price,&c)){
        //Se abre el archivo de entrada antes de crear cada hebra
        archivoEntrada = fopen(input,"r");
        //Se inicializa la tabla hash
        tablaHash = crearHash(min_year);
        //Se crea cada hebra
        hebras = (pthread_t *) malloc(sizeof(pthread_t)*threads);
        pthread_mutex_init(&mutex,NULL);
        for (int i = 0; i < threads; ++i) {
            pthread_create(&hebras[i],NULL,procesar,(void *) &c);
        }
        for (int i = 0; i < threads; ++i) {
            pthread_join(hebras[i],NULL);
        }
        //aqui la tabla deberia estar lista
        //se revisa si la flag de printear por pantalla esta activa
        if(flag){
            //se printea el archivo
            char string[1000];
            for (int i = 0; i < getSize(min_year); ++i) {
                yearToString(tablaHash[i],string);
                printf("%s\n", string);
            }
            return 0;
        }
            //no se printea
        //Se cierra el archivo de entrada al finalizar de procesar
        return 0;
    }
    return -1;
}