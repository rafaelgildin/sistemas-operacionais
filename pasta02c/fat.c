/* 
Programa em C para calcular o fatorial com multiprocessamento usando fork()
para executar: clear && gcc fat.c -o fat && ./fat 3 && echo
fontes:
    - https://www.geeksforgeeks.org/fork-system-call/
    - https://www.geeksforgeeks.org/factorial-calculation-using-fork-c-linux/
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main(int argc , char *argv[])
{
	pid_t pid; // pegando o id do processo
	if (argc != 2) // se o número de argumentos na chamada for diferente de 2
	{
		printf("falta ou excesso de argumentos\n");
		exit(0);
	}
	// atoi converte string para integer
	if ( atoi ( argv[1] ) < 0)
	{
		printf("nao se calcula fatorial de numero negativo. %d", atoi(argv[1]));
		exit(0);
	}
	pid=fork();//Cria o processo filho
	if ( pid<0 )
	{
		printf("falha ao criar o filho\n");
		exit(0);
	}
	else if ( pid==0 )//Processo filho
	{
		int k = 2;
        int i,j,n;
		// atoi converte o argumento do fatorial de string para integer
		n = atoi(argv[1]);
		int arr[n];//cria 2 vetores
		arr[0] = 1;//fat(0) = 1
		// gerando a serie fatorial até n
		for (i=1 ; i<n; i++) //ex:fat(2) arr[1]=arr[0]*2=1*2=2
		{
			arr[i] = arr[i-1]*k;
			k++;
		}
        //printa o fatorial
        printf("fat(%d) = %d\n", n,arr[n-1]);
		exit(0);
	}
	//Processo pai
	else
	{
		wait(NULL);
		// espera o processo filho terminar
		// printf("Done\n");
	}
}
