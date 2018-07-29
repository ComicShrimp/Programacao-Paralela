#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fila.h"
#include "Caixa.h"
#include "Cliente.h"

#define COMP 10

struct argCaixa{
    Caixa* cx;
    int* expediente;
};

void* cria_caixa(void* a){

    struct argCaixa* c = (struct argCaixa*) a;

    Caixa* ca = c->cx;

    srand((unsigned)time(NULL));

    ca->compe = rand()%COMP;

    ca->fila = fila_cria();

    ca->tamfila = *c->expediente;

    return NULL;
}

void insere_cliente(Cliente* a, Caixa* c){

}
