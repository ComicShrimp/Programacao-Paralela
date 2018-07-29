#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fila.h"
#include "Caixa.h"

#define COMP 10

void* cria_caixa(void* a){

    Caixa* ca = (Caixa*) a;

    srand((unsigned)time(NULL));

    ca->compe = rand()%COMP;

    ca->fila = fila_cria();

    return NULL;
}
