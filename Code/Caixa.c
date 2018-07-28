#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "fila.h"
#include "Caixa.h"

#define COMP 10

struct caixa{
    Fila* fila;
    int comp;
};

void* caixa(void* a){

    Caixa* ca = (Caixa*) malloc(sizeof(Caixa));

    srand((unsigned)time(NULL));

    ca->comp = rand()%COMP;

    ca->fila = fila_cria();

    return NULL;
}
