#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAM_BUFFER 5
#define NUM_TAXIS 4
#define MAX_PROD 10

void Produce(void * ptr);
void Consume(void * ptr);

struct Viaje{
    int id;
    int distancia;
};

sem_t sem_taxis, espacios, viajes;
struct Viaje buffer[TAM_BUFFER];
int a_vaciar = 0, a_llenar = 0;
int registroViajes[NUM_TAXIS][2];

int main(){
    int i, idMasViajes, mayorViajes = 0, idMasIngresos, mayorIngreso = 0;
    int idTaxis[NUM_TAXIS];
    pthread_t servidor, hiloTaxis[NUM_TAXIS];
    srand(time(NULL));

    sem_init(&sem_taxis,0,1);
    sem_init(&espacios,0,TAM_BUFFER);
    sem_init(&viajes,0,0);

    pthread_create(&servidor, NULL, (void*)&Produce,NULL);

    for(i = 0;i < NUM_TAXIS;i++){
        idTaxis[i]=i;
        pthread_create(&hiloTaxis[i],NULL,(void*)&Consume,(void*)(intptr_t)idTaxis[i]);
    }

    pthread_join(servidor,NULL);
    for(i = 0;i < NUM_TAXIS;i++)
        pthread_join(hiloTaxis[i],NULL);

    printf("\nEn total se atendieron %d viajes", MAX_PROD);
    for(i = 0;i < NUM_TAXIS;i++){
        if(registroViajes[i][0] > mayorViajes){
            mayorViajes = registroViajes[i][0];
            idMasViajes = i;
        }
        if(registroViajes[i][1] > mayorIngreso){
            mayorIngreso = registroViajes[i][1];
            idMasIngresos = i;
        }
    }

    printf("\nEl taxi que más viajes atendió fue %d con %d viajes",idMasViajes, mayorViajes);
    printf("\nEl taxi que más ingresos generó fue %d con %d pesos\n",idMasIngresos, mayorIngreso);

    sem_destroy(&sem_taxis);
    sem_destroy(&espacios);
    sem_destroy(&viajes);

    return 0;
}

void Produce(void * ptr){
    int i;

    for(i = 0;i < MAX_PROD;i++){
        struct Viaje producto;
        producto.id = i + 1;
        producto.distancia = rand() % 100 + 1;
        sem_wait(&espacios);
        buffer[a_llenar] = producto;
        a_llenar = (a_llenar + 1) % TAM_BUFFER;
        sem_post(&viajes);
    }
    for(i = 0;i < NUM_TAXIS;i++){
        struct Viaje terminar;
        terminar.id = -1;
        terminar.distancia = -1;
        sem_wait(&espacios);
        buffer[a_llenar] = terminar;
        a_llenar = (a_llenar + 1) % TAM_BUFFER;
        sem_post(&viajes);
    }
    pthread_exit(0);
}

void Consume(void * ptr){
    int viajesAtendidos = 0, ganancias = 0, numHilo = (intptr_t) ptr, distancia = 0, esFinal = 0;
    struct Viaje viaje;

    do{
        sem_wait(&viajes);
        sem_wait(&sem_taxis);
        viaje = buffer[a_vaciar];
        a_vaciar = (a_vaciar + 1) % TAM_BUFFER;
        sem_post(&sem_taxis);
        sem_post(&espacios);

        if(viaje.id == -1)
            break;

        esFinal = viaje.id;
        distancia = viaje.distancia;
        printf("Soy el taxi %d, voy a dormir\n",numHilo);
        sleep(distancia/10);
        ganancias += distancia * 10;
        viajesAtendidos += 1;
    }while(esFinal > 0);

    registroViajes[numHilo][0] = viajesAtendidos;
    registroViajes[numHilo][1] = ganancias;
    pthread_exit(0);
}