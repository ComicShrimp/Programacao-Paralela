#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "Caixa.h"

#define TC 20

int main(void){

    int nCaixas;
    int i;

    //Limitando o numero de caixas para os valores de 1 a 10.
    do{

        printf("Digite o numero de caixas:");
        scanf("%d",&nCaixas);

    }while((nCaixas < 1) && (nCaixas > 10));

    printf("\nAlocando %d caixas ao supermercado...\n",nCaixas);

    //criando vetor de caixas e alocando dinamicamente
    pthread_t *caixas;
    caixas = malloc(nCaixas * sizeof(pthread_t));

    for (i = 0; i < nCaixas; i++){

        //( endereço , atributos , funcao associada , argumento para funcao)
        pthread_create(&(caixas[i]),NULL,caixa,i + 1);
    }

    for (i = 0; i < nCaixas; i++){

        //botando pra executar a thread ( thread escolida , valor de retorno)
        pthread_join(caixas[i],NULL);
    }
    return 0;
}
