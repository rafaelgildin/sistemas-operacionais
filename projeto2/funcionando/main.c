// cd /c/Users/rafaa/rafa/git/sistemas-operacionais/projeto2
// clear && gcc main.c -o main -lpthread && ./main

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t the_mutex; //cira o mutex para a thread acessar a regiao critica
int N_THREADS = 100, TO_TO=0, TO_FROM=0;

struct c {
    int saldo;
};
typedef struct c conta;
conta from, to;

void *to_to(void *arg){
    /*
    objetivo: transfere valor da conta from para a conta to
    input: ponteiro para o valor
    output: NULL 
    */
    pthread_mutex_lock(&the_mutex);
    int *arg1 = (int *) arg;
    int valor = *arg1;
    if (from.saldo >= valor){
        TO_TO+=1;
        from.saldo -= valor;
        to.saldo += valor;
        printf("i:%d from->to: from = %d | to = %d\n",TO_TO ,from.saldo, to.saldo);
    }
    pthread_mutex_unlock(&the_mutex);
    return NULL;
}

void *to_from(void *arg){//valor
    /*
    objetivo: transfere valor da conta to para a conta from
    input: ponteiro para o valor
    output: NULL
    */
    pthread_mutex_lock(&the_mutex);//acessa a regiao critica
    int *arg1 = (int *) arg;
    int valor = *arg1;
    if (to.saldo >= valor){
        TO_FROM+=1;
        to.saldo -= valor;
        from.saldo += valor;
        printf("i:%d to->from: from = %d | to = %d\n",TO_FROM, from.saldo, to.saldo);
    }
    pthread_mutex_unlock(&the_mutex);//sai da regiao critica
    return NULL;
}

int main(int argc, char **argv){
    // Coloca os saldos das contas
    from.saldo = 100;
    to.saldo = 0;
    int i,j, valor=1;
    int n_threads_to_from = N_THREADS*0.1; //10% do N_THREADS para transferir do TO ao FROM
    int n_threads_to_to = N_THREADS*0.9; //90% do N_THREADS para transferir do FROM ao TO
    pthread_t threads[N_THREADS];//inicializa as threads
    pthread_mutex_init(&the_mutex, 0);//inicializa o mutex
    printf(
        "total de threads = %d; para TO = %d | para FROM = %d \n\n",
        N_THREADS,
        n_threads_to_to,
        n_threads_to_from);

    // cria as threads
    for (i = 0; i < N_THREADS; i++) {
        if(i < n_threads_to_to){
            pthread_create(&threads[i], 0, to_to, &valor);//thread from->to
        }
        else{
            pthread_create(&threads[i], 0, to_from, &valor);//thread to->from
        }
    }

    for (i = 0; i < N_THREADS; i++) {
        for (j = 0; j < 1000; j++) {//loop extra para testar o programa na exaustao
            pthread_join(threads[i], 0);//executa as threads
        }
    }
    pthread_mutex_destroy(&the_mutex);//destroi o mutex
    printf("final main:\nSaldos:\nfrom = %d | to = %d\n", from.saldo, to.saldo);
}