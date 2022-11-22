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

//Entrada  TDA Year
//Salida  void
//Descripcion  aumenta en uno la variable totalgamesyear
void countGame(year * anio){
    pthread_mutex_lock(&anio->mutex);
    anio->totalGamesYear++;
    pthread_mutex_unlock(&anio->mutex);
}


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
void toString(year* anio,char string[1500]){
    char string2[40];
    strcpy(string,"");
    sprintf(string,"Año %d", anio->year);
    sprintf(string2,"\nCantidad total de juegos: %d",anio->totalGamesYear);
    strcat(string,string2);
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
    anio->acum= anio->acum/anio->totalGamesYear;
    gcvt(anio->acum,7,string2);
    strcat(string,string2);
    strcat(string,"\nWindows: ");
    anio->win= (anio->win/anio->totalGamesYear)*100;
    gcvt(anio->win,7,string2);
    strcat(string,string2);
    strcat(string,"% Mac: ");
    anio->mac= (anio->mac/anio->totalGamesYear)*100;
    gcvt(anio->mac,7,string2);
    strcat(string,string2);
    strcat(string,"% Linux: ");
    anio->lix= (anio->lix/anio->totalGamesYear)*100;
    gcvt(anio->lix,7,string2);
    strcat(string,string2);
    if(strcmp(anio->free,"")==0){
        strcat(string,"%\nNo se encontraron juegos gratis\n");
    }else{
        strcat(string,"%\nJuegos gratis:\n");
        strcat(string,anio->free);
        strcat(string,"\n");
    }
}