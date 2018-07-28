/* fila.c */
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct lista {	// estrutura lista para implementação da lista
	float info;
	struct lista* prox;
};

struct fila {
	Lista* ini;	// ponteiro para o nó do início da fila
	Lista* fim;	// ponteiro para o nó do fim da fila
};
	
Fila* fila_cria(void) {						// cria uma fila, alocando memória para ela
	Fila* f = (Fila*) malloc(sizeof(Fila));	// aloca memória do tamanho de uma fila
	f->ini = f->fim = NULL;					// inicializa os dois ponteiros (ini e fim) como nulos, pois a fila está vazia
	return f;								// retorna o ponteiro que aponta para o endereço alocado
}
	
void fila_insere(Fila* f, float v) {			// insere um elemento (nó) no fim da fila 
	Lista* n = (Lista*) malloc(sizeof(Lista));	// aloca memória para o novo nó
	n->info = v;								// guarda no nó o valor passado como argumento (float v)
	n->prox = NULL;								// faz o próximo do nó ser nulo, pois será o último
	if(f->fim != NULL)							// verifica se a fila não está vazia...
		f->fim->prox = n;							// se não estiver, apenas faz o atual nó do fim apontar para o novo nó criado
	else										// caso contrário...
		f->ini = n;									// já que a fila está vazia, o novo nó será tanto o último como o primeiro. Então, é preciso atualizar "ini" também
	f->fim = n;									// faz o ponteiro "fim" apontar para o novo nó, já que ele será mesmo o último da fila
}

int fila_vazia(Fila* f) {		// verifica se a fila está vazia ou não
	return (f->ini == NULL);	// retorna o resultado (0 ou 1) da operação lógica de igualdade entre o ponteiro "ini" e NULL (se for NULL, a fila está vazia: retorna 1)
}

float fila_retira(Fila* f) {		// remove o primeiro elemento da fila (FIFO)
	Lista* t;						// ponteiro auxiliar para guardar o nó que vai ser removido
	float v;
	if(fila_vazia(f)) {				// verifica se a fila está vazia. Se estiver...
		printf("Fila vazia!\n");		// imprime mensagem de fila vazia
		exit(1);						// e encerra o programa
	}								// se não estiver, continua a função
	t = f->ini;						// guarda temporariamente o endereço do primeiro nó
	v = t->info;					// guarda temporariamente a informação do primeiro nó
	f->ini = t->prox;				// atualiza ponteiro "ini" para o próximo elemento da fila
	if(f->ini == NULL)				// se a fila tiver ficado vazia após a remoção...
		f->fim = NULL;					// atualiza também o ponteiro do fim para NULL
	free(t);						// libera o endereço do nó removido
	return v;						// retorna o valor do nó removido (float)
}

void fila_libera(Fila* f) {		// libera a memória alocada para a fila
	Lista* q = f->ini;			// ponteiro auxiliar para começar a percorrer a lista da fila desde o início
	while(q != NULL) {			// laço para percorrer a lista da fila
		Lista* t = q->prox;			// guarda o endereço do próximo nó para que o atual seja liberado sem perder a lista
		free(q);					// libera o nó atual
		q = t;						// aponta para o próximo nó (que estava guardado em "t")
	}
	free(f);					// libera, por fim, o ponteiro da fila inteira
}

/* exercício 01 */
void fila_imprime(Fila* f) {			// imprime todos os elementos da fila
	if(!fila_vazia(f)) {				// verifica se a fila não está vazia. Se não estiver...
		Lista* q = f->ini;					// ponteiro auxiliar para percorrer a lista da fila desde o início
		while(q != NULL) {					// laço para percorrer a lista até o fim
			printf("%.2f ", q->info);			// imprime informação (valor) do nó atual
			q = q->prox;						// atualiza "q" para o próximo nó da lista
		}
		printf("\n");						// imprime nova linha ao fim da impressão da fila
	} else								// caso contrário, se estiver vazia...
		printf("Fila vazia!\n");			// imprime mensagem indicando que está vazia
}
/****************/
