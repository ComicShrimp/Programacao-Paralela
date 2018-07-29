#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fila.h"
#include "Caixa.h"
#include "Cliente.h"

#define COMP 10

struct argCaixa{
    Caixa* cx;
    int* expediente;
};

void* cria_caixa(void* a){

    int t_ini, t_fim, itens;

    struct argCaixa* c = (struct argCaixa*) a;

    Caixa* ca = c->cx;

    srand((unsigned)time(NULL));

    ca->compe = rand()%COMP;
    ca->fila = fila_cria();
    ca->tamfila = c->cx->tamfila;
    int expediente = *c->expediente;

    while(expediente){
        if(!fila_vazia(ca->fila)){
            t_ini = time(NULL);

            itens = fila_retira(ca->fila);

            sleep((itens + ca->compe) / ca->compe);

            t_fim = time(NULL);
            printf("Tempo de Atendimeto: %d", t_fim - t_ini);
        }
    }

    return NULL;
}

void insere_cliente(int n, Caixa* c){
    fila_insere(c->fila, n);
}
