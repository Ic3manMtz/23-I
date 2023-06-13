#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_VECTORS 1000  // Máximo número de vectores
#define MAX_N 10  // Máximo tamaño del vector
#define NUM_THREADS 4  // Número de hilos a utilizar

typedef struct {
    int components[MAX_N];
} Vector;

Vector vectors[MAX_VECTORS];
Vector elite[MAX_VECTORS];
int elite_size = 0;

// Estructura de datos para los argumentos de los hilos
typedef struct {
    int start_index;
    int end_index;
} ThreadArgs;

// Función para comparar dos vectores
int compareVectors(const void* a, const void* b) {
    const Vector* vectorA = (const Vector*)a;
    const Vector* vectorB = (const Vector*)b;

    for (int i = 0; i < MAX_N; i++) {
        if (vectorA->components[i] < vectorB->components[i]) {
            return -1;
        } else if (vectorA->components[i] > vectorB->components[i]) {
            return 1;
        }
    }

    return 0;
}

// Función para verificar si un vector domina a otro
bool isDominated(const Vector* vectorA, const Vector* vectorB) {
    for (int i = 0; i < MAX_N; i++) {
        if (vectorA->components[i] < vectorB->components[i]) {
            return false;
        }
    }
    return true;
}

// Función para verificar si un vector es no dominado por ningún vector en la élite actual
bool isNonDominated(const Vector* vector) {
    for (int i = 0; i < elite_size; i++) {
        if (isDominated(&elite[i], vector)) {
            return false;
        }
    }
    return true;
}

// Función para imprimir un vector
void printVector(const Vector* vector, int n) {
    printf("(");
    for (int i = 0; i < n; i++) {
        printf("%d", vector->components[i]);
        if (i < n - 1) {
            printf(",");
        }
    }
    printf(")");
}

// Función ejecutada por cada hilo
void* checkNonDominated(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    int start_index = threadArgs->start_index;
    int end_index = threadArgs->end_index;

    for (int i = start_index; i < end_index; i++) {
        if (isNonDominated(&vectors[i])) {
            elite[elite_size] = vectors[i];
            elite_size++;
        }
    }

    pthread_exit(NULL);
}

// Función principal
int main() {
    int n;
    printf("Ingrese el tamano del vector (n): ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_N) {
        printf("Tamaño del vector invalido.\n");
        return 1;
    }

    printf("\nIngrese los vectores uno por uno separando los componentes por espacios.\n");
    printf("Cuando haya terminado, ingrese un vector con todos los componentes iguales a -1.\n");

    int vector_count = 0;
    while (vector_count < MAX_VECTORS) {
        Vector new_vector;
        int component;
        for (int i = 0; i < n; i++) {
            scanf("%d", &component);
            if (component == -1) {
                break;
            }
            new_vector.components[i] = component;
        }
        if (component == -1) {
            break;
        }
        vectors[vector_count] = new_vector;
        vector_count++;
    }

    // Ordenar los vectores en orden ascendente
    qsort(vectors, vector_count, sizeof(Vector), compareVectors);

    // Crear hilos para verificar los vectores no dominados
    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];

    int vectors_per_thread = vector_count / NUM_THREADS;
    int remaining_vectors = vector_count % NUM_THREADS;
    int start_index = 0;
    int end_index;

    for (int i = 0; i < NUM_THREADS; i++) {
        end_index = start_index + vectors_per_thread;
        if (remaining_vectors > 0) {
            end_index++;
            remaining_vectors--;
        }

        threadArgs[i].start_index = start_index;
        threadArgs[i].end_index = end_index;

        pthread_create(&threads[i], NULL, checkNonDominated, (void*)&threadArgs[i]);

        start_index = end_index;
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Mostrar la élite encontrada
    printf("La elite esta compuesta por:\n");
    for (int i = 0; i < elite_size; i++) {
        printVector(&elite[i], n);
        printf("\n");
    }

    return 0;
}
