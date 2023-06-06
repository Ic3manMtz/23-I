#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, size, N;
    int *matrix, *row_maxs, *all_maxs, *row_mins, *all_mins;
    int i, j, max_of_mins, min_of_maxs;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    srand(time(NULL) + rank);  // Inicializar la semilla aleatoria con un offset único para cada proceso

    // Generar la matriz de enteros aleatorios
    N = size;
    matrix = (int *)malloc(N * N * sizeof(int));

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            matrix[i * N + j] = rand() % 100;  // Generar números aleatorios en el rango [0, 99]
        }
    }

    // Imprimir la matriz generada por todos los procesos
    for (i = 0; i < size; i++) {
        MPI_Barrier(MPI_COMM_WORLD);  // Esperar a que todos los procesos lleguen a este punto antes de imprimir
        if (rank == i) {
            printf("Proceso %d:\n", rank);
            for (j = 0; j < N * N; j++) {
                printf("%d ", matrix[j]);
                if ((j + 1) % N == 0) {
                    printf("\n");
                }
            }
            printf("\n");
        }
    }

    // Calcular el mínimo de los máximos de cada renglón
    row_maxs = (int *)malloc(N * sizeof(int));
    all_maxs = (int *)malloc(N * sizeof(int));

    for (i = 0; i < N; i++) {
        int row_max = 0;
        for (j = 0; j < N; j++) {
            if (matrix[i * N + j] > row_max) {
                row_max = matrix[i * N + j];
            }
        }
        row_maxs[i] = row_max;
    }

    MPI_Reduce(row_maxs, all_maxs, N, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    // Calcular el máximo de los mínimos de la matriz (solo en el proceso 0)
    if (rank == 0) {
        min_of_maxs = all_maxs[0];
        for (i = 1; i < N; i++) {
            if (all_maxs[i] < min_of_maxs) {
                min_of_maxs = all_maxs[i];
            }
        }
    }

    // Imprimir el resultado final (solo en el proceso 0)
    if (rank == 0) {
        printf("El mínimo de los máximos de cada renglón es: %d\n", min_of_maxs);
    }

    // Liberar memoria
    free(matrix);
    free(row_maxs);
    free(all_maxs);

    MPI_Finalize();
    return 0;
}
