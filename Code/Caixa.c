#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fila.h"
#include "Caixa.h"
#include "Cliente.h"

//Struct com os argumentos que serão recebidos pela função
struct argCaixa{
    Caixa* cx;
    int* expediente;
};

//Struct que representa o cliente
struct cliente{
    int n;
    int tempo;
    clock_t* temp_fim;
    clock_t* temp_ini;
};

void* cria_caixa(void* a){

    //Variaveis que irão guardar medidas de tempo
    double t_ini, t_fim, t_total = 0;
    int itens; //Numero de itens do cliente

    //Transforma o ponteiro void para ponteiro do struct argCaixa
    struct argCaixa* c = (struct argCaixa*) a;

    Caixa* ca = c->cx; //Defini o caixa recebido à uma varivel local

    srand(clock()); //Recria a seed do rand com base no clock da cpu

    ca->compe = rand()%10; //Defini a competência do caixa de forma aleatoria
    ca->fila = fila_cria(); //Cria uma fila para o caixa
    ca->tamfila = c->cx->tamfila; //Defini à variavel local a varivavel alocada
                                  //função main

    //Caixa irá continuar esperando ou atendendo clientes enquato houver expediente
    while(*c->expediente){

        //Verifica se tem clientes na fila.
        if(!fila_vazia(ca->fila)){
            //Indica ao usuario qunaod um cliente é atendido.
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

    return NULL;
}
