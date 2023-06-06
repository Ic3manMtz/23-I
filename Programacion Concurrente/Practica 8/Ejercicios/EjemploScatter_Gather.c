// Programa MPI ejemplo para el uso de
// MPI_Scatter y MPI_Gather
// El proceso 0 genera un arreglo de 40 datos y los distribuye entre 4 procesos
// incluyéndose. Cada proceso suma los datos que recibe y le regresa la suma parcial al proceso 0

#include <mpi.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define EMISOR 0
#define TAM 40

void emisor(int mi_id, int numProcesos)
{   int k = (rand() % 20) * numProcesos;
    int datosOut[k];
    int i, datosIn[k/numProcesos], res[numProcesos];

    for(i=0; i<TAM; i++)
        datosOut[i] = rand() % TAM;

    MPI_Scatter(datosOut,10,MPI_INT,datosIn, 10, MPI_INT, mi_id,MPI_COMM_WORLD);

    printf("Emisor %d: recibi\n", mi_id);

    int suma = 0;
    for(i=0; i<10; i++){
        printf("%d: arreglo[%d]:%d \n",mi_id, i,datosIn[i]);
        suma += datosIn[i];
    }

    printf("Emisor %d: mandaré %d\n", mi_id, suma);

    MPI_Gather(&suma,1,MPI_INT,res,1,MPI_INT,EMISOR,MPI_COMM_WORLD);

    suma=0;
    for(i=0; i<numProcesos; i++){
        printf("%d: res[%d]:%d \n",mi_id, i,res[i]);
        suma+=res[i];
    }
        
    printf("La suma global es: %d\n", suma);
}


void receptor(int mi_id, int numProcesos)
{   
    int k = (rand() % 20) * numProcesos;
    int i, datosIn[k/numProcesos];

    MPI_Scatter(datosIn,10,MPI_INT,datosIn,10, MPI_INT, EMISOR,MPI_COMM_WORLD);

    printf("Receptor %d: recibi\n", mi_id);

    int suma = 0;
    for(i=0; i<10; i++){
        printf("%d: arreglo[%d]:%d \n",mi_id, i,datosIn[i]);
        suma += datosIn[i];
    }

    printf("Receptor %d: mandaré %d\n", mi_id, suma);

    MPI_Gather(&suma,1,MPI_INT,&suma,1,MPI_INT,EMISOR,MPI_COMM_WORLD);
}

int main(int argc, char *argv[])
{
    int rank, size;
    
    srand(time(NULL));
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
 
    if ( rank == EMISOR)
        emisor(rank, size);
    else
        receptor(rank, size);

    MPI_Finalize();
    return 0;
}
