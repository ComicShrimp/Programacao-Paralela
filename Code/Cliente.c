#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "fila.h"
#include "Cliente.h"
#include "Caixa.h"
#include <time.h> //Vai ser usada para gerar a seed do rand
#include <unistd.h>

#define MAXITENS 20
#define TEMPO 2

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

    sleep(c->tempo);

    Caixa* caux;
    int menor = -1;

    int i;
    for(i = 0;i < argc->nCaixas;i++){

        pthread_mutex_lock(&trava);

        if((menor == -1) || (menor > argc->cx[i].tamfila)){
            menor = argc->cx->tamfila;
            caux = &argc->cx[i];
        }

        pthread_mutex_unlock(&trava);
    }

    insere_cliente(c->n, caux);

    return NULL;
}
