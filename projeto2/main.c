// gcc main.c -o main && ./main
#define _GNU_SOURCE
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
// 64kB stack
#define FIBER_STACK 1024*64
struct c {
    int saldo;
};
typedef struct c conta;
conta from, to;
int valor;
// The child thread will execute this function
int transferencia( void *arg)
{
    if (from.saldo >= valor){ // 2
        from.saldo -= valor;
        to.saldo += valor;
    }
    printf("Transferência concluída com sucesso!\n");
    printf("Saldo de c1: %d\n", from.saldo);
    printf("Saldo de c2: %d\n", to.saldo);
    return 0;
}
int main()
{
    void* stack;
    pid_t pid;
    int i;
    // Allocate the stack
    stack = malloc( FIBER_STACK );
    if ( stack == 0 )
    {
        perror("malloc: could not allocate stack");
        exit(1);
    }
    // Todas as contas começam com saldo 100
    from.saldo = 100;
    to.saldo = 100;
    printf( "Transferindo 10 para a conta c2\n" );
    valor = 10;
    for (i = 0; i < 10; i++) {
        // Call the clone system call to create the child thread
        pid = clone( &transferencia, (char*) stack + FIBER_STACK,
        SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
        if ( pid == -1 )
        {
            perror( "clone" );
            exit(2);
        }
    }
    // Free the stack
    free( stack );
    printf("Transferências concluídas e memória liberada.\n");
    return 0;
}