#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct Celda{
    int estado;
    int * vecinos;
    struct Celda * izquierda;
    struct Celda * derecha;
    struct Celda * arriba;
    struct Celda * abajo;
}Celda;

struct NodoCola{
    int estado;
    struct NodoCola * siguiente;
}NodoCola;

struct Cola{
    struct NodoCola * frente;
    struct NodoCola * final;
}Cola;

struct NodoLaberinto{
    int numNodo;
    int estado;
    int padre;
    int costo;
    int profundidad;
    int * camino;
    struct NodoLaberinto * siguiente;
}NodoLaberinto;

struct ColaNodosCreados{
    struct NodoLaberinto * frente;
    struct NodoLaberinto * final;
}ColaNodosCreados;

//Funciones para el laberinto
struct Celda * crearCelda(int);
void crearLaberinto(struct Celda *);
void crearFila(struct Celda *);
void unirFilas(struct Celda * fila_1,struct Celda * fila_2);
void mostrarLaberinto(struct Celda *);
void establecerVecinos(struct Celda *);
void asignarVecinos(struct Celda *);
int buscarEstado(struct Celda*,int);

//Funciones para la cola
struct Cola * crearCola();
int vacia(struct Cola *);
void insertarNodoCola(struct Cola *,int);
void pop(struct Cola *);

//Funciones para el algoritmo
struct NodoLaberinto * crearNodo(int);
struct ColaNodosCreados * crearColaNodos();
void insertarNodoLaberinto(struct ColaNodosCreados *,struct NodoLaberinto*);
void imprimirNodo(struct NodoLaberinto *);
void busquedaPrimeroAnchura(struct Celda *,int,int);

void insertarVecinos(struct Cola *,struct Cola *,int, struct Celda*,int);
int obtenerCosto(struct ColaNodosCreados *,int);
int obtenerProfundidad(struct ColaNodosCreados *,int);
void construirCamino(struct NodoLaberinto *,struct ColaNodosCreados *,int);

int main(){
    struct Celda * laberinto;
    int estadoInicial,estadoFinal;

    crearLaberinto(laberinto);

    printf("\nEstado inicial...");
    scanf("%d",&estadoInicial);
    printf("Estado final...");
    scanf("%d",&estadoFinal);

    busquedaPrimeroAnchura(laberinto,estadoInicial,estadoFinal);

    return 0;
}


void busquedaPrimeroAnchura(struct Celda * laberinto,int estadoInicial,int estadoFinal){
    struct Cola * Cola, * Padres;
    struct ColaNodosCreados * nodos;
    struct NodoLaberinto * nodo0;
    int numNodo=0,test=0;

    Cola=crearCola();
    Padres=crearCola();
    nodos=crearColaNodos();

    //Se crea el Nodo 0
    insertarNodoCola(Cola,estadoInicial);
    nodo0=crearNodo(estadoInicial);
    if(nodo0->estado == estadoFinal)
        test=1;
    insertarNodoLaberinto(nodos,nodo0);
    imprimirNodo(nodo0);

    //Actualizar la cola
    insertarVecinos(Cola,Padres,numNodo,laberinto,nodo0->estado);
    numNodo+=1;
    pop(Cola);
    while(test == 0){
        //Nodo n
        //Se crea n nuevo nodo
        struct NodoLaberinto * nodoN;
        nodoN=crearNodo(numNodo);
        nodoN->estado=Cola->frente->estado;
        nodoN->padre=Padres->frente->estado;
        nodoN->costo=obtenerCosto(nodos,numNodo)+1;
        nodoN->profundidad=obtenerProfundidad(nodos,numNodo)+1;
        construirCamino(nodoN,nodos,numNodo);
        insertarNodoLaberinto(nodos,nodoN);

        if(nodoN->estado == estadoFinal){
            test=1;
            printf("\nLlegue al nodo\n");
        }

        insertarVecinos(Cola,Padres,numNodo,laberinto,nodoN->estado);
        numNodo+=1;
        insertarNodoLaberinto(nodos,nodoN);
        pop(Cola);
        pop(Padres);
        imprimirNodo(nodoN);
    }

    printf("Estado inicial %d, estado final %d\n",estadoInicial, estadoFinal);
}

//Funciones para el laberinto
struct Celda * crearCelda(int estado){
    struct Celda * nueva;
    nueva=(struct Celda *)malloc(sizeof(struct Celda));

    nueva->estado=estado;
    nueva->vecinos=(int *)calloc(4,sizeof(int));
    nueva->izquierda=NULL;
    nueva->derecha=NULL;
    nueva->arriba=NULL;
    nueva->abajo=NULL;

    return nueva;
}

void crearLaberinto(struct Celda * primerFila){
    struct Celda * segundaFila,* terceraFila, *cuartaFila;
    int i;

    primerFila = crearCelda(1);
    segundaFila = crearCelda(5);
    terceraFila = crearCelda(9);
    cuartaFila = crearCelda(13);

    for(i=0;i<4;i++){
        crearFila(primerFila);
        crearFila(segundaFila);
        crearFila(terceraFila);
        crearFila(cuartaFila);
    }

    unirFilas(primerFila,segundaFila);
    unirFilas(segundaFila,terceraFila);
    unirFilas(terceraFila,cuartaFila);

    establecerVecinos(primerFila);
    mostrarLaberinto(primerFila);
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

void mostrarLaberinto(struct Celda * primera){
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

void insertarVecinos(struct Cola * cola,struct Cola * padres,int numNodo,struct Celda * laberinto, int estado){
    int i,j;
    struct Celda * actual, *inicio;

    actual=laberinto;
    for(i=0;i<4;i++){
        inicio=actual->abajo;
        for(j=0;j<4;j++){
            if(actual->estado=estado){
                break;
            }
            actual=actual->derecha;
        }
        actual=inicio;
    }

    i=0;
    while(actual->vecinos[i]!=0){
        printf("Vecino %d del nodo %d",actual->vecinos[i],numNodo);
        insertarNodoCola(cola,actual->vecinos[i]);
        insertarNodoCola(padres,numNodo);
        i++;
    }
}

//Funciones para la cola
struct Cola * crearCola(){
    struct Cola *  cola;
    cola=(struct Cola*)malloc(sizeof(struct Cola));
    cola->frente=NULL;
    cola->final=NULL;

    return cola;
}

int vacia(struct Cola * cola){
    return cola->frente == NULL? 1 : 0;
}

void insertarNodoCola(struct Cola * cola,int estado){
    struct NodoCola * nuevo;
    nuevo=(struct NodoCola *)malloc(sizeof(struct NodoCola));
    nuevo->estado=estado;
    nuevo->siguiente=NULL;

    if(cola->frente==NULL){
        cola->frente=nuevo;
    }else{
        cola->final->siguiente=nuevo;
    }
    cola->final=nuevo;
}

void pop(struct Cola * cola){
    struct NodoCola * nuevo;
    nuevo=(struct NodoCola *)malloc(sizeof(struct NodoCola));

    if(cola->frente == NULL){
        return;
    }else{
        nuevo=cola->frente;
        cola->frente=nuevo->siguiente;
        free(nuevo);
    }
}


//Funciones para el algoritmo
struct NodoLaberinto * crearNodo(int estado){
    struct NodoLaberinto * nuevo;
    nuevo=(struct NodoLaberinto *)malloc(sizeof(struct NodoLaberinto));

    nuevo->numNodo=0;
    nuevo->estado=estado;
    nuevo->padre=0;
    nuevo->costo=0;
    nuevo->profundidad=0;
    nuevo->camino=(int*)malloc(sizeof(int));
    nuevo->camino[0]=estado;
    nuevo->siguiente=NULL;

    return nuevo;
}

struct ColaNodosCreados * crearColaNodos(){
    struct ColaNodosCreados *  nodo;
    nodo=(struct ColaNodosCreados*)malloc(sizeof(struct ColaNodosCreados));
    nodo->frente=NULL;
    nodo->final=NULL;

    return nodo;
}

void insertarNodoLaberinto(struct ColaNodosCreados * cola,struct NodoLaberinto * nodo){
    struct NodoLaberinto * nuevo;
    int i=0;
    nuevo=crearNodo(nodo->numNodo);
    nuevo->estado=nodo->estado;
    nuevo->padre=nodo->padre;
    nuevo->costo=nodo->costo;
    nuevo->profundidad=nodo->profundidad;
    while(nodo->camino[i]!=0){
        nuevo->camino[i]=nodo->camino[i];
        i++;
    }
    nuevo->siguiente=NULL;

    if(cola->frente==NULL){
        cola->frente=nuevo;
    }else{
        cola->final->siguiente=nuevo;
    }
    cola->final=nuevo;
}

void imprimirNodo(struct NodoLaberinto * nodo){

    int i=0;
    printf("\nNodo:\t%d\n",nodo->numNodo);
    printf("\tEstado:\t%d\n",nodo->estado);
    printf("\tPadre:\t%d\n",nodo->padre);
    printf("\tCosto:\t%d\n",nodo->costo);
    printf("\tProfundidad:\t%d\n",nodo->profundidad);
    printf("\tCamino:\t[");
    while(nodo->camino[i]!=0){
        printf("%d",nodo->camino[i]);
        i++;
    }
    printf("]\n");
}

int obtenerCosto(struct ColaNodosCreados * nodos,int numNodo){
    struct NodoLaberinto * actual;
    actual=nodos->frente;

    while(actual){
        if(actual->numNodo==numNodo)
            return actual->costo;
        actual=actual->siguiente;
    }
}

int obtenerProfundidad(struct ColaNodosCreados * nodos,int numNodo){
    struct NodoLaberinto * actual;
    actual=nodos->frente;

    while(actual){
        if(actual->numNodo==numNodo)
            return actual->profundidad;
        actual=actual->siguiente;
    }
}

void construirCamino(struct NodoLaberinto * nodoNuevo,struct ColaNodosCreados * nodos,int numNodo){
    struct NodoLaberinto * actual;
    int * camino;
    int i=0;

    actual=nodos->frente;
    camino=(int*)malloc(sizeof(int));

    while(actual){
        if(actual->numNodo==numNodo){
            while(actual->camino[i]!=0){
                nodoNuevo->camino[i]=actual->camino[i];
                i++;
            }
        }
    }
    nodoNuevo->camino[i]=numNodo;
}