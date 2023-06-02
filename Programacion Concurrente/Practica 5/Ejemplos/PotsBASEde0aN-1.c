/* Programa ejemplo Barreras
 * 
 * Una barrera es un mecanismo de sincronización que se usa 
 * para detectar cuando un grupo de n hilos han alcanzado 
 * un determinado punto en la ejecución. 
 * Una barrera se inicializa con el número de hilos que se requiere lleguen a ella
 * Un hilo que espera en una barrera se bloqueará.
 * Cuando el n-ésimo llegue, todos se desbloquean.
 * 
 * En este programa N hilos calculan BASE^i donde i es el número del hilo, es decir, 
 * el hilo 0 calcula BASE^0
 * el hilo 1 calcula BASE^1
 * el hilo 2 calcula BASE^2
 * ...
 * el hilo N-1 calcula BASE^N-1
 *
 * y solamente cuando todos los hilos han terminado su cálculo, el hilo impresor imprime las 
 * potencias
 *
 * Observe el comportamiento del programa antes y después de eliminar los comentarios en las líneas 
 * que contienen la primitiva de espera en la barrera.
 *
 */ 

#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 10
#define MAX 5
#define DURACION_VUELTA 5
#define BASE 2

void Calcula( void *ptr ); 
void Imprime( void *ptr ); 

pthread_barrier_t ResultadoListo;
int Resultados[N];

int main()
{ 
    int idc[N], i,j;
    pthread_t Calculador[N], Impresor;
    
    /* inicializa el la semilla aleatoria */
    srand ( time(NULL) );
    
     /* Se inicializa la barrera */
    pthread_barrier_init(&ResultadoListo,NULL,N+1);

    for (i = 0; i < N; i++) Resultados[i] = 0;
    
    /* Se crea el hilo Impresor */
    pthread_create(&Impresor, NULL, (void *) &Imprime, NULL);
    
    /* Se crean los hilos que calculan */     
    for (i = 0; i < N; i++){
      idc[i] = i;
      pthread_create(&Calculador[i], NULL,  (void *) &Calcula, (void *)(intptr_t)idc[i]);
    }

    /* El hilo padre espera a que terminen los hilos hijos */
    pthread_join(Impresor, NULL);
    for (i = 0; i < N; i++)
      pthread_join(Calculador[i], NULL);

    
    /* Se destruye la barrera */
    pthread_barrier_destroy(&ResultadoListo);

    return 0; 
}


/* 
** 
*/
void Calcula( void *ptr ) 
{ 
    int mi_id, i;      
    mi_id = (intptr_t) ptr; 
    Resultados[mi_id] = 1;
    
    sleep(rand()%10);
    
    for(i = 0; i < mi_id; i++)
      Resultados[mi_id] *= BASE;
      
    printf("Calculador %d dejo %d \n", mi_id, Resultados[mi_id]);	    fflush(stdout);
    
    /* Esperamos en la barrera a que se lo lleve el impresor */     
    //pthread_barrier_wait(&ResultadoListo);
      
    pthread_exit(0); 
}  



/* 
** 
*/
void Imprime( void *ptr ) 
{ 
    int i,j;      
    printf("Impresor \n");	    fflush(stdout);
    /* Espero a que todos tengan un resultado listo*/
    //pthread_barrier_wait(&ResultadoListo);

    /* Lo imprimo */
    printf("%d^i:",BASE);
    for (j = 0; j < N; j++) printf("\t%d,",Resultados[j]);
    printf("\n");
  
    
    pthread_exit(0); 
}  