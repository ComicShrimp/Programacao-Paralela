#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "Caixa.h"

#define AT 20

int main(void)
{
  int num1;
  int i ;
  printf("Digite o numero de caixas:");
  scanf("%d",&num1);
  printf("alocando %d caixas ao supermercado...\n",num1);

  //criando vetor de caixas e alocando dinamicamente
  pthread_t *caixas;
  caixas = malloc(num1 * sizeof(pthread_t));

  for (i = 0; i < num1; i++)
  {
    //( endereço , atributos , funcao associada , argumento para funcao)
    pthread_create(&(caixas[i]),NULL,caixa,i + 1);
  }

  for (i = 0; i < num1; i++)
  {
    //botando pra executar a thread ( thread escolida , valor de retorno)
    pthread_join(caixas[i],NULL);
  }

return 0;
}
