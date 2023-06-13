#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_N 10  // Máximo tamaño de la cuadrícula
#define NUM_THREADS 4  // Número de hilos

int grid[MAX_N][MAX_N];  // Cuadrícula
int n;  // Tamaño de la cuadrícula
int total_moves = 0;  // Número total de movimientos realizados
pthread_mutex_t mutex;

// Estructura de datos para representar un movimiento del caballo
typedef struct {
    int row;
    int col;
    int move;
} KnightMove;

// Matriz de movimientos posibles del caballo
int knight_moves[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1},
                         {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

// Función para comprobar si una posición (row, col) está dentro de la cuadrícula
bool isValidMove(int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n && grid[row][col] == 0);
}

// Función para realizar el movimiento del caballo en una posición (row, col)
void makeMove(int row, int col, int move) {
    grid[row][col] = move;
    total_moves++;
}

// Función para deshacer el movimiento del caballo en una posición (row, col)
void undoMove(int row, int col) {
    grid[row][col] = 0;
    total_moves--;
}

// Función para resolver el problema del caballo utilizando backtracking
bool solveKnightTour(int row, int col, int move) {
    // Hemos visitado todas las casillas
    if (total_moves == n * n) {
        return true;
    }

    for (int i = 0; i < 8; i++) {
        int next_row = row + knight_moves[i][0];
        int next_col = col + knight_moves[i][1];

        if (isValidMove(next_row, next_col)) {
            makeMove(next_row, next_col, move);

            if (solveKnightTour(next_row, next_col, move + 1)) {
                return true;
            }

            undoMove(next_row, next_col);
        }
    }

    return false;
}

// Función para ejecutar la función solveKnightTour en paralelo utilizando hilos
void* solveKnightTourParallel(void* arg) {
    KnightMove* knight_move = (KnightMove*)arg;
    int row = knight_move->row;
    int col = knight_move->col;
    int move = knight_move->move;

    makeMove(row, col, move);
    solveKnightTour(row, col, move + 1);
    undoMove(row, col);

    free(knight_move);

    pthread_exit(NULL);
}

int main() {
    printf("Ingrese el tamano de la cuadricula (n): ");
    scanf("%d", &n);

    int start_row, start_col;
    printf("Ingrese la posicion inicial del caballo (x,y) usando espacios para separar cada componente:");
    scanf("%d %d", &start_row, &start_col);

    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[NUM_THREADS];

    // Crear hilos para resolver el problema del caballo en paralelo
    for (int i = 0; i < NUM_THREADS; i++) {
        KnightMove* knight_move = malloc(sizeof(KnightMove));
        knight_move->row = start_row;
        knight_move->col = start_col;
        knight_move->move = 1;

        pthread_create(&threads[i], NULL, solveKnightTourParallel, (void*)knight_move);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Imprimir la solución
    printf("Soluci0n:\n");
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            printf("%2d ", grid[row][col]);
        }
        printf("\n");
    }

    pthread_mutex_destroy(&mutex);

    return 0;
}
