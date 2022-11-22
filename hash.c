#include "year.c"
#include <time.h>

//Entradas: void
//Salidas: Un entero que representa el year actual del SO
//Descripcion: Cmediante funciones de time.h obtiene el year
int getActualYear(){
    time_t t;
    struct tm *tm;
    char y[100];
    int year;
    t=time(NULL);
    tm=localtime(&t);
    strftime(y, 100, "%Y", tm);
    year = atoi(y);
    return year;
}

//Entradas: Un entero que representa el año del game
//Salidas: Un entero correspondiente a la casilla de la tabla hash
//Descripcion: Calcula la casilla de la tabla
int hashFunction(int number, int min_year){
    return number - min_year;
}
//Entradas: void
//Salidas: Un arreglo de listas enlazadas que corresponde a la tabla hash
//Descripcion: genera una tabla hash
year ** crearHash(int min_year){
    int anio = getActualYear();
    year ** M=(year**)malloc(sizeof(year*)*(anio-min_year+5));
    for (int i = 0; i < anio-min_year+5; ++i) {
        M[i] = (year*)malloc(sizeof(year));
        M[i]->access=0;
        M[i]->totalGamesYear=0;
        M[i]->mac = 0;
        M[i]->win = 0;
        M[i]->lix = 0;
        M[i]->acum = 0;
        strcpy(M[i]->free,"");
        pthread_mutex_init(&M[i]->mutex,NULL);
        pthread_mutex_init(&M[i]->mutexSetAll,NULL);
    }
    return M;
}

//Entradas

int getSize(int min_year){
    int anio = getActualYear();
    int size = anio-min_year+5;
    return size;
}