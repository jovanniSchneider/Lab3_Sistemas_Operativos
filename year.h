#include <string.h>
#include <stdlib.h>
#include <pthread.h>

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
}year;