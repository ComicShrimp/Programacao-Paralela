#include <stdlib.h>
#include <stdio.h>
#include "Caixa.h"


void* caixa(void* a)
{
  int numeracao = (int*) a;
  printf("Caixa %d rodando...\n",numeracao);

  return NULL;
}
