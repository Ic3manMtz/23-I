#include <stdio.h>

#ifndef _Celda_
#define _Celda_

typedef struct{
    int estado;
    int * vecinos;
    struct Celda * izquierda;
    struct Celda * derecha;
    struct Celda * arriba;
    struct Celda * abajo;
}Celda;

struct Celda * crearCelda(int);
void crearFila(struct Celda *);
void unirFilas(struct Celda * fila_1,struct Celda * fila_2);
void mostrarFila(struct Celda*);
void mostrarLaberinto(struct Celda *);
void establecerVecinos(struct Celda *);
void asignarVecinos(struct Celda *);

#endif