/* fila.h */
#include "Cliente.h"

/* Tipos exportado */
typedef struct fila Fila;
typedef struct lista Lista;

/* Fun��o cria
** Aloca mem�ria para uma estrutura do tipo Fila e retorna o ponteiro
*/
Fila* fila_cria(void);

/* Fun��o insere
** Insere um elemento no fim da Fila
*/
void fila_insere(Fila* f, int v);

/* Fun��o retira
** Remove o elemento do in�cio da Fila
*/
int fila_retira(Fila* f);

/* Fun��o vazia
** Retorna um inteiro (0 ou 1), indicando se a Fila est� vazia ou n�o
*/
int fila_vazia(Fila* f);

/* Fun��o libera
** Libera a mem�ria alocada para a Fila
*/
void fila_libera(Fila* f);

/* exerc�cio 01 */
/* Fun��o imprime
** Imprime todos os elementos da fila em ordem
*/
//void fila_imprime(Fila* f);
/****************/
