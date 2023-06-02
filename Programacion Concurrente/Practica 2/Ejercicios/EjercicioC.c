#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void EscribeLiderSeguidor( void *ptr);
int menorDivisor(int);
int esPrimo(int);
int numHilos, m;
int * arreglo;
int contador;
int turno; /* VARIABLE COMPARTIDA */

int main()
{ 
    printf("Indique el tamaño M del arreglo...");
    scanf("%d",&m);
    numHilos=menorDivisor(m);

    int i, ids[numHilos],semilla;
    pthread_t hilos[numHilos];
    
    //Inicializamos el generador de numeros aleatorios
    semilla=time(NULL);
    srand(semilla);
    turno = 0;	   

    //Reservamos memoria para el arreglo
    arreglo=(int*)calloc(m,sizeof(int));

    printf("\nLos valores de M y N son: %d y %d respectivamente\n\n",m,numHilos);
    //Se llena el arreglo con numero aleatorios entre 1 y 100
    for(i=0;i<m;i++){
        arreglo[i]=(rand() % (100 - 1 + 1)) + 1;
    }

    for(i = 0; i < numHilos; i++){
        ids[i] = i;
    	pthread_create(&hilos[i],NULL,(void *) &EscribeLiderSeguidor, (void *)(intptr_t)ids[i]);
    }

    for(i = 0;i < numHilos; i++){
	    pthread_join(hilos[i], NULL);
    }	
    
    printf("\n\nHilo padre: todos han terminado\n");
    printf("\tSe encotraron %d primos en el arreglo\n\n\t",contador);
    for(i=0;i<m;i++){
        printf("%d ",arreglo[i]);
    }
    printf("\n");
}


void EscribeLiderSeguidor(void *ptr){
	int j, numHilo = (intptr_t) ptr;
    int cotaMenor, cotaMayor,i;

    while(numHilo!=turno){ };

    cotaMenor=(m/numHilos*numHilo)+1;
    cotaMayor=(m/numHilos)*(numHilo+1);
    printf("Rango de busqueda en el arreglo del hilo %d : [%d,%d]\n",numHilo,cotaMenor,cotaMayor);
    for(i=cotaMenor-1;i<cotaMayor;i++){
        if(esPrimo(arreglo[i])==1)
            contador++;
    }
	/* LIBERA EL DERECHO DE ACCESO A LA PANTALLA CEDIENDOLO AL SIGUIENTE HILO*/
    turno = (turno + 1) % numHilos;

	pthread_exit(0);
}

int menorDivisor(int m){
    int i;
	for(i = 2; i <= m; i++) {
		if((m%i) == 0){
			return i;
		}
	}
}

int esPrimo(int a){
    int i,esPrimo=0;
    for (i = 1; i <= a; i++) {
        if (a % i == 0) {
            esPrimo++;
        }
    }

    if (esPrimo == 2) {
            return 1;
    }
    else {
            return 0;
    }
}
