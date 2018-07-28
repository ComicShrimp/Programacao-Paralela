#include <stdio.h>
#include <stdlib.h>
#include "Cliente.h"
#include <time.h> //Vai ser usada para gerar a seed do rand

#define MAXITENS 20
#define TEMPO 5

struct cliente{
    int n;
    int tempo;
};


void* cliente(void* a){

    Cliente* c = (Cliente*) malloc(sizeof(Cliente));

    srand((unsigned)time(NULL)); //Recria a seed com base na hora

    c->n = rand()%MAXITENS;
    c->tempo = c->n * TEMPO;

    return NULL;
}
