#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_BUFFER 5
#define MAX_PROD 10

void Produce( void *ptr ); 
void Consume( void *ptr ); 

sem_t mutex, espacios, productos;
int buffer[TAM_BUFFER];
int a_vaciar=0, a_llenar=0;

int main()
{ 
    int i, n, m;
    
    pthread_t HiloProd, HiloCons;
    
     /* inicializa el la semilla aleatoria */
    srand ( time(NULL) );

    sem_init(&mutex,0,1);
    sem_init(&espacios,0,TAM_BUFFER);
    sem_init(&productos,0,0);

    /* Se crea el hilo productor */
    pthread_create( &HiloProd, NULL,(void *) &Produce, NULL);
                
    /* Se crea el hilo consumidor */
    pthread_create(&HiloCons, NULL,  (void *) &Consume, NULL);

    /* El hilo padre espera a que terminen los hilos hijos */
    pthread_join(HiloCons, NULL);
    pthread_join(HiloProd, NULL);

    /* Se destruyen los semaforos */
    sem_destroy(&mutex);
    sem_destroy(&espacios);
    sem_destroy(&productos);
    
    return 0;

}


/* 
** 
*/
void Produce( void *ptr ) 
{ 
     int  i, prod, indice; 
     
     for (i = 0; i < MAX_PROD ; i++) 
         {  /* Se genera el producto */
            prod = rand() % 5;
	    
	      /* Esperamos un espacio para colocarlo en el buffer */
	      sem_wait(&espacios);
	      
	      /* Pedimos el derecho de acceso exclusivo al buffer */
	      sem_wait(&mutex);
		
			/* Modificamos el buffer */
			buffer[a_llenar] = prod;
			indice = a_llenar;
			a_llenar = (a_llenar+1) % TAM_BUFFER;
		
	      /* Se libera el derecho de acceso exclusivo al buffer*/
	      sem_post(&mutex);
	      
	      /* Se avisa que hay un producto disponible */
            sem_post(&productos);	      
	      
            printf("Productor(%d): produje Buffer[%d]:%d\n",i,indice,prod);

         } 
     pthread_exit(0); 
}  



/* 
** 
*/
void Consume( void *ptr ) 
{ 
     int  i, consumible, indice; 
     
     for (i = 0; i < MAX_PROD ; i++) 
         {  
	      /* Esperamos un producto para consumirlo */
	      sem_wait(&productos);
	      
	      /* Pedimos el derecho de acceso exclusivo al buffer */
	      sem_wait(&mutex);
		
			/* Modificamos el buffer */
			consumible = buffer[a_vaciar];
			indice = a_vaciar;
			a_vaciar = (a_vaciar+1) % TAM_BUFFER;
		
	      /* Se libera el derecho de acceso exclusivo al buffer*/
	      sem_post(&mutex);
	      
	      /* Se avisa que hay un espacio disponible  */
            sem_post(&espacios);

	      /* Se realiza el consumo */
	      printf("Consumidor (%d): Buffer[%d]:%d\n",i,indice,consumible);
	      sleep(consumible);
         } 
     pthread_exit(0); 
}  