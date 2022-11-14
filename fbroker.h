
//Entradas: entero que representa el numero maximo a generar
//Salida: Un entero
//Descripcion: Entrega un numero aleatorio entre 0 y el numero ingresado

int myRandom(int n);

// Entradas: char*
// Salidas: int
// Descripción: separa un string hasta obtener el dato que representa el year
int getYear(char * string);

//Entradas: string
//Salidas: float
//Descripcion: separa un string hasta obtener el dato que representa el precio
float getPrice(char * string);

//Entradas Char* del nombre del archivo, int del year minimo, int precio minimo, pipes, int de cant de workers
//Salidas TdaLista ** que trabaja como una tabla hash
//Descripcion se lee el archivo solicitado por el usuario, el contenido de este csv se almacena en una tabla hash segun
//            el year del juego en cuestion
void leerCSV(char nombreArchivo[30],int min_year,int min_price, int fd[][2],int workers);

// Entradas: char* (que es la salida de un worker) x int
// Salidas: char*
// Descripción: realiza strtok una cantida N de veces para obtener un dato de la salida
char * getGenerico(char * string, int posicion);

//Entradas hash, pipes, int cantidad de workers, int min year
//Salida void
//Descripcion lee los N pipes, almacenando los resultados en la hash entregada.
void recolectarDatos(year ** tabla, int fd[][2],int workers, int min_year);

//Entradas year, string
//Salida void
//Descripcion convierte una estructura year en un string entendible
void toString(year* anio,char string[1500]);

//Entradas hash, anio minimo, nombreSalida y flag
//Salidas void
//Descripcion Crea el archivo de salida y le agrega los datos correspondientes
void crearSalida(year** tabla,int min_year, char output[30], int flag);