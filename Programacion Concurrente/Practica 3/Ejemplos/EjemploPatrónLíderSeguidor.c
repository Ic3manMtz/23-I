/******************************************************************************
 * Programa ejemplo para el uso de las siguientes rutinas
 *  pthread_create: crea un hilo
 *  pthread_join: espera a que un hilo termine
 *  pthread_exit: termina la ejecución de un hilo
 *  y el patrón líder-seguidor
 * 
 * Elaboró: Elizabeth Pérez Cortés
 * 
*******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define HILOS 5
#define ITERACIONES 3

void EscribeLiderSeguidor( void *ptr);
pthread_mutex_t mi_candado = PTHREAD_MUTEX_INITIALIZER;

int main()
{ 
    int i, ids[HILOS];
    pthread_t hilos[HILOS];
    
    for(i = 0; i < HILOS; i++){
        ids[i] = i;
    	pthread_create(&hilos[i],NULL,(void *) &EscribeLiderSeguidor, (void *)(intptr_t)ids[i]);
    }

    for(i = 0;i < HILOS; i++){
	    pthread_join(hilos[i], NULL);
    }	
    
    printf("Hilo padre: todos han terminado\n");
	pthread_mutex_destroy(&mi_candado);
}


void EscribeLiderSeguidor(void *ptr){
	 
	int j, numHilo = (intptr_t) ptr;
	
	for(j=0; j<ITERACIONES; j++){
		pthread_mutex_lock(&mi_candado);		
		switch(j){
		  case 0: printf("%d: Hola!!!\n",numHilo);
			  break;
  		  case 1: printf("%d: Estoy feliz\n",numHilo);
			  break;
  		  default: printf("%d: Nos vemos pronto!!!\n",numHilo);
		}
		pthread_mutex_unlock(&mi_candado);		
	}
	pthread_exit(0);
}