#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int cp(void){
    FILE *arquivo1, *arquivo2_leitura, *arquivo2_escrita; // aponta para os arquivos
    char nome_arquivo_1[50], nome_arquivo_2[50];

    printf("Arquivo de entrada: ");
    scanf("%s", nome_arquivo_1);
    printf("Arquivo de saida: ");
    scanf("%s", nome_arquivo_2);
    
	//le os dois arquivos
	arquivo1 = fopen(nome_arquivo_1, "r");
    arquivo2_leitura = fopen(nome_arquivo_2, "r");

    //faz a checagem para achar os arquivos
	if (arquivo1 == NULL){
		printf("O arquivo de entrada nao foi encontrado.\n");
        return 0;
	}
    if (arquivo2_leitura != NULL){
		printf("Ja existe um arquivo com o nome do arquivo de saida.\n");
        return 0;
	}
    arquivo2_escrita = fopen(nome_arquivo_2, "w");

	//itera por um arquivo e vai escrevendo no outro ate chegar no fim do arquivo(EOF)
    char caractere;
	while((caractere=fgetc(arquivo1)) != EOF){
		fputc(caractere,arquivo2_escrita);
	};
	//fecha os dois arquivos
    fclose(arquivo1);
	fclose(arquivo2_escrita);
    fclose(arquivo2_leitura);
    printf("Arquivo copiado com sucesso!\n");
    return 0;
}


int cat (void) {
    FILE* ptr;
    char ch, nome_arquivo[50];

    printf("nome do arquivo: ");
    scanf("%s", nome_arquivo);

    // Abrindo o arquivo no modelo de leitura
    ptr = fopen(nome_arquivo, "r");
 
    if (NULL == ptr) {
        printf("O arquivo nao pode ser aberto\n");
        return 0;
    }
 
    // printar o que esta escrito no arquivo
    // caracter por caracter usando o loop
    printf("O conteudo do arquivo eh: \n");
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
        
        printf("\n\n\n####################################################################\n");
        printf("#################  COMPILADOR DE SISTEMAS OPERACIONAIS  ############\n");
        printf("####################################################################\n\n");
        
        printf("********************************************************************\n");
        printf("Digite o comando:\n");
        printf("(cat) leitura de um arquivo\n");
        printf("(cp) copia de um arquivo para o outro\n");
        printf("(exit) sair do compilador\n");
        printf("*******************************************************************\n\n");

        char comando[50];
        printf("$ ");
        scanf("%s", comando);
        // printf("Comando = %s\n", comando); //digitar o comando

        if(!strcmp(comando,"exit")){
            printf("Saindo do compilador :(\nVolte sempre :)\n\n");
            break;
        }
        else if(!strcmp(comando,"cat")){
            cat();
        }
        else if(!strcmp(comando,"cp")){
            cp();
        }
        else{
            printf("comando invalido!! \n\n\n\n");
        }
    }
}


int main () {
    entrada();
    return 0;
}
