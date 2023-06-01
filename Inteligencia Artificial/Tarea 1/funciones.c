#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

struct Celda * crearCelda(int estado){
    struct Celda * nueva;
    nueva=(struct Celda *)malloc(sizeof(Celda));

    nueva->estado=estado;
    nueva->vecinos=(int *)calloc(4,sizeof(int));
    nueva->izquierda=NULL;
    nueva->derecha=NULL;
    nueva->arriba=NULL;
    nueva->abajo=NULL;

    return nueva;
}

void crearFila(struct Celda * inicio){
    struct Celda * nueva, * actual;
    int i;

    actual=inicio;

    for(i=0;i<3;i++){
        nueva=crearCelda(inicio->estado + i + 1);
        nueva->izquierda=actual;
        actual->derecha=nueva;
        actual=actual->derecha;
    }
}

void unirFilas(struct Celda * fila_1,struct Celda * fila_2){
    struct Celda * actual_1,* actual_2;
    int i;

    actual_1=fila_1;
    actual_2=fila_2;

    for(i=0;i<4;i++){
        actual_1->abajo=actual_2;
        actual_2->arriba=actual_1;
        actual_1=actual_1->derecha;
        actual_2=actual_2->derecha;
    }
}

void mostrarFila(struct Celda * primera){
    int i,j;
    struct Celda * actual,* inicio;

    actual=primera;
    for(i=0;i<4;i++){
        inicio=actual->abajo;
        for(j=0;j<4;j++){
            printf("\t %d  ",actual->estado);
            actual=actual->derecha;
        }
        printf("\n");
        actual=inicio;
    }
}

void establecerVecinos(struct Celda * primera){
    int i,j;
    struct Celda *actual, *inicio;

    actual=primera;
    for(i=0;i<4;i++){
        inicio=actual->abajo;
        for(j=0;j<4;j++){
            asignarVecinos(actual);
            actual=actual->derecha;
        }
        printf("\n");
        actual=inicio;
    }
}

void asignarVecinos(struct Celda * celda){
    switch(celda->estado){
        case 1: celda->vecinos[0]=2;
            break;
        case 2: celda->vecinos[0]=1;
                celda->vecinos[1]=3;
                celda->vecinos[2]=6;
            break;
        case 3: celda->vecinos[0]=2;
                celda->vecinos[1]=4;
            break;
        case 4: celda->vecinos[0]=3;
                celda->vecinos[1]=8;
            break;
        case 5: celda->vecinos[0]=6;
                celda->vecinos[1]=9;
            break;
        case 6: celda->vecinos[0]=2;
                celda->vecinos[1]=5;
            break;
        case 7: celda->vecinos[0]=8;
                celda->vecinos[1]=11;
            break;
        case 8: celda->vecinos[0]=4;
                celda->vecinos[1]=7;
            break;
        case 9: celda->vecinos[0]=5;
                celda->vecinos[1]=10;
            break;
        case 10: celda->vecinos[0]=9;
                celda->vecinos[1]=14;
            break;
        case 11: celda->vecinos[0]=7;
                celda->vecinos[1]=12;
            break;
        case 12: celda->vecinos[0]=11;
                celda->vecinos[1]=16;
            break;
        case 13: celda->vecinos[0]=14;
            break;
        case 14: celda->vecinos[0]=10;
                celda->vecinos[1]=13;
            break;
        case 15: celda->vecinos[0]=14;
            break;
        case 16: celda->vecinos[0]=12;
            break;
    }
}