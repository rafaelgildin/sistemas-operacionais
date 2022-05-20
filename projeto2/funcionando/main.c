// cd /c/Users/rafaa/rafa/git/sistemas-operacionais/projeto2
// clear && gcc main.c -o main && ./main
#define _GNU_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t the_mutex;
int buffer = 0; /* buffer usado entre produtor e consumidor */
int valor_consumidor = 0;
int valor_produtor = 0;

struct c {
    int saldo;
};

typedef struct c conta;
conta from, to;
int valor;

void * sacar(void *ptr){//valor, thread
    int valor = 1;
    if (from.saldo >= valor){
        // printf("i: from = %d | to = %d\n", from.saldo, to.saldo);
        from.saldo -= valor;
        to.saldo += valor;
        printf("f: from = %d | to = %d\n", from.saldo, to.saldo);
    }
    return 0;
}

int main(int argc, char **argv){
    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 0;
    int i;
    pthread_t con;//inicializa as threads do consumidor
    printf( "Transferindo 10 para a conta c2(to)\n" );
    valor = 10;
    pthread_mutex_init(&the_mutex, 0);
    
    for (i = 0; i < 100; i++) {
        pthread_create(&con, 0, sacar, 0);
        // printf("thread %d criada\n", i);
    }

    while(to.saldo < 100){
        pthread_join(con, 0);
    }

    pthread_mutex_destroy(&the_mutex);
    printf("final main: from = %d | to = %d\n", from.saldo, to.saldo);

}