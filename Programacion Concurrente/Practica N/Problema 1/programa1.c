#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 3  // Tamaño de la matriz
#define NUM_THREADS N  // Número de hilos

float matriz[N][N];
float inversa[N][N];

// Estructura de datos para los argumentos de los hilos
typedef struct {
    int fila_inicio;
    int fila_fin;
} ThreadArgs;

// Función para imprimir una matriz
void imprimirMatriz(float matriz[N][N]) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%.3f\t", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Función para calcular la matriz de cofactores
void calcularCofactores(float matriz[N][N], float temp[N][N], int fila, int columna, int n) {
    int i = 0, j = 0;
    for (int fila_actual = 0; fila_actual < n; fila_actual++) {
        for (int columna_actual = 0; columna_actual < n; columna_actual++) {
            if (fila_actual != fila && columna_actual != columna) {
                temp[i][j++] = matriz[fila_actual][columna_actual];
                if (j == n - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

// Función para calcular el determinante de una matriz
float calcularDeterminante(float matriz[N][N], int n) {
    float determinante = 0;
    if (n == 1) {
        return matriz[0][0];
    }
    float temp[N][N];
    int signo = 1;
    for (int columna = 0; columna < n; columna++) {
        calcularCofactores(matriz, temp, 0, columna, n);
        determinante += signo * matriz[0][columna] * calcularDeterminante(temp, n - 1);
        signo = -signo;
    }
    return determinante;
}

// Función para calcular la matriz adjunta (trabajada por hilos)
void *calcularAdjunta(void *args) {
    ThreadArgs *threadArgs = (ThreadArgs *)args;
    int fila_inicio = threadArgs->fila_inicio;
    int fila_fin = threadArgs->fila_fin;

    float temp[N][N];
    int signo;

    for (int i = fila_inicio; i < fila_fin; i++) {
        for (int j = 0; j < N; j++) {
            calcularCofactores(matriz, temp, i, j, N);
            signo = ((i + j) % 2 == 0) ? 1 : -1;
            inversa[j][i] = signo * (calcularDeterminante(temp, N - 1));
        }
    }

    pthread_exit(NULL);
}

// Función para calcular la matriz inversa
void calcularInversa() {
    float determinante = calcularDeterminante(matriz, N);
    if (determinante == 0) {
        printf("La matriz no tiene inversa.\n");
        return;
    }

    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];

    int filas_por_hilo = N / NUM_THREADS;
    int resto = N % NUM_THREADS;
    int fila_inicio = 0;
    int fila_fin;

    for (int i = 0; i < NUM_THREADS; i++) {
        fila_fin = fila_inicio + filas_por_hilo;
        if (resto > 0) {
            fila_fin++;
            resto--;
        }

        threadArgs[i].fila_inicio = fila_inicio;
        threadArgs[i].fila_fin = fila_fin;

        pthread_create(&threads[i], NULL, calcularAdjunta, (void *)&threadArgs[i]);

        fila_inicio = fila_fin;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            inversa[i][j] /= determinante;
        }
    }
}

// Función principal
int main() {
    srand(time(NULL));  // Inicializar la semilla para generar números aleatorios

    printf("Matriz original:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = rand() % 200;  // Generar números aleatorios entre 0 y 99
        }
    }
    imprimirMatriz(matriz);

    calcularInversa();

    printf("Matriz inversa:\n");
    imprimirMatriz(inversa);

    return 0;
}
