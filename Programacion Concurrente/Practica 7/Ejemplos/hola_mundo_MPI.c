// Programa ejemplo MPI en donde se inicializa y se termina el entorno.

#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI
 
    printf("¡Hola Mundo!\n");
 
    MPI_Finalize(); //Terminamos el entorno MPI
    return 0;
}
