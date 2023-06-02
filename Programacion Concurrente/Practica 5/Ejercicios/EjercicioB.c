#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define N 6

void CalcularMaximo(void *ptr);
void CalcularMinimo(void *ptr);
void LlenarMatriz();
void MostrarMatriz();
int matriz[N][N];
int resultados[N];

pthread_barrier_t EntregarMaximos;

int main(int argc, char const *argv[])
{
    printf("\n***** Ejercicio B *****\n");
    printf("\n++++Creando y llenando matriz++++");
    int id[N],i;
    pthread_t Renglones[N],Minimo;
    srand(time(NULL));
    LlenarMatriz();
    pthread_barrier_init(&EntregarMaximos,NULL,N+1);

    for(i=0;i<N;i++){
        id[i]=i;
        pthread_create(&Renglones[i],NULL,(void*)&CalcularMaximo,(void*)(intptr_t)id[i]);
    }
    pthread_create(&Minimo,NULL,(void*)&CalcularMinimo,NULL);

    pthread_join(Minimo,NULL);
    for(i=0;i<N;i++){
        pthread_join(Renglones[i],NULL);
    }
    pthread_barrier_destroy(&EntregarMaximos);
    return 0;
}

void CalcularMaximo(void *ptr){
    int id,i,maximo;
    id=(intptr_t)ptr;
    maximo=0;
    for(i=0;i<N;i++){
        if(matriz[id][i]>maximo)
            maximo=matriz[id][i];
    }
    printf("El máximo del renglón %d es %d\n",id, maximo);
    fflush(stdout);
    resultados[id]=maximo;
    pthread_barrier_wait(&EntregarMaximos);
    pthread_exit(0);
}

void CalcularMinimo(void *ptr){
    int i, minimo;
    minimo=51;
    printf("Maximos de cada renglon\n"); fflush(stdout);
    for(i=0;i<N;i++){
        printf("|%d|\n",resultados[i]); fflush(stdout);
    }
    for(i=0;i<N;i++){
        if(resultados[i]<minimo)
            minimo=resultados[i];
    }
    printf("El mínimo de los máximos es %d\n",minimo);
    pthread_barrier_wait(&EntregarMaximos);
    pthread_exit(0);
}

void LlenarMatriz(){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            matriz[i][j]=rand()%50;
        }
    }
    printf("\n++++Matriz llena++++\n\n");
    MostrarMatriz();
}

void MostrarMatriz(){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            printf(" %d\t",matriz[i][j]);
        }
        printf("\n");
    }
}

