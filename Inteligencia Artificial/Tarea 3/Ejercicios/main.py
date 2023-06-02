# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

import csv
import random
import math
import matplotlib.pyplot as plt
import numpy as np

# Cargar los datos de la base de datos IRIS
file = open("IRIS.csv")
type(file)
csvreader = csv.reader(file)
header = next(csvreader)
rows = []
for row in csvreader:
    rows.append(row)
file.close()
firstStep = np.array(rows)
data = firstStep.astype(float)

# Parámetros del algoritmo de recocido simulado
temperatura_inicial = 1000
factor_enfriamiento = 0.99
num_iteraciones = 1000

# Función para calcular la distancia de Manhattan entre dos puntos
def distancia_manhattan(punto1, punto2):
    return sum(abs(a - b) for a, b in zip(punto1, punto2))

# Función para calcular el costo total de los clusters
def costo_total(clusters):
    costo = 0
    for i, centroide in enumerate(clusters):
        for punto in clusters[i]:
            costo += distancia_manhattan(punto, centroide)
    return costo

# Función para generar una solución inicial aleatoria
def generar_solucion_inicial(num_clusters, data):
    solucion = [[] for _ in range(num_clusters)]
    for punto in data:
        cluster = random.randint(0, num_clusters-1)
        solucion[cluster].append(punto)
    return solucion

# Función para generar una nueva solución vecina
def generar_vecino(solucion):
    nueva_solucion = solucion.copy()
    cluster_origen = random.randint(0, len(solucion)-1)
    cluster_destino = random.randint(0, len(solucion)-1)
    punto = nueva_solucion[cluster_origen].pop(random.randint(0, len(nueva_solucion[cluster_origen])-1))
    nueva_solucion[cluster_destino].append(punto)
    return nueva_solucion

# Algoritmo de recocido simulado
def recocido_simulado(data, num_clusters, temperatura_inicial, factor_enfriamiento, num_iteraciones):
    solucion_actual = generar_solucion_inicial(num_clusters, data)
    costo_actual = costo_total(solucion_actual)
    mejor_solucion = solucion_actual.copy()
    mejor_costo = costo_actual
    temperatura = temperatura_inicial

    for _ in range(num_iteraciones):
        nueva_solucion = generar_vecino(solucion_actual)
        nuevo_costo = costo_total(nueva_solucion)

        if (nuevo_costo < costo_actual).any:
            solucion_actual = nueva_solucion
            costo_actual = nuevo_costo
        else:
            probabilidad_aceptacion = math.exp((costo_actual - nuevo_costo) / temperatura)
            if random.random() < probabilidad_aceptacion:
                solucion_actual = nueva_solucion
                costo_actual = nuevo_costo

        if (costo_actual < mejor_costo).any:
            mejor_solucion = solucion_actual.copy()
            mejor_costo = costo_actual

        temperatura *= factor_enfriamiento

    return mejor_costo

def crear_boxplot(datos):
    datos = list(zip(*datos))
    plt.figure(num='Tarea 3')
    plt.boxplot(datos)
    plt.title("Diagrama de cajas")

    nombres_x=['sepal_lenght','sepal_width','petal_lenght','petal_width']
    plt.xticks(range(1, len(nombres_x) + 1), nombres_x)
    plt.show()

# Ejecutar el algoritmo de recocido simulado
num_clusters = 3
mejores_costos = []

for i in range(30):
    try:
        mejor_costo = recocido_simulado(data, num_clusters, temperatura_inicial, factor_enfriamiento, num_iteraciones)
        mejores_costos.append(mejor_costo)
        print(f"Mejor costo de la corrida {i}: {mejor_costo}")
    except ValueError:
        print("Error en los valores random ocasionado por la semilla")

crear_boxplot(mejores_costos)

