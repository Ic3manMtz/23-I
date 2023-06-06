// Programa MPI ejemplo de uso del MPI_Bcast
// El proceso 0 lee k del teclado y lo difunde a
// todos los demás para que sumen k veces su id

#include <mpi.h>
#include <stdio.h>
#define EMISOR 0


void emisor(int mi_id)
{   int k;

    printf("¿Cuantos datos quieres que sumen?\n");
    scanf("%d",&k);

    MPI_Bcast(&k,1,MPI_INT,mi_id,MPI_COMM_WORLD);

    printf("Emisor: mande k=%d\n", k);

    int i,suma=0;

    for(i=0; i<k; i++)
        suma += mi_id;

    printf("Proceso %d: mi suma es %d\n", mi_id, suma);

}


void receptor(int mi_id)
{   int k;


    MPI_Bcast(&k,1,MPI_INT,EMISOR,MPI_COMM_WORLD);

    printf("Receptor %d: recibi %d\n", mi_id, k);

    int i,suma=0;

    for(i=0; i<k; i++)
        suma += mi_id;

    printf("Proceso %d: mi suma es %d\n", mi_id, suma);
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
