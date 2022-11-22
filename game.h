//
// Created by jovanni on 21-11-22.
//
#include <stdio.h>

#ifndef LAB3_GAME_H
#define LAB3_GAME_H

#endif //LAB3_GAME_H

typedef struct game{
    int ID;
    char name[100];
    int ageRest;
    float price;
    int comSoon;
    int year;
    int free;
    int win;
    int mac;
    int lix;
}game;

void game_toString(game * juego);

//Entradas Char * que representa la linea leida de un juego
//Salidas un struct de tipo game
//Descripcion convierte un string a su correspondiente en game
game stringToGame(char string[500]);


//Entradas Char* del nombre del archivo, int del year minimo, int precio minimo, pipes, int de cant de workers
//Salidas TdaLista ** que trabaja como una tabla hash
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este csv se almacena en una tabla hash segun
//            el year del juego en cuestion
int leerCSV(FILE * fp,int chunks,game lineasLeidas[]);