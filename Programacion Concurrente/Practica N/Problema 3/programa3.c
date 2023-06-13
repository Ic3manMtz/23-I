#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_FILES 10  // Máximo número de archivos
#define MAX_NUMBERS 1000000  // Máximo número de elementos en cada archivo

int numbers[MAX_FILES][MAX_NUMBERS];
int merged_numbers[MAX_NUMBERS * MAX_FILES];

// Estructura de datos para los argumentos de los hilos
typedef struct {
    int file_index;
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

// Función para combinar dos arreglos ordenados en uno solo
void mergeArrays(int* array1, int size1, int* array2, int size2, int* merged_array) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < size1 && j < size2) {
        if (array1[i] <= array2[j]) {
            merged_array[k] = array1[i];
            i++;
        } else {
            merged_array[k] = array2[j];
            j++;
        }
        k++;
    }

    while (i < size1) {
        merged_array[k] = array1[i];
        i++;
        k++;
    }

    while (j < size2) {
        merged_array[k] = array2[j];
        j++;
        k++;
    }
}

// Función para combinar múltiples archivos de números en un solo archivo ordenado
void* mergeFiles(void* args) {
    ThreadArgs* threadArgs = (ThreadArgs*)args;
    int file_index = threadArgs->file_index;
    int start_index = threadArgs->start_index;
    int end_index = threadArgs->end_index;

    int size1 = end_index - start_index + 1;
    int size2 = MAX_NUMBERS;

    int* array1 = numbers[file_index];
    int* array2 = merged_numbers;

    for (int i = file_index + 1; i <= end_index; i++) {
        mergeArrays(array1, size1, numbers[i], size2, array2);
        size1 += size2;
        int* temp = array1;
        array1 = array2;
        array2 = temp;
    }

    // Copiar el resultado final al arreglo merged_numbers
    for (int i = 0; i < size1; i++) {
        merged_numbers[i] = array1[i];
    }

    pthread_exit(NULL);
}

// Función principal
int main() {
    int num_files;
    printf("Ingrese el número de archivos a combinar (máximo %d): ", MAX_FILES);
    scanf("%d", &num_files);

    if (num_files < 2 || num_files > MAX_FILES) {
        printf("Número de archivos inválido.\n");
        return 1;
    }

    // Leer los números de los archivos
    for (int i = 0; i < num_files; i++) {
        char file_name[20];
        printf("Ingrese el nombre del archivo %d: ", i + 1);
        scanf("%s", file_name);

        FILE* file = fopen(file_name, "r");
        if (file == NULL) {
            printf("No se pudo abrir el archivo %s.\n", file_name);
            return 1;
        }

        int num_count = 0;
        int number;
        while (fscanf(file, "%d", &number) != EOF) {
            numbers[i][num_count] = number;
            num_count++;
        }

        fclose(file);
    }

    printf("Archivos originales:\n");
    for (int i = 0; i < num_files; i++) {
        printf("Archivo %d: ", i + 1);
        printNumbers(numbers[i], MAX_NUMBERS);
    }

    pthread_t threads[num_files - 1];
    ThreadArgs threadArgs[num_files - 1];

    // Crear los hilos para combinar los archivos
    for (int i = 0; i < num_files - 1; i++) {
        threadArgs[i].file_index = i;
        threadArgs[i].start_index = i;
        threadArgs[i].end_index = num_files - 1;

        pthread_create(&threads[i], NULL, mergeFiles, (void*)&threadArgs[i]);
    }

    // Ejecutar el último hilo en el hilo principal
    ThreadArgs lastThreadArgs;
    lastThreadArgs.file_index = num_files - 1;
    lastThreadArgs.start_index = num_files - 1;
    lastThreadArgs.end_index = num_files - 1;
    mergeFiles((void*)&lastThreadArgs);

    // Esperar a que los hilos terminen
    for (int i = 0; i < num_files - 1; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Archivo combinado:\n");
    printNumbers(merged_numbers, MAX_NUMBERS * num_files);

    // Guardar el archivo combinado
    FILE* merged_file = fopen("archivo_combinado.txt", "w");
    if (merged_file == NULL) {
        printf("No se pudo crear el archivo combinado.\n");
        return 1;
    }

    for (int i = 0; i < MAX_NUMBERS * num_files; i++) {
        fprintf(merged_file, "%d\n", merged_numbers[i]);
    }

    fclose(merged_file);

    printf("El archivo combinado se ha guardado exitosamente.\n");

    return 0;
}
