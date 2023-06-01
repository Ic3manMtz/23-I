//Autores.- Martinez Buenrostro Jorge Rafael 

#include <stdio.h>

#ifndef _arreglo_
#define _arreglo_

typedef struct{
	int* arr;
	int tam;
}Arreglo;

typedef struct{
	char* wn;
}Cadena;

typedef struct{
	int* coeficiente;
	int* exponente;
}Monomio;

typedef Arreglo* arreglo;
typedef Cadena* cadena;
typedef Monomio* monomio;

arreglo crearArreglo(int n);
int numeroRandom(int minimo,int maximo);
void llenarArreglo(arreglo a);
void liberarArreglo(arreglo a);
void ordenarArreglo(arreglo a);
void mostrarArreglo(arreglo a);

void unirArreglo(arreglo a,arreglo b,arreglo c);

double cronometro(arreglo a);

void mergeSort(arreglo a,int bajo,int alto);
void merge(arreglo a,int bajo_1,int alto_1,int bajo_2,int alto_2);

cadena crearCadena();
void pedirCadena(cadena a);
void subCadena(cadena a,cadena b);

monomio crearMonomio();
void mostrarMonomio(monomio m);
#endif