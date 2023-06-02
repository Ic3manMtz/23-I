#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define TAM 10

// Prototipos
void Frecuencia( void *ptr);
void Moda(void *ptr);

//Variables compartidas
struct lims { int ini, fin;}; 
struct lims limites[2] = {{0,4},{5,9}};
int nums[TAM] = {1,4,7,2,9,5,6,3,1,2};
int frec[TAM] = {0,0,0,0,0,0,0,0,0,0};
int modas[TAM];
int k;

// Candados con los parámetros por defecto (abierto)
pthread_mutex_t mis_candados[TAM];

int main()
{ 
    int i;
    pthread_t hilo1, hilo2, hilo3;

    for(i=0;i<TAM;i++)
        pthread_mutex_init(&mis_candados[i], NULL);
    
    
    pthread_create(&hilo1,NULL,(void *) &Frecuencia, (void *)&limites[0]);
	pthread_create(&hilo2,NULL,(void *) &Frecuencia, (void *)&limites[1]);

    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    pthread_create(&hilo3,NULL,(void *) &Moda,NULL);
    pthread_join(hilo3,NULL);

    printf("Hilo padre: las frecuencias son \n\n");
    for (i=0;i<TAM; i++)
        printf("[%d]:frec[%d]\n", i+1, frec[i]);

    i=0;
    printf("\nModa\t= ");
    while(modas[i]!=0){
        printf("%d ",i+1);
        i++;
    }
    
    printf("\n");
 
    // Se destruyen los candados
    for(i=0;i<TAM;i++)
        pthread_mutex_destroy(&mis_candados[i]);

    return 0;
}

void Frecuencia(void *ptr){
	int i,j,num,cont;
	
	struct lims *mis_limites = (struct lims *) ptr;

    for(num = 1; num<=10; num++){
                cont = 0;
                for(j= (mis_limites->ini); j<= (mis_limites->fin); j++)
                    if(nums[j] == num)  
                        cont++;
                pthread_mutex_lock(&mis_candados[num-1]);
                frec[num-1] += cont;
                pthread_mutex_unlock(&mis_candados[num-1]);
    }
	pthread_exit(0);
}

void Moda(void *ptr){
    int i,j,max=0,moda;
    for (i=0;i<TAM-1;i++){
        moda=0;
        for(j=i+1;j<TAM;j++){
            if (nums[i] == nums[j]){
                moda++;
            }
        }
        if((moda>max) && (moda!=0)){
            k = 0;
            max = moda;
            modas[k] = frec[i];
            k++;
        }
        else if (moda==max){
            modas[k] = nums[i];
            k++;
        }
    }
}

