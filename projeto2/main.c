// cd /c/Users/rafaa/rafa/git/sistemas-operacionais/projeto2
// clear && gcc -pthread -o main main.c -o main && ./main
// clear && gcc main.c -o main -lpthread && ./main

// #define _GNU_SOURCE
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <signal.h>
// #include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t the_mutex;
// int buffer = 0; /* buffer usado entre produtor e consumidor */
struct c {
    int saldo;
};
typedef struct c conta;
conta from, to;


void *sacar(void *arg){//valor, thread
    // printf("thread = %p\n", ptr);
    int *arg1 = (int *) arg;
    int valor = *arg1;
    // printf(" valor = %d | ", valor);
    // printf("thread = %d\n", &n);
    if (from.saldo >= valor){
        // printf("i: from = %d | to = %d\n", from.saldo, to.saldo);
        from.saldo -= valor;
        to.saldo += valor;
        printf("from = %d | to = %d\n", from.saldo, to.saldo);
    }
    // return 0;
}


int main(int argc, char **argv){
    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 0;
    int i, valor=1;
    // pthread_t con;
    pthread_t threads[100];//inicializa as threads do consumidor
    pthread_mutex_init(&the_mutex, 0);
    
    for (i = 0; i < 100; i++) {
        // pthread_create(&con, 0, sacar, 0);
        pthread_create(&threads[i], 0, sacar, &valor); // alterar parametros para passar o valor da
        // printf("thread = %d = %d\n", i, &threads[i]);
        // printf("thread %d criada\n", i);
    }
    for (i = 0; i < 100; i++) {
        while(to.saldo < 100){
            pthread_join(threads[i], 0);
        }
    }
    // while(to.saldo < 100){    
    //     // pthread_join(con, 0);
    //     pthread_join(threads[i], 0);
    // }
    pthread_mutex_destroy(&the_mutex);
    printf("final main: from = %d | to = %d\n", from.saldo, to.saldo);
}