# This is a sample Python script.
import csv
import random

import numpy
import numpy as np
import plotly.express as px

def import_data():
    file = open('/home/jorgemartinez/Documents/UAM/23 - I/Inteligencia Artificial/Tarea 2/IRIS.csv')
    type(file)
    csvreader = csv.reader(file)
    header = next(csvreader)

    rows = []

    for row in csvreader:
        rows.append(row)

    file.close()

    return rows

def print_data(data):
    for i, row in enumerate(data):
        print(f"Obs {i} [{row[0]}][{row[1]}][{row[2]}][{row[3]}]")

def min_values(data):
    minimos = [10.0, 10.0, 10.0, 10.0]

    for row in data:
        for i, column in enumerate(row):
            if i == 0:
                coordenada = float(column)
                if coordenada < minimos[i]:
                    minimos[i] = coordenada
            if i == 1:
                coordenada = float(column)
                if coordenada < minimos[i]:
                    minimos[i] = coordenada
            if i == 2:
                coordenada = float(column)
                if coordenada < minimos[i]:
                    minimos[i] = coordenada
            if i == 3:
                coordenada = float(column)
                if coordenada < minimos[i]:
                    minimos[i] = coordenada

    return minimos

def max_values(data):
    maximos = [0.0, 0.0, 0.0, 0.0]

    for row in data:
        for i, column in enumerate(row):
            if i == 0:
                coordenada = float(column)
                if coordenada > maximos[i]:
                    maximos[i] = coordenada
            if i == 1:
                coordenada = float(column)
                if coordenada > maximos[i]:
                    maximos[i] = coordenada
            if i == 2:
                coordenada = float(column)
                if coordenada > maximos[i]:
                    maximos[i] = coordenada
            if i == 3:
                coordenada = float(column)
                if coordenada > maximos[i]:
                    maximos[i] = coordenada

    return maximos

def set_species(data):
    for row in data:
        row[4] = str(random.randint(0, 2))

def normalize_data(data, minimos, maximos):
    for row in data:
        value = float(row[0])
        normal = (value - minimos[0]) / (maximos[0] - minimos[0])
        row[0] = str(round(normal, 2))
        value = float(row[1])
        normal = (value - minimos[1]) / (maximos[1] - minimos[1])
        row[1] = str(round(normal, 2))
        value = float(row[2])
        normal = (value - minimos[2]) / (maximos[2] - minimos[2])
        row[2] = str(round(normal, 2))
        value = float(row[3])
        normal = (value - minimos[3]) / (maximos[3] - minimos[3])
        row[3] = str(round(normal, 2))

def sol_inicial(data):
    sol_act = []
    for row in data:
        sol_act.append(row[4])

    return sol_act

def func_obj(solucion, obj):
    contador = []
    for i in range(3):
        contador.append(solucion.count(str(i)))

    #print("\nVeces que se repiten 0, 1, 2 en la solución")
    #print(contador)

    centroides = np.array([[0.0, 0.0, 0.0, 0.0], [0.0, 0.0, 0.0, 0.0], [0.0, 0.0, 0.0, 0.0]])

    for row in obj:
        if row[4] == '0':
            centroides[0][0] += float(row[0])
            centroides[0][1] += float(row[1])
            centroides[0][2] += float(row[2])
            centroides[0][3] += float(row[3])
        if row[4] == '1':
            centroides[1][0] += float(row[0])
            centroides[1][1] += float(row[1])
            centroides[1][2] += float(row[2])
            centroides[1][3] += float(row[3])
        if row[4] == '2':
            centroides[2][0] += float(row[0])
            centroides[2][1] += float(row[1])
            centroides[2][2] += float(row[2])
            centroides[2][3] += float(row[3])

    for i, row in enumerate(centroides):
        if contador[i] != 0:
            row[0] = row[0] / contador[i]
            row[1] = row[1] / contador[i]
            row[2] = row[2] / contador[i]
            row[3] = row[3] / contador[i]

    #print("\nCentroides")
    #for i, row in enumerate(centroides):
    #    print(f"C[{i}] = ({row[0]},{row[1]},{row[2]},{row[3]})")

    distancia = 0.0

    for row in obj:
        if row[4] == '0':
            distancia += abs(centroides[0][0] - float(row[0]))
            distancia += abs(centroides[0][1] - float(row[1]))
            distancia += abs(centroides[0][2] - float(row[2]))
            distancia += abs(centroides[0][3] - float(row[3]))
        if row[4] == '1':
            distancia += abs(centroides[1][0] - float(row[0]))
            distancia += abs(centroides[1][1] - float(row[1]))
            distancia += abs(centroides[1][2] - float(row[2]))
            distancia += abs(centroides[1][3] - float(row[3]))
        if row[4] == '2':
            distancia += abs(centroides[2][0] - float(row[0]))
            distancia += abs(centroides[2][1] - float(row[1]))
            distancia += abs(centroides[2][2] - float(row[2]))
            distancia += abs(centroides[2][3] - float(row[3]))

    #print(f"\nDistancia:{distancia}")

    return distancia

def hill_climbing(sol_act,data,costo_act):
    vecinos = np.zeros(shape=(3,150))

    for i, row in enumerate(sol_act):
        for j in range(3):
            if row == '0':
                vecinos[j][i] = 1234567.89
                if row != '1':
                    aux = row
                    sol_act[i] = '1'
                    vecinos[j][i] = func_obj(sol_act, data)
                    sol_act[i] = aux
                elif row != '2':
                    aux = row
                    sol_act[i] = '2'
                    vecinos[j][i] = func_obj(sol_act, data)
                    sol_act = aux
            elif row != '1':
                vecinos[j][i] = 1234567.89
                if row != '0':
                    aux = row
                    sol_act[i] = '0'
                    vecinos[j][i] = func_obj(sol_act, data)
                    sol_act[i] = aux
                elif row != '2':
                    aux = row
                    sol_act[i] = '2'
                    vecinos[j][i] = func_obj(sol_act, data)
                    sol_act = aux
            elif row != '2':
                vecinos[j][i] = 1234567.89
                if row != '0':
                    aux = row
                    sol_act[i] = '0'
                    vecinos[j][i] = func_obj(sol_act, data)
                    sol_act[i] = aux
                elif row != '1':
                    aux = row
                    sol_act[i] = '1'
                    vecinos[j][i] = func_obj(sol_act, data)
                    sol_act = aux

    for i, row in enumerate(vecinos):
        for j, column in enumerate(row):
            if column <= costo_act:
                sol_act[j] = i
                costo_act = column

    return costo_act

def boxplot(data):
    df = px.data.tips()
    fig = px.box(df, x="time",y="total_bill")
    fig.show()

def main(iteraciones):
    data = import_data()
    minimos = min_values(data)
    maximos = max_values(data)

    set_species(data)

    #print("\nDatos iniciales")
    #print_data(data)
    normalize_data(data, minimos, maximos)
    #print(f"\nValores minimos [{minimos[0]}, {minimos[1]}, {minimos[2]}, {minimos[3]}]")
    #print(f"\nValores maximos [{maximos[0]}, {maximos[1]}, {maximos[2]}, {maximos[3]}]")
    #print("\nDatos normalizados")
    #print_data(data)

    sol_act = sol_inicial(data)
    #print("\nSol_Act")
    #print(sol_act)

    costo_act = func_obj(sol_act, data)
    print(f"Costo de la primer funcion objetivo {costo_act}")

    nuevo_costo = hill_climbing(sol_act, data, costo_act)
    for i in range(50):
        nuevo_costo = hill_climbing(sol_act, data, nuevo_costo)
        print(f"Costo de la {i} iteracion de hill climbing {nuevo_costo}")

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    costo = main(1)