//gcc CadeiaProcessos.c -o CadeiaProcessos1
//./CadeiaProcessos
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    pid_t childpid = 0;
    int i, n;
    if (argc != 2){ /* check for valid number of command-line arguments */
	    //fprintf(stderr, "Usage: %s processes\n", argv[0]);
        printf(stdout, "Usage: %s processes\n", argv[0]);
	    return 1;
    }
    n = atoi(argv[1]);
    // printf("n = %d", n);
    for (i = 1; i < n; i++)
	    if (childpid = fork())
	    	break;
	    	
    //fprintf(stderr, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",i, (long)getpid(), (long)getppid(), (long)childpid);
    printf(stdout, "i:%d process ID:%ld parent ID:%ld child ID:%ld\n",i, (long)getpid(), (long)getppid(), (long)childpid);
    return 0;
}
