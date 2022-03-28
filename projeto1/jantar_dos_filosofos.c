/*
executar no terminal:
   gcc -o jantar_dos_filosofos.o jantar_dos_filosofos.c -pthread && ./jantar_dos_filosofos.o 
   http://wiki.icmc.usp.br/images/7/76/Aula06_2.pdf
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//constantes
#define QUANT (5)                     //Quantidade de filósofos
#define ESQUERDA (id_filosofo + QUANT - 1) % QUANT   //Id do filósofo a esquerda do id
#define DIREITA  (id_filosofo + 1) % QUANT              //Id do filósofo a direita do id
#define PENSANDO (0)                     //Id para estado pensado
#define FAMINTO  (1)                                //Id para estado de fome
#define COMENDO  (2)                      //Id para estado comendo
#define TEMPO (5)

//global
int estado [QUANT];                        //Estado dos filósofos
pthread_mutex_t mutex;                     //Região crítica
pthread_mutex_t mux_filo [QUANT];                    //Mutex por filósofo
pthread_t jantar[QUANT];                          //Todos os filósofos

//prototipacao
void * filosofo ( void * param );
void pegar_hashi ( int id_filosofo );
void devolver_hashi ( int id_filosofo );
void intencao ( int id_filosofo );
void comer ( int id_filosofo );
void pensar ( int id_filosofo );

//-------------------------------------------------------------------------------
/*!
* @fn void devolver_hashi ( int id_filosofo )
* @brief Função que filósofo devolve os hashis para a mesa
* @param id_filosofo id do filósofo
*/
void devolver_hashi ( int id_filosofo )
{
   pthread_mutex_lock ( &(mutex) );   //Entra na regiсo crítica
   printf("Filosofo %d esta pensando\n", id_filosofo);
   estado[ id_filosofo ] = PENSANDO;   //Terminou de comer
   intencao( ESQUERDA );         //Vê se o vizinho da esquerda pode comer agora
   intencao( DIREITA );            //Vê se o vizinho da direita pode comer agora
   pthread_mutex_unlock ( &(mutex) );   //Sai da regiсo crítica
}
//-------------------------------------------------------------------------------
/*!
* @fn void comer ( int id_filosofo )
* @brief Função que filósofo fica comendo
*/
void comer ( int id_filosofo )
{
   int r = (rand() % 10 + 1);
   sleep( r );   //Gasta um tempo em segundos
}
//-------------------------------------------------------------------------------
/*!
* @fn void intencao ( int id_filosofo )
* @brief Função que filósofo tem intenção de pegar os hashis para comer
* @param id_filosofo id do filósofo
*/
void intencao ( int id_filosofo )
{
   printf("Filosofo %d esta com intencao de comer\n", id_filosofo);
   if( (estado[id_filosofo] == FAMINTO) &&           //Se o filósofo está come fome
      (estado[ESQUERDA] != COMENDO) &&     //Se o vizinho da esquerda não está comendo
      (estado[DIREITA] != COMENDO ) )      //Se o vizinho da direita nсo está comendo
   {
      printf("Filosofo %d ganhou a vez de comer\n", id_filosofo);
      estado[ id_filosofo ] = COMENDO;          //Filósofo ganho a vez de comer
      pthread_mutex_unlock( &(mux_filo[id_filosofo]) );   //Libera os hashis
   }
}
//-------------------------------------------------------------------------------
/*!
* @fn void pegar_hashi ( int id_filosofo )
* @brief Função que filósofo pega os hashis da mesa
* @param id_filosofo id do filósofo
*/
void pegar_hashi ( int id_filosofo )
{
   pthread_mutex_lock( &(mutex) );         //Entra na regiсo crítica
   printf("Filosofo %d esta faminto\n", id_filosofo);
   estado[ id_filosofo ] = FAMINTO;            //Altera o estado do filósofo
   intencao( id_filosofo );               //Intenção de pegar os hashis
   pthread_mutex_unlock( &(mutex) );         //Sai na região crítica
   pthread_mutex_lock( &(mux_filo[id_filosofo]) );   //Bloqueia os hashis
}
//-------------------------------------------------------------------------------
/*!
* @fn void pensar ( int id_filosofo )
* @brief Função que filósofo fica pensando
*/
void pensar ( int id_filosofo )
{
   int r = (rand() % 10 + 1);
   printf("Filosofo %d pensa por %d segundos\n", id_filosofo, r );
   sleep( r );   //Gasta um tempo em segundos
}
//-------------------------------------------------------------------------------
/*!
* @fn void * filosofo ( void * param )
* @brief 
* @param vparam id do filósofo
*/
void * filosofo ( void * vparam )
{
   int * id = (int *) (vparam);   //Repassa o id do filósofo
   printf("Filosofo %d foi criado com sucesso\n", *(id) );
   while (1)//enquanto todos os filosofos não estiverem alimentados
   {
      pensar( *(id) );         //Aguarda o filósofo pensar
      pegar_hashi( *(id) );      //Filósofo pega os hashis
      comer( *(id) );         //Aguarda comer
      devolver_hashi( *(id) );   //Devolver os hashis pra mesa
   }
   pthread_exit( (void*) 0 );      //Legado do retorno
}
//-------------------------------------------------------------------------------
int main ( void )
{
   int cont;   //Contador auxiliar
   int status;   //Criação da thread

   //Inicia os mutexes
   pthread_mutex_init( &(mutex), NULL);
   for( cont = 0 ; cont < QUANT ; cont++ )
   {
      pthread_mutex_init( &(mux_filo[cont]), NULL );
   }

   //Inicia threads (filósofos)
   for( cont = 0 ; cont < QUANT ; cont++ )
   {
      //verifica se ocorreu erro
      status = pthread_create( &(jantar[cont]), NULL, filosofo, (void *) &(cont) );
      // printf("filoso %d criado-----------------------\n", cont);
      if ( status )
      {
         printf("Erro criando thread %d, retornou codigo %d\n", cont, status );
         return EXIT_FAILURE;
      }
   }

   //Destroi antes de sair
   pthread_mutex_destroy( &(mutex) );
   for( cont = 0 ; cont < QUANT ; cont++ )
   {
      // printf("destruindo as threads ---------------------------\n");
      pthread_mutex_destroy( &(mux_filo[cont]) );
   }
   pthread_exit( NULL );
   // printf("acabou de destruir --------------------------\n");
   return EXIT_SUCCESS;
}