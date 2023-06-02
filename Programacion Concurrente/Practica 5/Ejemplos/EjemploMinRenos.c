#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define N 7

void RutinaReno( void *ptr ); 
void RutinaSanta(void *ptr);

pthread_barrier_t EntregarJuguetes;

int main()
{ 
    int idc[N], i,j;
    pthread_t Renos[N], Santa;
    
    /* inicializa el la semilla aleatoria */
    srand ( time(NULL) );
     /* Se inicializa la barrera */
    pthread_barrier_init(&EntregarJuguetes,NULL,N+1);

     /* Se crean los hilos renos */     
    for (i = 0; i < N; i++){
      idc[i] = i;
      pthread_create(&Renos[i], NULL,  (void *) &RutinaReno, (void *)(intptr_t)idc[i]);
    }
    pthread_create(&Santa, NULL, (void*)&RutinaSanta, NULL);

    /* El hilo padre espera a que terminen los hilos hijos */
    pthread_join(Santa,NULL);
    for (i = 0; i < N; i++)
      pthread_join(Renos[i], NULL);
      
    /* Se destruye la barrera */
    pthread_barrier_destroy(&EntregarJuguetes);
    
    return 0;
}

void RutinaReno( void *ptr ){ 
    int mi_id, i, tiempo;      
    mi_id = (intptr_t) ptr; 
  
    tiempo = rand()%10;
    printf("Reno %d vacacionare %d unidades de tiempo\n", mi_id, tiempo); fflush(stdout);
    sleep(tiempo);
    printf("Reno %d: YA LLEGUE!!\n",mi_id); fflush(stdout);
    pthread_barrier_wait(&EntregarJuguetes);
    printf("Reno %d vamonos a entregar juguetes!\n", mi_id); fflush(stdout);
    pthread_exit(0); 
}  

void RutinaSanta(void *ptr){
    int mi_id, i, tiempo;      
    mi_id = (intptr_t) ptr; 
  
    tiempo = rand()%10;
    printf("Santa: Duermo mientras los otros vacacionan\n\n"); fflush(stdout);
    sleep(tiempo);

    printf("Santa: Espero a que lleguen los renos\n"); fflush(stdout);

    pthread_barrier_wait(&EntregarJuguetes);
    printf("Santa: ¡¡¡Vamos a entregar juguetes!!!"); fflush(stdout);
    pthread_exit(0); 
}