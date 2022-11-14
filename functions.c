#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>


// Entradas: entra un char*
// Salidas: un int 0 o 1
// Descripción: verifica que el string de entrada este conformado solo por digitos
int digitValidate(char * string) {
    for (int i = 0; i < strlen(string); ++i) {
        if (!isdigit(string[i])) {
            if ('.' == string[i]) {
                continue;
            } else
                return 0;
        }
    }
    return 1;
}


// Entradas: parametros ingresados por consola los cuales podrian variar segun la entrada del usuario
// Salidas: int 0 o 1
// Descripción: verifica los parametros ingresados por consola para corroborar que cumplan ciertos parametros para el
// correcto funcionamiento del codigo.
int validate(int argc, char * argv[], char input[], char output[], int * min_year, int * flag, int * threads,
             float * min_price, int * chunks){
    int opt;
    while((opt = getopt(argc,argv,":b i: o: d: p: n: c: :h"))!= -1){
        switch (opt) {
            case 'i':
                strcpy(input,optarg);
                break;
            case 'o':
                strcpy(output,optarg);
                break;
            case 'd':
                if(digitValidate(optarg)) {
                    *min_year = atoi(optarg);
                }
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'p':
                if(digitValidate(optarg)) {
                    *min_price = atof(optarg);
                }
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'b':
                *flag = 1;
                break;
            case 'n':
                if(digitValidate(optarg))
                    *threads = atoi(optarg);
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'c':
                if(digitValidate((optarg)))
                    *chunks = atoi(optarg);
                else{
                    printf("Invalid argument for %c\n",optopt);
                    exit(0);
                }
                break;
            case 'h':
                printf("-i: input file including extension\n"
                       "-o: output file including extension\n"
                       "-d: game start year, must be an int number\n"
                       "-p: minimum game price, must be in dollars\n"
                       "-b: details flag (show additional information on console)\n"
                       "-n: number of threads to create, must be an int number\n"
                       "-c: chunks for each thread, must be an int number\n"
                       "-h: help\n");
                exit(0);
            case '?':
                printf("Unknown option: %c\n",optopt);
                exit(0);
            case ':':
                printf("Missing arg for %c\n",optopt);
                exit(0);
        }
    }
    return 1;
}

// Entradas: char*
// Salidas: int
// Descripción: separa un string hasta obtener el dato que representa el year
int getYear(char * string) {
    char string2[150];
    strcpy(string2,string);
    char separacion[2] = ",";
    char * pedacito;
    int year;
    pedacito = strtok(string2,separacion);//980830,Spirit Hunter: Death Mark,18,50.0,False,2019,False,Yes,No,No
    for (int i = 0; i<5;i++){
        pedacito = strtok(NULL,separacion);
    }
    year = atoi(pedacito);
    return year;
}


//Entradas Char* del nombre del archivo, int del year minimo, int precio minimo, pipes, int de cant de workers
//Salidas TdaLista ** que trabaja como una tabla hash
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este csv se almacena en una tabla hash segun
//            el year del juego en cuestion
int leerCSV(FILE * fp,int chunks,char ** lineasLeidas){
    char string[150];
    int lineas = 0;
    while(fgets(string,150,fp)!=NULL && lineas < chunks){
        strcpy(lineasLeidas[lineas],string);
        lineas++;
    }
    return lineas;
}