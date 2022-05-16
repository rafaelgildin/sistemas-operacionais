// cd /c/Users/rafaa/rafa/git/sistemas-operacionais/projeto2
// clear && gcc main.c -o main && ./main
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
    // travar a regiao critica
    if (from.saldo >= valor){ // 2
        from.saldo -= valor;
        to.saldo += valor;
    }
    printf("\nTransferencia concluida com sucesso | from = %d | to = %d \n", from.saldo, to.saldo);
    return 0;
}
int main()
{
    void* stack; // ponteiro sem tipo definido
    pid_t pid;
    printf("\n\npocess id = %d\n\n", pid);
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
    printf( "Transferindo 10 para a conta c2(to)\n" );
    valor = 10;

    // return 0;
    for (i = 8; i < 10; i++) {
        // Call the clone system call to create the child thread
        pid = clone( &transferencia, (char*) stack + FIBER_STACK,
        SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, 0 );
        if ( pid == -1 )
        {
            printf("\nerror in clone\n");
            perror( "clone" );
            exit(2);
        }
    }
    // Free the stack
    free( stack );
    printf("Transferencias concluidas e memoria liberada.\n");
    return 0;
}