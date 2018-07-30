#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "Caixa.h"
#include "Cliente.h"
#include "fila.h"
#include <unistd.h>

struct argCliente{
    Caixa* cx;
    int nCaixas;
    double* temp_fim;
    double* temp_ini;
};

struct argCaixa{
    Caixa* cx;
    int* expediente;
};

int main(void){

    int nCaixas, i, tempoc, t_delay, expediente;

    long t_ini;

    t_delay = 0;
    expediente = 1;

    //Limitando o numero de caixas para os valores de 1 a 10.
    do{

        printf("Digite o numero de caixas: ");
        scanf("%d",&nCaixas);

    }while((nCaixas < 1) && (nCaixas > 10));

    printf("\nDigite o tempo da chegada dos clientes: ");
    scanf("%d", &tempoc);
    printf("\nTempo de loja aberta(em minutos): ");
    scanf("%d", &t_delay);
    //t_delay *= 60;

    printf("O Programa Iniciou\n");

    //criando vetor de caixas e alocando dinamicamente
    pthread_t* cx = (pthread_t*) malloc(nCaixas * sizeof(pthread_t));

    //Criação dos caixas que irão atender os clientes
    Caixa* aux = (Caixa*) malloc(nCaixas * sizeof(Caixa));

    //Passando parametros para passar pra função cria_caixa
    struct argCaixa* argca = (struct argCaixa*) malloc(nCaixas * sizeof(struct argCaixa));

    for (i = 0; i < nCaixas; i++){

        argca[i].cx = &aux[i];
        argca[i].expediente = &expediente;

        //( endereço , atributos , funcao associada , argumento para funcao)
        pthread_create(&cx[i],NULL,cria_caixa,(void*) &argca[i]);
    }

    t_ini = time(NULL);

    printf("Supermercado Aberto.\n\n");

    int n_thread = (t_delay / tempoc);
    pthread_t n[n_thread];

    //Passando parametros para o struct pra poder passar pra função cliente
    struct argCliente* argc = (struct argCliente*) malloc(n_thread * sizeof(struct argCliente));

    double* tempo_ini = (double*) malloc(n_thread * sizeof(double));
    double* tempo_fim = (double*) malloc(n_thread * sizeof(double));

    int p = 0;
    while(time(NULL) - t_ini < t_delay){

        argc[i].cx = aux;
        argc[i].nCaixas = nCaixas;
        argc[i].temp_fim = &tempo_fim[i];
        argc[i].temp_ini = &tempo_ini[i];

        printf("\nCliente Chegou\n");
        pthread_create(&n[p], NULL, cliente,(void*) &argc[i]);
        sleep(tempoc);
        p++;
    }

    expediente = 0;

    printf("\nExpediente Encerrado !!!\n");

    //Espera todos os clientes chegarem ao caixa
    for(i = 0;i < n_thread;i++){
        pthread_join(n[i], NULL);
    }


    printf("Todos os Clientes estao no caixa\n");

    for(i = 0;i < nCaixas;i++){
        pthread_join(cx[i], NULL);
    }

    printf("Caixas Encerrados, Fim de expediente.\n");

    double media = 0;
    double tmp = 0;
    int n_exec = 1;

    for(i = 0;i < n_thread;i++){

        printf("Tempo decorrido %.2f\n", difftime(tempo_fim[i], tempo_ini[i]));
    }

    printf("Executados %d\n", n_exec);

    media = media / n_exec;

    printf("Tempo medio de atendimento %.2f\n", media);

    return 0;
}
