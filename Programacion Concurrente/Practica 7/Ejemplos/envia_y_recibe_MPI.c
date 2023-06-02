// Programa ejemplo MPI en donde cada proceso se manda a sí mismo un mensaje con su rango

#include "stdio.h"
#include "mpi.h"

#define TAM 5

int main(int argc, char *argv[])
{
    int rank, i;
    MPI_Status estado;
    int buffIn[TAM];
    int buffOut[TAM];
 
    MPI_Init(&argc, &argv); // Inicializamos la comunicacion de los procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador
 
    for(i=0;i<TAM;i++) buffOut[i] = (10*i) + rank;

    //Envia y recibe mensajes
    MPI_Send(buffOut //referencia al vector de elementos a enviar
            ,TAM // tamaño del vector a enviar
            ,MPI_INT // Tipo de dato que envias
            ,rank // pid del proceso destino (YO MISMO)
            ,0 //etiqueta
            ,MPI_COMM_WORLD); //Comunicador por el que se manda
 
    MPI_Recv(buffIn // Referencia al vector donde se almacenara lo recibido
            ,TAM // tamaño del vector a recibir
            ,MPI_INT // Tipo de dato que recibe
            ,rank // pid del proceso origen del que se recibe
            ,0 // etiqueta
            ,MPI_COMM_WORLD // Comunicador por el que se recibe
            ,&estado); // estructura informativa del estado
 
    for(i=0;i<TAM;i++)  printf("Soy el proceso %d y he recibido: %d\n",rank, buffOut[i]);
 
    MPI_Finalize();
    return 0;
}
