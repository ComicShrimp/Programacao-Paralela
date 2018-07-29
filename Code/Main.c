#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "Caixa.h"
#include "fila.h"
#include "unistd.h"

#define TC 20

int main(void){

    int nCaixas;
    int i;
    int tempoc;
    int t_delay;

    long t_ini;

    t_delay = 0;

    //Limitando o numero de caixas para os valores de 1 a 10.
    do{

        printf("Digite o numero de caixas: ");
        scanf("%d",&nCaixas);

    }while((nCaixas < 1) && (nCaixas > 10));

    printf("\nDigite o tempo da chegada dos clientes: ");
    scanf("%d", &tempoc);
    printf("Tempo de loja aberta(em minutos): ");
    scanf("%d", &t_delay);
    printf("O Programa Iniciou\n");

    t_ini = time(NULL);

    //criando vetor de caixas e alocando dinamicamente
    pthread_t cx[10];

    //Criação dos caixas que irão atender os clientes
    Caixa* aux = (Caixa*) malloc(nCaixas * sizeof(Caixa));

    for (i = 0; i < nCaixas; i++){

        //( endereço , atributos , funcao associada , argumento para funcao)
        printf("Ola\n");
        pthread_create(&cx[i],NULL,cria_caixa,(void*) &aux[i]);
    }

    printf("Terminei\n");;
    while(time(NULL) - t_ini < t_delay){
        printf("Executando\n");
        fflush(stdout);
        sleep(tempoc);
    }

    fflush(stdout);
    printf("Acabou\n");

    return 0;
}
