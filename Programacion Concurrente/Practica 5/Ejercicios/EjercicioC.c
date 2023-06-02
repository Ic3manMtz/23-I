#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define N 6
#define NUMMAT 5

void CalcularMaximo(void *ptr);
void CalcularMinimo(void *ptr);
void LlenarMatriz();
void MostrarMatriz();

pthread_barrier_t MaximosListos, MostrarResultados;

int matriz[N][N];
int resultados[N];

int main(int argc, char const *argv[]){
    int id[N],i;
    pthread_t Maximos[N],Minimo;

    pthread_barrier_init(&MaximosListos,NULL,N+1);
    pthread_barrier_init(&MostrarResultados,NULL,N+1);

    srand(time(NULL));
    LlenarMatriz();

    for(i=0;i<N;i++){
        id[i]=i;
        pthread_create(&Maximos[i],NULL,(void*)&CalcularMaximo,(void*)(intptr_t)id[i]);
    }
    pthread_create(&Minimo,NULL,(void*)&CalcularMinimo,NULL);

    pthread_join(Minimo,NULL);
    for(i=0;i<N;i++){
        pthread_join(Maximos[i],NULL);
    }
    pthread_barrier_destroy(&MaximosListos);
    pthread_barrier_destroy(&MostrarResultados);
    return 0;
}

void CalcularMaximo(void *ptr){
    int id,i,j,maximo;
    id=(intptr_t)ptr;
    
    for(i=0;i<NUMMAT;i++){
            maximo=0;
        for(j=0;j<N;j++){
            if(matriz[id][j]>maximo)
                maximo=matriz[id][j];
        }
        resultados[id]=maximo;
        pthread_barrier_wait(&MaximosListos);
        pthread_barrier_wait(&MostrarResultados);
    }

    pthread_exit(0);
}

void CalcularMinimo(void *ptr){
    int i, j, minimo;

    for(i=0;i<NUMMAT;i++){
        pthread_barrier_wait(&MaximosListos);
            minimo=51;

        printf("\nMaximos de cada renglon\n"); fflush(stdout);
        for(j=0;j<N;j++){
            printf("\t|%d|\n",resultados[j]); fflush(stdout);
        }
        for(j=0;j<N;j++){
            if(resultados[j]<minimo)
                minimo=resultados[j];
        }
        printf("\n  El mínimo de los máximos es %d\n",minimo);
        if(i<NUMMAT-1)
            LlenarMatriz();
        pthread_barrier_wait(&MostrarResultados);
    }

    pthread_exit(0);
}

void LlenarMatriz(){
    int i,j;
    char car = '-';
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            matriz[i][j]=rand()%50;
        }
    }
    printf("+------------------------------------------------+");
    printf("\n\t\tMatriz nueva \n\n");
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

