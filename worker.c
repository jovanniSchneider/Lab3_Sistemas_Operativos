//
// Created by bull on 19-10-22.
//
//main que usa al fworker
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fworker.c"

int main(int argc, char * argv[]){
    char buffer[250];
    char out[1000];
    int lineas = 0;
    int min_year = atoi(argv[1]);
    int flag = atoi(argv[2]);
    year ** tabla = crearHash(min_year);
    read(STDIN_FILENO,buffer, sizeof(char)*150);
    while (strcmp(buffer,"FIN")!=0) {
        fflush(stdout);
        fflush(stdin);
        if(strcmp(buffer,"")!=0){
            trabajarLinea(tabla,buffer,min_year);
            lineas++;
        }
        read(STDIN_FILENO,buffer, sizeof(char)*150);
    }
    for (int i = 0; i < getSize(min_year); ++i) {
        toString(tabla[i],out);
        if(strcmp(out,"ND")!=0) {
            write(121, out, sizeof(out));
        }
    }
    strcpy(out,"FIN2");
    write(121,out, sizeof(out));
    if(flag)
        printf("\nProceso %d = %d Lineas procesadas\n",getpid(),lineas);
    return 0;
}