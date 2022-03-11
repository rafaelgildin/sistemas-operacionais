/* 
para execução:
clear && gcc fork-question-1.c -o fork-question-1 && ./fork-question-1  && echo

Um processo não pode invadir o espaco de memoria do outro
Objetivo: alteração do processo filho se reflita no processo pai. Logo o 
          ultimo print deve ser: PARENT: value = 20

*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int value=5, p[2];
    pipe(p);
	pid_t pid;
	pid = fork();

	if (pid == 0) { /* child process */
		printf("Entrei no filho!\n");
		value += 15;
        write(p[1], &value, sizeof(value));
		printf ("CHILD: value = %d\n",value); /* LINE A */
		return 0;
	}
	else if (pid > 0) { /* parent process */
		wait(NULL);// bloquea o pai ate terminar os processos filhos
        read(p[0], &value, sizeof(value));
		printf ("PARENT: value = %d\n",value); /* LINE A */
		return 0;
	}
}