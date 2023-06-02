#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_BUFFER 5
#define MAX_PROD 10

void ProduceNumeros(void * ptr);
void ConsumeNumeros(void * ptr);
void ConsumePares(void * ptr);
int Collatz(int);

struct ParCollatz{
    int numero;
    int longitud;
};

int bufferNumeros[TAM_BUFFER];
struct ParCollatz bufferPares[TAM_BUFFER];
sem_t espaciosNumeros, numeros,espaciosPares, pares;
int sacarNumero = 0, ponerNumero = 0;
int sacarPar = 0, ponerPar = 0;
int main(){

    pthread_t generadorNumeros,analizadorNumeros,analizadorPares;

    sem_init(&espaciosNumeros, 0, TAM_BUFFER);
    sem_init(&espaciosPares, 0 , TAM_BUFFER);
    sem_init(&numeros, 0, 0);
    sem_init(&pares, 0, 0);

    pthread_create(&generadorNumeros,NULL,(void*)&ProduceNumeros,NULL);
    pthread_create(&analizadorNumeros,NULL,(void*)&ConsumeNumeros,NULL);
    pthread_create(&analizadorPares,NULL,(void*)&ConsumePares,NULL);
    
    pthread_join(generadorNumeros,NULL);
    pthread_join(analizadorNumeros,NULL);
    pthread_join(analizadorPares,NULL);
    return 0;
}

void ProduceNumeros(void * ptr){
    int numero;
    do{
        printf("\nAnote el número a analizar, para terminar ingrese -1...");
        scanf("%d",&numero);
        sem_wait(&espaciosNumeros);
        bufferNumeros[ponerNumero] = numero;
        ponerNumero = (ponerNumero + 1) % TAM_BUFFER;
        sem_post(&numeros);
    }while(numero > 0);
    pthread_exit(0);
}

void ConsumeNumeros(void * ptr){
    int longitud, numero;
    struct ParCollatz nuevoPar;

    do{
        sem_wait(&numeros);
        numero = bufferNumeros[sacarNumero];
        sacarNumero = (sacarNumero + 1) % TAM_BUFFER;
        sem_post(&espaciosNumeros);

        if(numero == -1){
            nuevoPar.numero = -1;
            nuevoPar.longitud = -1;
        }else{
            longitud = Collatz(numero);
            nuevoPar.numero = numero;
            nuevoPar.longitud = longitud;
        }

        sem_wait(&espaciosPares);
        bufferPares[ponerPar] = nuevoPar;
        ponerPar = (ponerPar + 1) % TAM_BUFFER;
        sem_post(&pares);

    }while(numero >0);
    pthread_exit(0);
}

void ConsumePares(void * ptr){
    struct ParCollatz maximo, terminar, aux;
    maximo.longitud = 0;
    maximo.numero = 0;
    do{
        sem_wait(&pares);
        aux = bufferPares[sacarPar];
        sacarPar = (sacarPar + 1) % TAM_BUFFER;
        sem_post(&espaciosPares);

        terminar.numero = aux.numero;
        terminar.longitud = aux.longitud;

        if(aux.longitud > maximo.longitud){
            maximo.numero = aux.numero;
            maximo.longitud = aux.longitud;
        }
    }while(terminar.numero == -1 && terminar.longitud == -1);

    printf("\nLa secuencia de Collatz más larga fue %d con el número %d\n",maximo.longitud,maximo.numero);
    pthread_exit(0);
}

int Collatz(int num){
    int longitud = 1;

    while(num != 1){
        longitud += 1;

        if (num % 2 == 0) {
            num = num / 2;
        } else {
            num = 3 * num + 1;
        }
    }
    return longitud;
}