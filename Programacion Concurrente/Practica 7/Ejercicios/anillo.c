
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {

  int rank, size, mensaje;
  
  MPI_Init(&argc, &argv); //Inicializamos la comunicación de los procesos
  
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank != 0) {
    MPI_Recv(&mensaje, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("El proceso %d recivió el mensaje %d del proceso %d\n", rank, mensaje, rank - 1);
  } else {
    mensaje = rank;
  }

  mensaje =  rank;
  MPI_Send(&mensaje, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    MPI_Recv(&mensaje, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("El proceso %d recibió el mensaje %d del proceso %d\n", rank, mensaje, size - 1);
  }
  MPI_Finalize();
}

