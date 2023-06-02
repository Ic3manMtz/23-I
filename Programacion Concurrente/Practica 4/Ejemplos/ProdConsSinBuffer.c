#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <unistd.h>

void Lee( void *ptr ); 
void Procesa( void *ptr ); 

sem_t dato_listo, trabajador_listo;
int dato = 0;

int main()
{ 
    int i, n, m;
    
    pthread_t thread1, thread2;

    sem_init(&dato_listo,0,0); //Se inicializa el semáforo en 0
    sem_init(&trabajador_listo,0,1); //Se inicializa el semáforo en 1 

    /* Se crea el hilo que lee la solicitud del cliente */
    pthread_create( &thread1, NULL,  
                    (void *) &Lee, (void *)(intptr_t)4);
   
    /* Se crea el hilo que procesa la solicitud del cliente */
    pthread_create(&thread2, NULL,  
                    (void *) &Procesa, (void *)(intptr_t)4);


    /* El hilo padre espera a que terminen los hilos que creó */
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    /* Se destruye el semaforo */
    sem_close(&dato_listo);
    sem_close(&trabajador_listo);
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
            sem_wait(&trabajador_listo);
            printf("Lector: Dame el siguiente número a procesar:");
		    scanf("%d",&dato);
            printf("Lector: Recibi %d\n", dato);
            sem_post(&dato_listo);
            
         } 
     pthread_exit(0); 
}  


/* 

*/
void Procesa( void *ptr ) 
{ 
     int iteraciones, i; 
     iteraciones = (intptr_t) ptr; 
     for (i = 0; i < iteraciones ; i++) 
         {        
         sem_wait(&dato_listo);
         printf("Trabajador: procesaré %d\n", dato);
         sem_post(&trabajador_listo);
         
         }
     pthread_exit(0); 
}  