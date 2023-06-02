/****************************************************************
 * Programa ejemplo para el uso de las siguientes rutinas
 *  pthread_create: crea un hilo
 *  pthread_join: espera a que un hilo termine
 *  pthread_exit: termina la ejecución de un hilo
 *  
 * Elaboró: Elizabeth Pérez Cortés
 * 
 * **************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define HILOS 4
#define ITERACIONES 3

void Escribe( void *ptr);  

int main()
{   
    int semilla;
    int i, ids[HILOS];
    pthread_t hilos[HILOS];
    
    /* Inicializamos el generador de numeros aleatorios */
    semilla = time(NULL);
    srand(semilla);
    
    for(i = 0; i < HILOS; i++){  
	ids[i] = i;
    	pthread_create(&hilos[i],NULL,(void *) &Escribe,(void *)(intptr_t)ids[i]);
    }

    for(i = 0;i < HILOS; i++){
	    pthread_join(hilos[i], NULL);
    }	
    
    printf("Hilo padre: todos han terminado\n");
}


void Escribe(void *ptr){
	int j, numHilo = (intptr_t) ptr;
	
	for(j=0; j<ITERACIONES; j++){
		switch(j){
		  case 0: printf("%d: Hola!!!\n",numHilo);
			  break;
  		  case 1: printf("%d: Estoy feliz\n",numHilo);
			  break;
  		  default: printf("%d: Nos vemos pronto!!!\n",numHilo);
			  break;
		}	
		//sleep(random()%2);
	}
	pthread_exit(0);
}