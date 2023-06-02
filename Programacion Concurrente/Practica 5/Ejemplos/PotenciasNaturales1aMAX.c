/* Programa ejemplo Barreras
 * 
 * En este programa hay N hilos que calculan, cada uno, las potencias de
 * su identificador desde 1 hasta MAX. También hay un hilo impresor que cuando
 * todos los hilos han calculado una potencia, la imprime. 
 * 
 */ 

#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define N 10
#define MAX 5

void Calcula( void *ptr ); 
void Imprime( void *ptr ); 

pthread_barrier_t ResultadoListo, CeldaLista;
int Resultados[N];

int main(){ 
    int idc[N], i;
    pthread_t Calculador[N], Impresor;
    
    /* Se inicializan las barreras */
    pthread_barrier_init(&ResultadoListo,NULL,N+1);
    pthread_barrier_init(&CeldaLista,NULL,N+1);

    for (i = 0; i < N; i++) Resultados[i] = 1;

    /* Se crean los hilos que calculan */     
    for (i = 0; i < N; i++){
      idc[i] = i+1;
      pthread_create(&Calculador[i], NULL,  (void *) &Calcula, (void *)(intptr_t)idc[i]);
    }

    /* Se crea el hilo Impresor */
    pthread_create(&Impresor, NULL, (void *) &Imprime, NULL);

    /* El hilo padre espera a que terminen los hilos hijos */
    pthread_join(Impresor, NULL);
    for (i = 0; i < N; i++)
      pthread_join(Calculador[i], NULL);

    
    /* Se destruyen las barreras */
    pthread_barrier_destroy(&ResultadoListo);
    pthread_barrier_destroy(&CeldaLista);
    
    return 0;

}

void Calcula( void *ptr ){ 
    int mi_id, i;      
    mi_id = (intptr_t) ptr; 
  
    printf("Calculador %d \n", mi_id);	    fflush(stdout);

    for(i = 0; i < MAX; i++){
      Resultados[mi_id-1] *= mi_id;
      /* Colocamos el resultado y esperamos a que todos los demás terminen */
      pthread_barrier_wait(&ResultadoListo);
      /* Esperamos a que el impresor haya terminado de imprimir para colocar ahí mismo la siguiente potencia*/
      pthread_barrier_wait(&CeldaLista);
    }
    
    pthread_exit(0); 
}  

void Imprime( void *ptr ){ 
    int i,j;      

    printf("Impresor \n");	    fflush(stdout);

    for(i = 0; i < MAX; i++){
      /* Espero a que todos tengan un resultado listo*/
      pthread_barrier_wait(&ResultadoListo);
      
      /* Lo imprimo */
      printf("x^%d:",i+1);
      for (j = 0; j < N; j++) printf("\t%d,",Resultados[j]);
      printf("\n");

      /* Desbloqueo a los que estan esperando por la celda lista */
      pthread_barrier_wait(&CeldaLista);
    }

    
    pthread_exit(0); 
}  
