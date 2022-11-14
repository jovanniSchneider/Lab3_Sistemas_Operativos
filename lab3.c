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

void * procesar(void * arg){
    int * chunks = (int *) arg;
    printf("tengo que leer :%d chunks\n",*chunks);
    int lineas;
    char ** lineasLeidas = (char**) malloc(sizeof ((char*)malloc(sizeof (char)*150))* (*chunks));
    for (int i = 0; i <= *chunks; ++i) {
        lineasLeidas[i] = (char*)malloc(sizeof (char)*150);
    }
    pthread_mutex_lock(&mutex);
    lineas = leerCSV(archivoEntrada,*chunks,lineasLeidas);
    pthread_mutex_unlock(&mutex);
    for (int i = 0; i < lineas; ++i) {
        printf("i = %d\nlinea: %s\n",i,lineasLeidas[i]);
    }
}

int main(int argc, char * argv[]) {
    char input[30] = "datos_juegos_1000.csv";
    char output[30] = "output.txt";
    int flag = 0;
    int threads;
    int chunks;
    float min_price;
    pthread_t * hebras;
    //Se valida utilizando getopt
    if(validate(argc,argv,input,output,&min_year,&flag,&threads,&min_price,&chunks)){
        //Se abre el archivo de entrada antes de crear cada hebra
        archivoEntrada = fopen(input,"r");
        //Se inicializa la tabla hash
        //tablaHash = crearHash(min_year);
        //Se crea cada hebra
        hebras = (pthread_t *) malloc(sizeof(pthread_t)*threads);
        pthread_mutex_init(&mutex,NULL);
        for (int i = 0; i < threads; ++i) {
            pthread_create(&hebras[i],NULL,procesar,(void *) &chunks);
            pthread_join(hebras[i],NULL);
        }
        //Se cierra el archivo de entrada al finalizar de procesar
        //fclose(archivoEntrada);
        return 0;
    }
    return -1;
}