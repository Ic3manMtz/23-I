#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_NUMBERS 1000000  // Máximo número de elementos en el archivo
#define NUM_THREADS 4  // Número de hilos a utilizar
#define CHUNK_SIZE (MAX_NUMBERS / NUM_THREADS)  // Tamaño de cada fragmento a ordenar

int numbers[MAX_NUMBERS];
int sorted_numbers[MAX_NUMBERS];

// Estructura de datos para los argumentos de los hilos
typedef struct {
    int start_index;
    int end_index;
} ThreadArgs;

// Función para imprimir un arreglo de números
void printNumbers(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Función de comparación para el ordenamiento ascendente
int compareAscending(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Función para ordenar una porción del arreglo
void* sortArray(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    int start_index = threadArgs->start_index;
    int end_index = threadArgs->end_index;

    qsort(&numbers[start_index], end_index - start_index + 1, sizeof(int), compareAscending);

    pthread_exit(NULL);
}

// Función para combinar los fragmentos ordenados en un solo arreglo
void mergeArrays(int* array, int start_index, int mid_index, int end_index) {
    int left_size = mid_index - start_index + 1;
    int right_size = end_index - mid_index;

    int left_array[left_size];
    int right_array[right_size];

    for (int i = 0; i < left_size; i++) {
        left_array[i] = array[start_index + i];
    }

    for (int i = 0; i < right_size; i++) {
        right_array[i] = array[mid_index + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = start_index;

    while (i < left_size && j < right_size) {
        if (left_array[i] <= right_array[j]) {
            array[k] = left_array[i];
            i++;
        } else {
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        array[k] = left_array[i];
        i++;
        k++;
    }

    while (j < right_size) {
        array[k] = right_array[j];
        j++;
        k++;
    }
}

// Función para ordenar el arreglo utilizando el algoritmo de mezcla (merge sort)
void mergeSort(int* array, int start_index, int end_index) {
    if (start_index < end_index) {
        int mid_index = start_index + (end_index - start_index) / 2;

        mergeSort(array, start_index, mid_index);
        mergeSort(array, mid_index + 1, end_index);

        mergeArrays(array, start_index, mid_index, end_index);
    }
}

// Función principal
int main() {
    FILE* file = fopen("numeros.txt", "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    int num_count = 0;
    int number;

    // Leer los números del archivo
    while (fscanf(file, "%d", &number) != EOF) {
        numbers[num_count] = number;
        num_count++;
    }

    fclose(file);

    printf("Numeros sin ordenar:\n");
    printNumbers(numbers, num_count);

    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];

    // Crear los hilos para ordenar cada porción del arreglo
    for (int i = 0; i < NUM_THREADS; i++) {
        threadArgs[i].start_index = i * CHUNK_SIZE;
        threadArgs[i].end_index = (i + 1) * CHUNK_SIZE - 1;

        if (i == NUM_THREADS - 1) {
            threadArgs[i].end_index = num_count - 1;  // Último hilo se encarga del resto
        }

        pthread_create(&threads[i], NULL, sortArray, (void*)&threadArgs[i]);
    }

    // Esperar a que todos los hilos terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Combinar los fragmentos ordenados
    mergeSort(numbers, 0, num_count - 1);

    printf("Números ordenados:\n");
    printNumbers(numbers, num_count);

    return 0;
}
