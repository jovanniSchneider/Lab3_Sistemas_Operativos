//
// Created by jovan on 9/13/2022.
//
// Entradas: char* (que representa un juego) x int
// Salidas: char*
// Descripción: realiza strtok una cantida N de veces para obtener un dato del juego
char * getGenerico(char string[250], int posicion);

// Entradas: char*
// Salidas: int
// Descripción: transforma un char* a bool(int 0 o 1)
int convertirBool(char string[10]);

// Entradas: hash, string, anio minimo
// Salidas: void
// Descripción: trabaja un char* del tipo juego, para agregarlo a la tabla hash en la posicion correspondiente
void trabajarLinea(year ** tabla, char linea[250], int min_year);

//Entradas year, string
//Salida void
//Descripcion convierte una estructura year en un string entendible
void toString(year * anio,char string[1000]);

