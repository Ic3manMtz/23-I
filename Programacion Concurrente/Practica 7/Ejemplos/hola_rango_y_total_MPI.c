// Programa ejemplo MPI para obtener el total de procesos y el rango de cada uno

#include "mpi.h"
#include <stdio.h>
 
int main(int argc, char *argv[])
{
    int rank, size, name_len;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
 
    MPI_Init(&argc, &argv); // Inicializacion del entorno MPI

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero de procesos en el comunicador global
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos la identificacion de nuestro proceso en el comunicador global
    MPI_Get_processor_name(processor_name, &name_len);

    printf("¡Hola Mundo desde el host:%s de tamaño %d. Soy el proceso %d de %d que somos!\n",processor_name, name_len, rank, size);
 
    MPI_Finalize();

    return 0;
}
