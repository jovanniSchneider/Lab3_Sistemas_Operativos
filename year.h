//
// Created by jovanni on 21-11-22.
//

#ifndef LAB3_YEAR_H
#define LAB3_YEAR_H

#endif //LAB3_YEAR_H

#include <pthread.h>
#include "game.h"
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
void countGame(year * anio);


//Entrada  TDA Year
//Salida  void
//Descripcion  activa la flag access
void setAccess(year * anio);


//Entrada  TDA Year x int
//Salida  void
//Descripcion  cambia el valor de la variable year
void setYear(year * anio, int yearEntry);


//Entrada  TDA Year x string x float
//Salida  void
//Descripcion  setea la informacion respecto al juego mas caro
void setMoreExpensive(year * anio,char * name, float price);


//Entrada  TDA Year x string x float
//Salida  void
//Descripcion  setea la informacion respecto al juego mas barato
void setCheaper(year * anio,char * name, float price);


//Entrada  TDA Year x string
//Salida  void
//Descripcion  concatena el string de entrada en la variable que representan los juegos gratis
void addFree(year * anio, char * name);


//Entrada  TDA Year x float x float x float x float
//Salida  void
//Descripcion  aumenta en 1 o 0 los juegos segun SO y aumenta el precio acumulado
void setOthers(year * anio, float win, float mac, float lix, float precio );


//Entrada  TDA Year x TDA game
//Salida  void
//Descripcion  setea todos los datos en el anio con el juego de entrada
void setAll(year * anio, game * juego);


//Entradas year, string
//Salida void
//Descripcion convierte una estructura year en un string entendible
void toString(year* anio,char string[1500]);