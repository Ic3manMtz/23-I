#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define MAX_POPULATION 1000  // Máximo número de individuos
#define MAX_N 10  // Máximo tamaño del vector
#define NUM_GENERATIONS 5  // Número de generaciones a evolucionar
#define NUM_THREADS 4  // Número de hilos para evaluación paralela

typedef struct {
    int components[MAX_N];
    double fitness;
} Individual;

Individual population[MAX_POPULATION];
int population_size;
pthread_mutex_t mutex;

// Función para generar un número aleatorio en un rango dado
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Función para evaluar la aptitud de un individuo (f)
double evaluateFitness(const Individual* individual, int n) {
    // Aquí debes implementar la función f() que evalúa la aptitud del individuo
    // y devuelve un número real
    // Por ejemplo, supongamos que la función f() calcula la suma de los componentes
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += individual->components[i];
    }
    return sum;
}

// Función para comparar dos individuos por su aptitud (fitness)
int compareIndividuals(const void* a, const void* b) {
    const Individual* individualA = (const Individual*)a;
    const Individual* individualB = (const Individual*)b;

    if (individualA->fitness < individualB->fitness) {
        return -1;
    } else if (individualA->fitness > individualB->fitness) {
        return 1;
    } else {
        return 0;
    }
}

// Función para generar la siguiente generación de individuos
void generateNextGeneration(int n) {
    // Ordenar la población actual por aptitud (de menor a mayor)
    qsort(population, population_size, sizeof(Individual), compareIndividuals);

    // Crear la siguiente generación
    int next_generation_size = population_size / 2;  // Tamaño de la siguiente generación
    Individual next_generation[MAX_POPULATION];  // Población de la siguiente generación

    // Copiar los mejores individuos (mitad de la población actual) a la siguiente generación
    for (int i = 0; i < next_generation_size; i++) {
        next_generation[i] = population[i];
    }

    // Generar nuevos individuos aplicando operadores de mutación y combinación
    for (int i = next_generation_size; i < population_size; i++) {
        // Operador de mutación: cambiar una posición al azar sumando o restando la unidad
        Individual mutated_individual = population[randomInRange(0, population_size - 1)];
        int random_position = randomInRange(0, n - 1);
        int random_operation = randomInRange(0, 1);  // 0 para restar, 1 para sumar

        if (random_operation == 0) {
            mutated_individual.components[random_position]--;
        } else {
            mutated_individual.components[random_position]++;
        }

        // Operador de combinación: combinar el individuo mutado con otro individuo existente
        Individual combined_individual = next_generation[randomInRange(0, next_generation_size - 1)];
        int first_component = randomInRange(0, n - 1);
        int second_component = randomInRange(0, n - 1);

        mutated_individual.components[first_component] = combined_individual.components[first_component];
        mutated_individual.components[second_component] = combined_individual.components[second_component];

        next_generation[i] = mutated_individual;
    }

    // Actualizar la población actual con la siguiente generación
    population_size = population_size / 2;
    for (int i = 0; i < population_size; i++) {
        population[i] = next_generation[i];
    }
}

// Función para calcular el promedio de la función f() para los individuos de la población actual (paralela)
void* calculateAverageFitness(void* arg) {
    int n = *((int*)arg);
    double sum = 0;

    for (int i = 0; i < population_size; i++) {
        double fitness = evaluateFitness(&population[i], n);
        sum += fitness;
    }

    pthread_mutex_lock(&mutex);
    *(double*)arg += sum;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    srand(time(NULL));

    int n;  // Tamaño del vector
    printf("Ingrese el tamano del vector: ");
    scanf("%d", &n);

    printf("Ingrese los componentes de los individuos de la poblacion (separados por espacios):\n");

    // Leer la población inicial
    population_size = 0;
    while (population_size < MAX_POPULATION) {
        Individual new_individual;
        for (int i = 0; i < n; i++) {
            scanf("%d", &new_individual.components[i]);
        }
        population[population_size] = new_individual;
        population_size++;

        char next_char = getchar();
        if (next_char == '\n') {
            break;
        }
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[NUM_THREADS];
    double total_fitness = 0;

    // Evolucionar las siguientes N generaciones
    for (int generation = 0; generation < NUM_GENERATIONS; generation++) {
        generateNextGeneration(n);

        // Calcular la aptitud promedio en paralelo utilizando hilos
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_create(&threads[i], NULL, calculateAverageFitness, (void*)&total_fitness);
        }

        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
    }

    // Calcular y mostrar el promedio de la función f() para los individuos de las generaciones resultantes
    double average_fitness = total_fitness / (NUM_GENERATIONS * population_size);
    printf("El promedio de la funcion f() para los individuos de las generaciones resultantes es: %.2f\n", average_fitness);

    pthread_mutex_destroy(&mutex);

    return 0;
}
