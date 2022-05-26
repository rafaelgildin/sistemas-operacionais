// cd /c/Users/rafaa/rafa/git/sistemas-operacionais/projeto2
// clear && gcc main.c -o main -lpthread && ./main

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t the_mutex;
int N_THREADS = 100, TO_TO=0, TO_FROM=0;

struct c {
    int saldo;
};
typedef struct c conta;
conta from, to;

void *to_from(void *arg){//valor, thread
    // printf("thread = %p\n", ptr);
    pthread_mutex_lock(&the_mutex);
    int *arg1 = (int *) arg;
    int valor = *arg1;
    // printf(" valor = %d | ", valor);
    // printf("thread = %d\n", &n);
    if (to.saldo >= valor){
        // printf("i: from = %d | to = %d\n", from.saldo, to.saldo);
        TO_FROM+=1;
        to.saldo -= valor;
        from.saldo += valor;
        printf("i:%d to->from: from = %d | to = %d\n",TO_FROM, from.saldo, to.saldo);
    }
    pthread_mutex_unlock(&the_mutex);
    return NULL;
}

void *to_to(void *arg){//valor, thread
    // printf("thread = %p\n", ptr);
    pthread_mutex_lock(&the_mutex);
    int *arg1 = (int *) arg;
    int valor = *arg1;
    // printf(" valor = %d | ", valor);
    // printf("thread = %d\n", &n);
    if (from.saldo >= valor){
        // printf("i: from = %d | to = %d\n", from.saldo, to.saldo);
        TO_TO+=1;
        from.saldo -= valor;
        to.saldo += valor;
        printf("i:%d from->to: from = %d | to = %d\n",TO_TO ,from.saldo, to.saldo);
    }
    pthread_mutex_unlock(&the_mutex);
    return NULL;
}

int main(int argc, char **argv){
    
    // Todas as contas começam com saldo 100
    from.saldo = 1000;
    to.saldo = 0;
    int i,j, valor=1;
    int n_threads_to_to = N_THREADS*0.1; //10% para mudar de ordem
    pthread_t threads[N_THREADS];//inicializa as threads do consumidor
    pthread_mutex_init(&the_mutex, 0);
    printf("numero de threads = %d\n",N_THREADS);
    printf("numero de threads para TO = %d\n\n",n_threads_to_to);

    for (i = 0; i < N_THREADS; i++) {
        if(i >= N_THREADS-n_threads_to_to){
            pthread_create(&threads[i], 0, to_from, &valor);
        }
        else{
            pthread_create(&threads[i], 0, to_to, &valor); // alterar parametros para passar o valor da
        }
    }
    for (i = 0; i < N_THREADS; i++) {
        for (j = 0; j < 1000; j++) {
            pthread_join(threads[i], 0);
        }
    }
    pthread_mutex_destroy(&the_mutex);
    printf("final main: from = %d | to = %d\n", from.saldo, to.saldo);
}