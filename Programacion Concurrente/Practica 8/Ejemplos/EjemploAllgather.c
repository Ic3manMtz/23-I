// Programa MPI ejemplo para el uso de
// MPI_Allgather
// Cada proceso le manda su id a los demás y todos los procesos imprimen lo
// que recibieron.

#include <mpi.h>
#include <stdio.h>

void emisor_receptor(int mi_id, int num_proc)
{   int datosOut;
    int i, datosIn[num_proc];

    datosOut = mi_id;
    printf("Proceso %d: mandaré %d\n", mi_id, datosOut);

    MPI_Allgather(&datosOut,1,MPI_INT,datosIn,1, MPI_INT,MPI_COMM_WORLD);

    for(i=0; i<num_proc; i++)
        printf("Proceso %d: recibi datosIn[%d]=%d\n", mi_id,i,datosIn[i]);


}


int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global

    emisor_receptor(rank, size);

    MPI_Finalize();
    return 0;
}
