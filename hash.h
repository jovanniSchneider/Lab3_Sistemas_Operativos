//
// Created by jovanni on 21-11-22.
//

#ifndef LAB3_HASH_H
#define LAB3_HASH_H

#endif //LAB3_HASH_H

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

//Entradas: void
//Salidas: Un entero que representa el year actual del SO
//Descripcion: Cmediante funciones de time.h obtiene el year
int getActualYear();

//Entradas: Un entero que representa el año del game
//Salidas: Un entero correspondiente a la casilla de la tabla hash
//Descripcion: Calcula la casilla de la tabla
int hashFunction(int number, int min_year);

//Entradas: void
//Salidas: Un arreglo de listas enlazadas que corresponde a la tabla hash
//Descripcion: genera una tabla hash
year ** crearHash(int min_year);

