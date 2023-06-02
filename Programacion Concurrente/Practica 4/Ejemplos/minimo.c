#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define  TAM 5

void Lee( void *ptr ); 
void Procesa( void *ptr ); 

sem_t recursos;
int dato[TAM];

int main()
{ 
    int i, n, m;
    
    pthread_t thread1;

    sem_init(&recursos,0,TAM); //Se inicializa el semáforo en 0
    
    /* Se crea el hilo */
    pthread_create( &thread1, NULL,  
                    (void *) &Lee, (void *)(intptr_t)TAM);
   
    /* El hilo padre espera a que termine el  hilo que creó */
    pthread_join(thread1, NULL);
   
    /* Se destruye el semaforo */
    sem_close(&recursos);
    return 0;

}


/* 
*/
void Lee( void *ptr ) 
{ 
     int iteraciones, i; 
     iteraciones = (intptr_t) ptr; 
     for (i = 0; i < iteraciones ; i++) 
         {  
            sem_wait(&recursos);
            printf("Lector: Dame el siguiente número a procesar:");
		    scanf("%d",&dato[i]);
            printf("Lector: Recibi %d\n", dato[i]);
            
         } 
     pthread_exit(0); 
}  


