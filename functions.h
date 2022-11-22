// Entradas: entra un char*
// Salidas: un int 0 o 1
// Descripción: verifica que el string de entrada este conformado solo por digitos
int digitValidate(char * string);

// Entradas: parametros ingresados por consola los cuales podrian variar segun la entrada del usuario
// Salidas: int 0 o 1
// Descripción: verifica los parametros ingresados por consola para corroborar que cumplan ciertos parametros para el
// correcto funcionamiento del codigo.
int validate(int argc, char * argv[], char input[], char output[], int * min_year, int * flag, int * threads,
             float * min_price, int * chunks);

// Entradas: char*
// Salidas: int
// Descripción: transforma un char* a bool(int 0 o 1)
int convertirBool(char string[10]);


// Entradas: char*
// Salidas: int
// Descripción: separa un string hasta obtener el dato que representa el year
int getYear(char * string);


// Entradas: char* (que representa un juego) x int
// Salidas: char*
// Descripción: realiza strtok una cantida N de veces para obtener un dato del juego
char * getGenerico(char string[250], int posicion);