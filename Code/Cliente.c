#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "fila.h"
#include "Cliente.h"
#include "Caixa.h"
#include <time.h> //Vai ser usada para gerar a seed do rand
#include <unistd.h>

#define MAXITENS 20
#define TEMPO 1

struct cliente{
    int n;
    int tempo;
};

struct argCliente{
    Caixa* cx;
    int nCaixas;
};

void* cliente(void* a){

    pthread_mutex_t trava = PTHREAD_MUTEX_INITIALIZER;

    Cliente* c = (Cliente*) malloc(sizeof(Cliente));

    struct argCliente* argc = (struct argCliente*) a;

    srand((unsigned)time(NULL)); //Recria a seed com base na hora

    c->n = rand()%MAXITENS;
    c->tempo = c->n * TEMPO;
    Caixa* l = argc->cx;

    sleep(c->tempo);

    Caixa* caux;
    int menor = -1;

    int i;

    pthread_mutex_lock(&trava);

    for(i = 0;i < argc->nCaixas;i++){

        if((menor == -1) || (menor > l[i].tamfila)){
            menor = argc->cx->tamfila;
            caux = &argc->cx[i];
        }

    }

    printf("\nEntrando na fila\n");

    insere_cliente(c->n, caux);

    pthread_mutex_unlock(&trava);

    return NULL;
}
