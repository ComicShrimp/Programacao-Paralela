#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include "Caixa.h"
#include "Cliente.h"
#include "fila.h"
#include <unistd.h>
#include <math.h>

struct argCliente{
    Caixa* cx;
    int nCaixas;
    int* expediente;
    clock_t* temp_fim;
    clock_t* temp_ini;
};

struct argCaixa{
    Caixa* cx;
    int* expediente;
};

int main(void){

    // nCaixas = numero de caixas  i = variavel para laços for
    // tempoc = tempo de espera dos clientes  t_delay = tempo de execução do programa
    // expediente = indica quando se expendinte esta encerrao ou não
    int nCaixas, i, tempoc, t_delay, expediente;

    //Guarda o valor de começo do programa
    long t_ini;

    t_delay = 0;
    expediente = 1; // Indica que ainda há expediente

    //Limitando o numero de caixas para os valores de 1 a 10.
    do{

        printf("Digite o numero de caixas: ");
        scanf("%d",&nCaixas);               //Pega o numero de caixas do teclado

    }while((nCaixas < 1) && (nCaixas > 10));

    printf("\nDigite o tempo da chegada dos clientes(em segundos): ");
    scanf("%d", &tempoc);  //Pega o delay em segundos da chegada dos clientes

    printf("\nTempo de loja aberta(em minutos): ");
    scanf("%d", &t_delay); //Pega o tempo em que a loja estara aberta
    t_delay *= 60; //multiplica por 60 pois o codigo trabalha em segundos

    //Alocando um vetor de thread's para ser executado junto aos caixas
    pthread_t* cx = (pthread_t*) malloc(nCaixas * sizeof(pthread_t));

    //Alocando os caixas que irão atender os clientes
    Caixa* aux = (Caixa*) malloc(nCaixas * sizeof(Caixa));

    //Alocando struct que guarda parametros necessarios na função cria_caixa
    struct argCaixa* argca = (struct argCaixa*) malloc(nCaixas * sizeof(struct argCaixa));

    //Laço de criação dos caixas
    for (i = 0; i < nCaixas; i++){

        //Atribui o endereço da variavel de expediente e de uma posição do vetor
        //de caixas para uma posição do vetor de struct
        argca[i].cx = &aux[i];
        argca[i].expediente = &expediente;

        //É criado a thread do caixa passando como argumento o struct acima
        pthread_create(&cx[i],NULL,cria_caixa,(void*) &argca[i]);
    }

    printf("\nContagem Iniciada\n"); // Indica ao usuario o inicio da conteagem

    t_ini = time(NULL); // Atribui a variavel o valor da data atual em segundos

    printf("\nSupermercado Aberto.\n"); //Indica o inicio da chegada dos clientes

    //calculo do numero de thread's necessarios para os clientes com base no tempo
    //de execução e no tempo de chegada de cada cliente.
    int n_thread = ceil((t_delay / tempoc)); //Valor é arredondado sempre para cima
    pthread_t n[n_thread]; //Alocação das thread's dos clientes

    //Alocando struct que guarda parametros necessarios na função cliente.
    struct argCliente* argc = (struct argCliente*) malloc(n_thread * sizeof(struct argCliente));

    //Alocação dos vetores para guarda os tempos iniciais e finais de cada cliente
    clock_t* tempo_ini = (clock_t*) malloc(n_thread * sizeof(clock_t));
    clock_t* tempo_fim = (clock_t*) malloc(n_thread * sizeof(clock_t));

    int p = 0;
    //Laço de criação dos clientes
    while(time(NULL) - t_ini < t_delay){ //Irá rodar até o tempo estipulado

        //Atribuindo valores para o struct auxiliar dos clientes
        argc[p].cx = aux;
        argc[p].nCaixas = nCaixas;
        argc[p].expediente = &expediente;
        argc[p].temp_fim = &tempo_fim[p];
        argc[p].temp_ini = &tempo_ini[p];

        printf("\nCliente Chegou\n");
        pthread_create(&n[p], NULL, cliente,(void*) &argc[p]);
        sleep(tempoc); //Delay estipulado entre a criação dos clientes
        p++;
    }

    expediente = 0; // Indica o fim do expediente

    //Indica ao usuario, que o expediente foi encerrado
    printf("\nExpediente Encerrado !!!\n");
    printf("\nTodos os Clientes estao no caixa ou foram embora.\n");

    //Aguarda todos os caixas finalizarem o atendimento atual
    for(i = 0;i < nCaixas;i++){
        pthread_join(cx[i], NULL);
    }

    //Indica ao usuario que todos os caixas encerram seus atendimentos
    printf("\nCaixas Encerrados, Fim de expediente.\n");

    //Variaveis auxiliares no calculo da media de tempo de atendimento.
    double media = 0;//Guarda a media de tempo total
    double tmp = 0; //Guarda o valor do tempo temporariamente
    int n_exec = 0; //Guarda o numero de clientes atendidos

    printf("\nTempos Individuais\n");

    //Laço para mostrar e somar todos os tempos individuais dos clientes
    for(i = 0;i < n_thread;i++){

        //Calcula a diferença de tempo desde a entrada da fila ate o atendimento.
        tmp = difftime(tempo_fim[i], tempo_ini[i]);

        //Verifica se o valor é maior que zero, pois, o tempo final é adquirido
        //antes do inicial, para poder filtrar os clientes que realmente foram
        //executados.
        if((tmp >= 0) && (tmp < 600)){
            n_exec++;
            printf("Tempo %f\n", tmp);
            media += tmp;
        }
    }

    //Mostra ao usuario as informações obtidas
    printf("\nClientes que chegaram ao Supermercado: %d\n",n_thread);
    printf("\nClientes Atendidos: %d\n", n_exec);

    media = media / n_exec; // Cacula a media

    printf("\nTempo medio de atendimento: %.2f\n", media);

    return 0;
}
