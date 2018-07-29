#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "Caixa.h"
#include "Cliente.h"
#include "fila.h"
#include <unistd.h>

#define TC 20

struct argCliente{
    Caixa* cx;
    int nCaixas;
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

    t_ini = time(NULL);

    //criando vetor de caixas e alocando dinamicamente
    pthread_t* cx = (pthread_t*) malloc(nCaixas * sizeof(pthread_t));

    //Criação dos caixas que irão atender os clientes
    Caixa* aux = (Caixa*) malloc(nCaixas * sizeof(Caixa));

    //Passando parametros para o struct pra poder passar pra função clinete
    struct argCliente argc;

    argc.cx = aux;
    argc.nCaixas = nCaixas;

    //Passando parametros para passar pra função cria_caixa
    struct argCaixa argca;

    for (i = 0; i < nCaixas; i++){

        argca.cx = &aux[i];
        argca.expediente = &expediente;

        //( endereço , atributos , funcao associada , argumento para funcao)
        pthread_create(&cx[i],NULL,cria_caixa,(void*) &argca);
    }

    printf("Clientes chegando.\n\n");

    int n_thread = (t_delay / tempoc);
    pthread_t n[n_thread];

    int p = 0;
    while(time(NULL) - t_ini < t_delay){
        printf("\nCliente Chegou\n");
        pthread_create(&n[p], NULL, cliente,(void*) &argc);
        sleep(tempoc);
        p++;
    }

    //Espera todos os clientes chegarem ao caixa
    for(i = 0;i < n_thread;i++){
        pthread_join(n[i], NULL);
    }

    expediente = 0;

    printf("\nExpediente Encerrado !!!\n");

    for(i = 0;i < nCaixas;i++){
        pthread_join(cx[i], NULL);
    }

    printf("Caixas Encerrados, Fim de expediente.\n");

    return 0;
}
