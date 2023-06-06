// Programa MPI ejemplo para el uso de
// MPI_Scatter y MPI_Reduce
// El proceso 0 genera un arreglo de 40 datos y los distribuye entre 4 procesos
// incluyéndose. Cada proceso suma los datos que recibe y después el proceso 0 mediante una
// reducción recibe y suma al mismo tiempo los resultados parciales.

#include <mpi.h>
#include <stdio.h>
#define MAESTRO 0
#define TAM 40

void maestro(int mi_id)
{   int datosOut[TAM];
    int i, suma_local, suma_global, datosIn[10];

    for(i=0; i<TAM; i++)
        datosOut[i] = i;

    MPI_Scatter(datosOut,10,MPI_INT,datosIn, 10, MPI_INT, mi_id,MPI_COMM_WORLD);

    printf("Maestro %d: recibi\n", mi_id);

    suma_local = 0;
    for(i=0; i<10; i++){
        printf("%d: arreglo[%d]:%d \n",mi_id, i,datosIn[i]);
        suma_local += datosIn[i];
    }

    printf("Maestro %d: mandaré %d\n", mi_id, suma_local);

    MPI_Reduce(&suma_local, &suma_global, 1, MPI_INT, MPI_SUM, mi_id, MPI_COMM_WORLD);

    printf("Maestro %d: suma total = %d\n", mi_id, suma_global);

}


void trabajador(int mi_id)
{   int i, suma_local, suma_global, datosIn[10];

    MPI_Scatter(datosIn,10,MPI_INT,datosIn,10, MPI_INT, MAESTRO, MPI_COMM_WORLD);

    printf("Trabajador %d: recibi\n", mi_id);

    suma_local = 0;
    for(i=0; i<10; i++){
        printf("%d: arreglo[%d]:%d \n",mi_id, i,datosIn[i]);
        suma_local += datosIn[i];
    }

    printf("Trabajador %d: mandaré %d\n", mi_id, suma_local);

    MPI_Reduce(&suma_local, &suma_global, 1, MPI_INT, MPI_SUM, MAESTRO, MPI_COMM_WORLD);
}

int main(int argc, char *argv[])
{
    int rank, size;
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
 
    if ( rank == MAESTRO)
        maestro(rank);
    else
        trabajador(rank);

    MPI_Finalize();
    return 0;
}
