#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funciones.h"

void main(){
	nodo lista,listaValores,listaMbytes,listaTasa;
	int tam,valor_1,valor_2,valor_3,mbytes_1,mbytes_2,mbytes_3;

	//Inicializacion de las listas 

	lista = crearLista();
	lista = abrirArchivo(lista);
	listaValores = crearLista();
	listaMbytes = crearLista();
	listaTasa = crearLista();
	valor_1 = 0;
	valor_2 = 0;
	mbytes_1 = 0;
	mbytes_2 = 0;

	printf("Introduzca el tamaño de la USB.......");
	scanf("%d",&tam);

	//Lista ordenada por valor
	lista = ordenarPorValor(lista);
	listaValores = obtenerDatos(lista,tam);
	valor_1 = valorTotal(listaValores);
	mbytes_1 = mbytesTotales(listaValores);
	
	//Lista ordenada por mbytes
	lista = ordenarPorMb(lista);
	listaMbytes = obtenerDatos(lista,tam);
	valor_2 = valorTotal(listaMbytes);
	mbytes_2 = mbytesTotales(listaMbytes);

	//Lista ordenada por tasa
	//la tasa es obtenida dividiendo los mbyte entre el valor
	lista = ordenarPorTasa(lista);
	listaTasa = obtenerDatos(lista,tam);
	valor_3 = valorTotal(listaTasa);
	mbytes_3 = mbytesTotales(listaTasa);

	if( valor_1 > valor_2 && valor_1 > valor_3){
		printf("\n");
		mostrarLista(listaValores);
		printf("\nDatos con valor %d y capacidad %dMb\n",valor_1,mbytes_1);
	}else if( valor_2 > valor_1 && valor_2 > valor_3 ){
		printf("\n");
		mostrarLista(listaMbytes);
		printf("\nDatos con valor %d y capacidad %dMb\n",valor_2,mbytes_2);
	}else{
		printf("\n");
		mostrarLista(listaTasa);
		printf("\nDatos con valor %d y capacidad %dMb\n",valor_3,mbytes_3);		
	}


}