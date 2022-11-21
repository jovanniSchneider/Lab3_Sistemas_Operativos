#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "game.c"

typedef struct year{
    int access;
    int year;
    char moreExpensive[100];
    float priceEx;
    char cheaper[100];
    float  priceCh;
    char free[1500];
    int totalGamesYear;
    float win;
    float mac;
    float lix;
    float acum;
    pthread_mutex_t mutex;
    pthread_mutex_t mutexSetAll;
}year;

void setAccess(year * anio){
    pthread_mutex_lock(&anio->mutex);
    anio->access = 1;
    pthread_mutex_unlock(&anio->mutex);
}

void setYear(year * anio, int yearEntry){
    pthread_mutex_lock(&anio->mutex);
    anio->year = yearEntry;
    pthread_mutex_unlock(&anio->mutex);
}

void setMoreExpensive(year * anio,char * name, float price){
    pthread_mutex_lock(&anio->mutex);
    strcpy(anio->moreExpensive,name);
    anio->priceEx = price;
    pthread_mutex_unlock(&anio->mutex);
}
void setCheaper(year * anio,char * name, float price){
    pthread_mutex_lock(&anio->mutex);
    strcpy(anio->cheaper,name);
    anio->priceCh = price;
    pthread_mutex_unlock(&anio->mutex);
}

void addFree(year * anio, char * name){
    pthread_mutex_lock(&anio->mutex);
    if(strcmp(anio->free,"")!=0){
        strcat(anio->free, "\n");
    }
    strcat(anio->free, name);
    pthread_mutex_unlock(&anio->mutex);
}
void setOthers(year * anio, float win, float mac, float lix, float precio ){
    pthread_mutex_lock(&anio->mutex);
    anio->totalGamesYear++;
    anio->win+= win;
    anio->mac+= mac;
    anio->lix+= lix;
    anio->acum+= precio;
    pthread_mutex_unlock(&anio->mutex);
}

void setAll(year * anio, game * juego){
    pthread_mutex_lock(&anio->mutexSetAll);
    setAccess(anio);
    setYear(anio,juego->year);
    setMoreExpensive(anio,juego->name,juego->price);
    setCheaper(anio,juego->name,juego->price);
    setOthers(anio,juego->win,juego->mac,juego->lix,juego->price);
    pthread_mutex_unlock(&anio->mutexSetAll);
}

//Entradas year, string
//Salida void
//Descripcion convierte una estructura year en un string entendible
void yearToString(year * anio,char string[1000]){
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