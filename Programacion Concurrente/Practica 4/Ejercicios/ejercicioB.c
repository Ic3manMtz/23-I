#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_BUFFER 5
#define MAX_PROD 10

void Produce( void *ptr ); 
void Consume( void *ptr ); 

sem_t sem_consumidor, sem_productor, espacios, productos;
int buffer[TAM_BUFFER];
int a_vaciar=0, a_llenar=0;

int main()
{ 
    int i, n, m;
    int numConsumidores, numProductores;

    printf("Indique el número de consumidores y productores...");
    scanf("%d",&numConsumidores);
    numProductores = numConsumidores;    
    int idConsumidores[numConsumidores];
    int idProductores[numProductores];
    
    pthread_t hiloProds[numProductores], hiloCons[numConsumidores];
    
     /* inicializa el la semilla aleatoria */
    srand ( time(NULL) );

    sem_init(&sem_productor,0,1);
    sem_init(&sem_consumidor,0,1);
    sem_init(&espacios,0,TAM_BUFFER);
    sem_init(&productos,0,0);

    /* Se crea el hilo productor */
    for(i=0;i<numProductores;i++){
        idProductores[i]=i+1;
        pthread_create( &hiloProds[i], NULL, (void *) &Produce, (void *)(intptr_t)idProductores[i]);
    }

    /* Se crea el hilo consumidor */
    for(i=0;i<numConsumidores;i++){
        idConsumidores[i]=i+1;
        pthread_create(&hiloCons[i], NULL, (void *) &Consume, (void *)(intptr_t)idConsumidores[i]);
    }
        

    /* El hilo padre espera a que terminen los hilos hijos */
    for(i=0;i<numConsumidores;i++)
        pthread_join(hiloCons[i], NULL);
        
    for(i=0;i<numProductores;i++)
        pthread_join(hiloProds[i], NULL);

    /* Se destruyen los semaforos */
    sem_destroy(&sem_productor);
    sem_destroy(&sem_consumidor);
    sem_destroy(&espacios);
    sem_destroy(&productos);
    
    return 0;

}

void Produce( void *ptr ) 
{ 
    int  i, prod, indice, numHilo = (intptr_t) ptr; 

    for (i = 0; i < MAX_PROD ; i++){  
        /* Se genera el producto */
        prod = rand() % 5;
	    /* Esperamos un espacio para colocarlo en el buffer */
        sem_wait(&espacios);
        /* Pedimos el derecho de acceso exclusivo al buffer */
        sem_wait(&sem_productor);	
		/* Modificamos el buffer */
		buffer[a_llenar] = prod;
		indice = a_llenar;
		a_llenar = (a_llenar+1) % TAM_BUFFER;	
        /* Se libera el derecho de acceso exclusivo al buffer*/
        sem_post(&sem_productor);  
        /* Se avisa que hay un producto disponible */
        sem_post(&productos);	      
        printf("Productor(%d): produje Buffer[%d]:%d\n",numHilo,indice,prod);
    } 
    pthread_exit(0); 
}  

void Consume( void *ptr ){ 
    int  i, consumible, indice, numHilo = (intptr_t) ptr; 
    for (i = 0; i < MAX_PROD ; i++){  
	    /* Esperamos un producto para consumirlo */
        sem_wait(&productos);  
	    /* Pedimos el derecho de acceso exclusivo al buffer */
        sem_wait(&sem_consumidor);
		/* Modificamos el buffer */
		consumible = buffer[a_vaciar];
		indice = a_vaciar;
		a_vaciar = (a_vaciar+1) % TAM_BUFFER;
        /* Se libera el derecho de acceso exclusivo al buffer*/
        sem_post(&sem_consumidor);
        /* Se avisa que hay un espacio disponible  */
        sem_post(&espacios);
	    /* Se realiza el consumo */
        printf("Consumidor (%d): Buffer[%d]:%d\n",numHilo,indice,consumible);
        sleep(consumible);
    } 
    pthread_exit(0); 
}  

