#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "fila.h"
#include "Cliente.h"
#include "Caixa.h"
#include <time.h> //Vai ser usada para gerar a seed do rand
#include <unistd.h>

#define MAXITENS 15 //Numero maximo de itens que um cliente pode ter
#define TEMPO 1 //Tempo de espera no Supermercado por item

//Struct que representa o cliente
struct cliente{
    int n;
    int tempo;
    clock_t* temp_fim;
    clock_t* temp_ini;
};

//Struct com os argumentos que serão recebidos pela função
struct argCliente{
    Caixa* cx;
    int nCaixas;
    int* expediente;
    clock_t* temp_fim;
    clock_t* temp_ini;
};

//Função Cliente
void* cliente(void* a){

    //Inicializa um variavel necessario para a exclusão multipla
    pthread_mutex_t trava = PTHREAD_MUTEX_INITIALIZER;

    //Aloca um cliente
    Cliente* c = (Cliente*) malloc(sizeof(Cliente));

    //Transforma o ponteiro void para ponteiro do struct argCliente
    struct argCliente* argc = (struct argCliente*) a;

    srand(clock()); //Recria a seed do rand com base no clock da cpu

    c->n = 1 + (rand()%MAXITENS); //Defini o numero de itens aleatoriamente.
    c->tempo = c->n * TEMPO; //Defini o tempo antes de ir ao caixa
    //Atribui as Variaveis recebidas à variavel local
    c->temp_ini = argc->temp_ini;
    c->temp_fim = argc->temp_fim;

    //Guarda o tempo final antes do inicial para realizar a filtragem dos Clientes
    //executados no final do programa
    *c->temp_fim = time(NULL);

    Caixa* l = argc->cx; //Defini o vetor de caixas recebido à uma varivel local

    sleep(c->tempo); //Aguarda o tempo definido mais acima

    Caixa* caux; //Variavel auxiliar para guardar o caixa com menor fila
    int menor = -1; //variavel para indicar a primeira execução do laço

    int i;

    //inicio da Região critica onde há exclusão mutua
    pthread_mutex_lock(&trava);

    //laço para verificar o caixa com menor fila
    for(i = 0;i < argc->nCaixas;i++){

        if((menor == -1) || (menor > l[i].tamfila)){
            menor = argc->cx->tamfila;
            caux = &argc->cx[i];
        }

    }

    //Indica ao usuario que o cliente entrou na fila.
    printf("\nEntrando na Fila\n");

    *c->temp_ini = time(NULL); //Guarda o tempo em que o cliente entrou na fila

    //Incrementa o valor da fila do caixa no qual o cliente entrou
    caux->tamfila += 1;

    //Isere o cliente na fila do caixa
    fila_insere(caux->fila, c);

    //Fim da Região critica
    pthread_mutex_unlock(&trava);

    return NULL;
}
