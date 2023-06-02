/******************************************************************************
 * Programa ejemplo para el uso de los mutex de la librería
 * pthread. 
 * El programa calcula la sumatoria de cuadrados desde i=1 hasta N
 * 
 * Elaboró: Elizabeth Pérez Cortés
 * 
*******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define HILOS 5

void Aporta( void *ptr);
// Se declara e inicializa el candado con los parámetros por defecto (abierto)
pthread_mutex_t mi_candado = PTHREAD_MUTEX_INITIALIZER; 
int total;

int main()
{ 
    int i, ids[HILOS];
    pthread_t hilos[HILOS];
    
    total = 0;
    
    for(i = 0; i < HILOS; i++){
        ids[i] = i+1;
    	pthread_create(&hilos[i],NULL,(void *) &Aporta, (void *)(intptr_t)ids[i]);
    }

    for(i = 0;i < HILOS; i++){
	    pthread_join(hilos[i], NULL);
    }	
    printf("Hilo padre: el total es %d\n", total);
    
    // Se destruye el candado
    pthread_mutex_destroy(&mi_candado);
    return 0;
}


void Aporta(void *ptr){
	 
	int j, numHilo = (intptr_t) ptr;

    // Se solicita el derecho de acceso
    pthread_mutex_lock(&mi_candado);
    
        total = total + numHilo*numHilo;
        
    // Se libera el derecho de acceso
    pthread_mutex_unlock(&mi_candado);
	
	pthread_exit(0);
}