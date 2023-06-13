#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_N 10  // Máximo tamaño del tablero
#define NUM_THREADS 4  // Número de hilos

int solutions[MAX_N][MAX_N];  // Matriz para almacenar las soluciones encontradas
int num_solutions = 0;  // Número de soluciones encontradas
int n;  // Tamaño del tablero
pthread_mutex_t mutex;

// Función para comprobar si una reina puede ser colocada en la posición (row, col)
bool isSafe(int row, int col) {
    // Comprobar si hay otra reina en la misma columna
    for (int i = 0; i < row; i++) {
        if (solutions[i][col] == 1) {
            return false;
        }
    }

    // Comprobar si hay otra reina en la diagonal superior izquierda
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (solutions[i][j] == 1) {
            return false;
        }
    }

    // Comprobar si hay otra reina en la diagonal superior derecha
    for (int i = row, j = col; i >= 0 && j < n; i--, j++) {
        if (solutions[i][j] == 1) {
            return false;
        }
    }

    return true;
}

// Función para resolver el problema de las n-reinas utilizando backtracking
void solveNQueens(int row) {
    if (row == n) {
        pthread_mutex_lock(&mutex);

        // Se encontró una solución
        num_solutions++;
        printf("Solucion %d:\n", num_solutions);

        // Mostrar la solución encontrada
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%d ", solutions[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        pthread_mutex_unlock(&mutex);

        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            // Colocar una reina en la posición (row, col)
            solutions[row][col] = 1;

            // Resolver para la siguiente fila
            solveNQueens(row + 1);

            // Eliminar la reina de la posición (row, col) para volver a intentar con otras columnas
            solutions[row][col] = 0;
        }
    }
}

// Función para ejecutar la función solveNQueens en paralelo utilizando hilos
void* solveNQueensParallel(void* arg) {
    int row = *((int*)arg);
    solveNQueens(row);

    pthread_exit(NULL);
}

int main() {
    printf("Ingrese el tamano del tablero (n): ");
    scanf("%d", &n);

    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[NUM_THREADS];
    int rows_per_thread = n / NUM_THREADS;

    // Crear hilos para resolver el problema de las n-reinas en paralelo
    for (int i = 0; i < NUM_THREADS; i++) {
        int start_row = i * rows_per_thread;
        int end_row = start_row + rows_per_thread - 1;

        // El último hilo se encarga de las filas restantes
        if (i == NUM_THREADS - 1) {
            end_row = n - 1;
        }

        int* thread_arg = malloc(sizeof(int));
        *thread_arg = start_row;

        pthread_create(&threads[i], NULL, solveNQueensParallel, (void*)thread_arg);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Se encontraron %d soluciones en total.\n", num_solutions);

    pthread_mutex_destroy(&mutex);

    return 0;
}
