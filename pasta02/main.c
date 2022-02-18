#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

int principal(void){
    // pegar o nome do arquivo
    char nome_arquivo[250];
    printf("Digite o nome do arquivo: ");
    scanf("%s", &nome_arquivo);
    printf("Nome do arquivo = %s\n", nome_arquivo);

    FILE *entrada;
    entrada = fopen (nome_arquivo, "r");//abre o arquivo
    if (entrada == NULL) {
        printf ("\nNao encontrei o arquivo!\n");
        exit (EXIT_FAILURE);
    }   
    double soma = 0.0;
    int n = 0;
    while (true) {
        int x; 
        int k = fscanf (entrada, "%d", &x);
        if (k != 1) break;
        soma += x;
        n += 1;
    }
    fclose (entrada);//fecha o arquivo
    printf ("A media dos numeros e %f\n", soma/n);
    return EXIT_SUCCESS;
}

int leitura_teclado (void) {
   char linha[100];
   int n = 0;
   while (true) {
      linha[n] = getchar ();
      if (linha[n] == '\n') break;
      n = n + 1;
   }
   for (int i = 0; i <= n; i += 1)
      putchar (linha[i]);
   return EXIT_SUCCESS;
}


int leitura_arquivo (void) {
    FILE* ptr;
    char ch;
 
    // Abrindo o arquivo no modelo de leitura
    ptr = fopen("dados.txt", "r");
 
    if (NULL == ptr) {
        printf("O arquivo nao pode ser aberto\n");
    }
 
    printf("O conteudo do arquivo eh: \n");
 
    // printar o que esta escrito no arquivo
    // caracter por caracter usando o loop
    do {
        ch = fgetc(ptr);
        printf("%c", ch);
 
        // Verificar se caracter nao eh EOF(end of file).
        // Se for EOF, pare de ler.
    } while (ch != EOF);
 
    // Fechando o arquivo.
    fclose(ptr);
    return 0;
}

void entrada() {
    while(true){
        
        printf("####################################################################\n");
        printf("#################  COMPILADOR DE SISTEMAS OPERACIONAIS  ############\n");
        printf("####################################################################\n\n");
        
        printf("********************************************************************\n");
        printf("Digite o comando:\n");
        printf("(cat) leitura de um arquivo\n");
        printf("(exit) sair do compilador\n");
        printf("*******************************************************************\n\n");

        // char comando[50];
        // printf("$");
        // scanf("%s", comando);
        // printf("Comando = %s\n", comando); //digitar o comando

        // if(comando == "cat"){
        //     leitura_arquivo();
        //     break;
        // }
        // else{
        //     printf("comando invalido!! \n\n\n\n\n\n\n\n");
        // }
        break;
    }
}


int main () {
    /*
    exercicio: file:///C:/Users/rafaa/git/sistemas-operacionais/pasta02/aula02_lab.pdf
    ler 
    https://cboard.cprogramming.com/c-programming/48313-if-statements-using-strings-condition.html
    geeksforgeeks.org/c-program-to-read-contents-of-whole-file/
    https://www.geeksforgeeks.org/basic-input-and-output-in-c/
    */
    entrada();
    return 0;
}