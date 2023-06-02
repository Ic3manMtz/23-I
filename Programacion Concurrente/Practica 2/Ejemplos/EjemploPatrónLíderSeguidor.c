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
int turno; /* VARIABLE COMPARTIDA */

int main()
{ 
    int i, ids[HILOS];
    pthread_t hilos[HILOS];
    
    turno = 0;	     	

    for(i = 0; i < HILOS; i++){
        ids[i] = i;
    	pthread_create(&hilos[i],NULL,(void *) &EscribeLiderSeguidor, (void *)(intptr_t)ids[i]);
    }

    for(i = 0;i < HILOS; i++){
	    pthread_join(hilos[i], NULL);
    }	
    
    printf("Hilo padre: todos han terminado\n");
}


void EscribeLiderSeguidor(void *ptr){
	 
	int j, numHilo = (intptr_t) ptr;
	
	for(j=0; j<ITERACIONES; j++){

		/* ADQUIERE DERECHO DE ACCESO A LA PANTALLA */
		while(numHilo != turno){/* espera */}; 
		
		switch(j){
		  case 0: printf("%d: Hola!!!\n",numHilo);
			  break;
  		  case 1: printf("%d: Estoy feliz\n",numHilo);
			  break;
  		  default: printf("%d: Nos vemos pronto!!!\n",numHilo);
		}
		
		/* LIBERA EL DERECHO DE ACCESO A LA PANTALLA CEDIENDOLO AL SIGUIENTE HILO*/
		turno = (turno + 1) % HILOS;
	}
	pthread_exit(0);
}