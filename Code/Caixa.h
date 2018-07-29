/* Caixa.h */
#include "fila.h"       //Foi necessario trazer o struct e fila.h para poder utilizar o typedef
                        //Ocorreu um erro de foward declaration que impossibilitava a utilização
struct caixa{           //Na função Main
    Fila* fila;
    int compe;
};

typedef struct caixa Caixa;

void* cria_caixa(void* a);
