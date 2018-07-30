#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fila.h"
#include "Caixa.h"
#include "Cliente.h"

struct argCaixa{
    Caixa* cx;
    int* expediente;
};

struct cliente{
    int n;
    int tempo;
    clock_t* temp_fim;
    clock_t* temp_ini;
};

void* cria_caixa(void* a){

    double t_ini, t_fim, t_total = 0;
    int itens;

    struct argCaixa* c = (struct argCaixa*) a;

    Caixa* ca = c->cx;

    srand(clock());

    ca->compe = rand()%10;
    ca->fila = fila_cria();
    ca->tamfila = c->cx->tamfila;

    while((*c->expediente) /*|| (!fila_vazia(ca->fila))*/){ //A fila agora para quando acaba o tempo
        if(!fila_vazia(ca->fila)){
            printf("\nCliente Sendo Atendido\n");
            t_ini = time(NULL);

            Cliente* cl = fila_retira(ca->fila);

            itens = cl->n;

            *cl->temp_fim = t_ini;

            sleep((itens + ca->compe) / ca->compe);

            t_fim = time(NULL);
            t_total += t_fim - t_ini;
            printf("\nTempo de Atendimeto(itens: %d, Comp.: %d): %.2f\n", itens, ca->compe, t_fim - t_ini);
            ca->tamfila -= 1;
        }
    }

    while(!fila_vazia(ca->fila)){
        fila_retira(ca->fila);
    }

    return NULL;
}

void insere_cliente(Cliente* n, Caixa* c){
    c->tamfila += 1;
    fila_insere(c->fila, n);
    printf("Inseriu\n");
}
