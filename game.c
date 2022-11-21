#include <string.h>
#include <stdio.h>

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

void game_toString(game * juego){
    char string[300];
    char aux[50];
    sprintf(string,"%d",juego->ID);
    strcat(string,",");
    strcat(string,juego->name);
    strcat(string,",");
    sprintf(aux,"%d",juego->ageRest);
    strcat(string,aux);
    strcat(string,",");
    sprintf(aux,"%f",juego->price);
    strcat(string,aux);
    strcat(string,",");
    sprintf(aux,"%d",juego->comSoon);
    strcat(string,aux);
    strcat(string,",");
    sprintf(aux,"%d",juego->year);
    strcat(string,aux);
    strcat(string,",");
    sprintf(aux,"%d",juego->free);
    strcat(string,aux);
    strcat(string,",");
    sprintf(aux,"%d",juego->win);
    strcat(string,aux);
    strcat(string,",");
    sprintf(aux,"%d",juego->mac);
    strcat(string,aux);
    strcat(string,",");
    sprintf(aux,"%d",juego->lix);
    strcat(string,aux);
    //printf("%s\n",string);
}

//Entradas Char * que representa la linea leida de un juego
//Salidas un struct de tipo game
//Descripcion convierte un string a su correspondiente en game
game stringToGame(char string[500]){
    game juego;
    char aux[300];
    //980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    //ID=0, Nombre=1, Rest=2, Price=3, year=5, Free=6, Win=7, Mac=8, Linux = 9
    strcpy(aux,getGenerico(string,0));
    juego.ID = atoi(aux);
    strcpy(juego.name, getGenerico(string,1));
    strcpy(aux,getGenerico(string,2));
    juego.ageRest = atoi(aux);
    strcpy(aux,getGenerico(string,3));
    juego.price = atof(aux);
    strcpy(aux,getGenerico(string,5));
    juego.year = atoi(aux);
    strcpy(aux,getGenerico(string,6));
    juego.free = convertirBool(aux);
    strcpy(aux,getGenerico(string,7));
    juego.win = convertirBool(aux);
    strcpy(aux,getGenerico(string,8));
    juego.mac = convertirBool(aux);
    strcpy(aux,getGenerico(string,9));
    juego.lix = convertirBool(aux);
    return juego;
}

//Entradas Char* del nombre del archivo, int del year minimo, int precio minimo, pipes, int de cant de workers
//Salidas TdaLista ** que trabaja como una tabla hash
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este csv se almacena en una tabla hash segun
//            el year del juego en cuestion
int leerCSV(FILE * fp,int chunks,game lineasLeidas[]){
    char string[500];
    int lineas = 0;
    while(fgets(string,500,fp)!=NULL && lineas < chunks){
        lineasLeidas[lineas] = stringToGame(string);
        lineas++;
    }
    return lineas;
}