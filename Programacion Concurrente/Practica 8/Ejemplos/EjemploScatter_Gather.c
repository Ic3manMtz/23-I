// Programa MPI ejemplo para el uso de
// MPI_Scatter y MPI_Gather
// El proceso 0 genera un arreglo de 40 datos y los distribuye entre 4 procesos
// incluyéndose. Cada proceso suma los datos que recibe y le regresa la suma parcial al proceso 0

#include <mpi.h>
#include <stdio.h>
#define EMISOR 0
#define TAM 40

void emisor(int mi_id)
{   int datosOut[TAM];
    int i, datosIn[10], res[4];

    for(i=0; i<TAM; i++)
        datosOut[i] = i;

    MPI_Scatter(datosOut,10,MPI_INT,datosIn, 10, MPI_INT, mi_id,MPI_COMM_WORLD);

    printf("Emisor %d: recibi\n", mi_id);

    int suma = 0;
    for(i=0; i<10; i++){
        printf("%d: arreglo[%d]:%d \n",mi_id, i,datosIn[i]);
        suma += datosIn[i];
    }

    printf("Emisor %d: mandaré %d\n", mi_id, suma);

    MPI_Gather(&suma,1,MPI_INT,res,1,MPI_INT,EMISOR,MPI_COMM_WORLD);

    for(i=0; i<4; i++)
        printf("%d: res[%d]:%d \n",mi_id, i,res[i]);

}


void receptor(int mi_id)
{   int i, datosIn[10];

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
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
 
    if ( rank == EMISOR)
        emisor(rank);
    else
        receptor(rank);

    MPI_Finalize();
    return 0;
}
