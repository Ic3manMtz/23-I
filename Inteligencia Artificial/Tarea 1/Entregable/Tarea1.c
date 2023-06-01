#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo{
    int numNodo;
    int estado;
    int padre;
    int costo;
    int profundidad;
    struct Arreglo * camino;
    struct Nodo * siguiente;
}Nodo;

typedef struct Cola{ 
    struct Nodo * frente;
    struct Nodo * final;
    int tam;
}Cola;

typedef struct Arreglo{
    int * datos;
}Arreglo;

typedef Nodo * nodo; 
typedef Cola * cola;
typedef Arreglo * arreglo;

void llenarLaberinto(int [][3]);
cola crearCola();
nodo crearNodo();
int vacia(cola);
void encolar(cola,nodo);
int sacar(cola);
void mostrarNodo(nodo);
arreglo crearArreglo();
void mostrarArreglo(arreglo);
void pop(arreglo);
void push(arreglo c, int n);
int obtenerCosto(cola, int);
int obtenerProfundidad(cola, int);
arreglo obtenerCamino(cola, int);

int main(){
    //Declaración de variables
    int laberinto[16][3];
    arreglo Cola, Padres;
    cola nodos;
    int numNodo,test,estadoInicial,estadoFinal;

    //Inicialización de variables
    llenarLaberinto(laberinto);
    Cola=crearArreglo();
    Padres=crearArreglo();
    nodos=crearCola();
    numNodo=0;
    test=0;
    /*
        printf("\nIndique el estado inicial...");
        scanf("%d",&estadoInicial);
        printf("Indique el estado final...");
        scanf("%d",&estadoFinal);
    */
    estadoInicial=6;
    estadoFinal=9;

    //Creación Nodo 0
    Cola->datos[0]=estadoInicial;
    nodo nodo0=crearNodo();
    nodo0->estado=estadoInicial;
    nodo0->camino->datos[0]=estadoInicial;
    if(estadoInicial==estadoFinal){
        test=1;
    }
    encolar(nodos,nodo0);
    printf("\nCola = ");
    mostrarArreglo(Cola);
    printf("\tPadres = ");
    mostrarArreglo(Padres);
    mostrarNodo(nodo0);

    //Actualiza Cola
    if(laberinto[nodo0->estado-1][2]!=-1){
        push(Cola,laberinto[nodo0->estado-1][2]);
        push(Padres,numNodo+1);
    }
    if(laberinto[nodo0->estado-1][1]!=-1){
        push(Cola,laberinto[nodo0->estado-1][1]);
        push(Padres,numNodo+1);
    }
    if(laberinto[nodo0->estado-1][0]!=-1){
        push(Cola,laberinto[nodo0->estado-1][0]);
        push(Padres,numNodo+1);
    }
    numNodo++;
    pop(Cola);
    printf("\nCola = ");
    mostrarArreglo(Cola);
    printf("\tPadres = ");
    mostrarArreglo(Padres);

    while(test==0){
        nodo nuevo=crearNodo();
        nuevo->numNodo=numNodo;
        nuevo->estado=Cola->datos[0];
        nuevo->padre=Padres->datos[0];
        nuevo->costo=obtenerCosto(nodos,Padres->datos[0])+1;
        nuevo->profundidad=obtenerProfundidad(nodos,Padres->datos[0])+1;
        nuevo->camino=obtenerCamino(nodos,Padres->datos[0]);
        push(nuevo->camino,Cola->datos[0]);

        if(nuevo->estado == estadoFinal){
            test=1;
            printf("\nLlegue la nodo: ");
            break;
        }

        if(laberinto[nodo0->estado-1][2]!=-1){
            push(Cola,laberinto[nodo0->estado-1][2]);
            push(Padres,numNodo);
        }
        if(laberinto[nodo0->estado-1][1]!=-1){
            push(Cola,laberinto[nodo0->estado-1][1]);
            push(Padres,numNodo);
        }
        if(laberinto[nodo0->estado-1][0]!=-1){
            push(Cola,laberinto[nodo0->estado-1][0]);
            push(Padres,numNodo);
        }

        numNodo++;
        encolar(nodos,nuevo);
        pop(Cola);
        pop(Padres);
    }
    return 0;
}

void llenarLaberinto(int laberinto[][3]){
    //Celda 1
    laberinto[0][0]=2;
    laberinto[0][1]=-1;
    laberinto[0][2]=-1;
    //Celda 2
    laberinto[1][0]=1;
    laberinto[1][1]=3;
    laberinto[1][2]=6;
    //Celda 3
    laberinto[2][0]=2;
    laberinto[2][1]=4;
    laberinto[2][2]=-1;
    //Celda 4
    laberinto[3][0]=3;
    laberinto[3][1]=8;
    laberinto[3][2]=-1;
    //Celda 5
    laberinto[4][0]=6;
    laberinto[4][1]=9;
    laberinto[4][2]=-1;
    //Celda 6
    laberinto[5][0]=2;
    laberinto[5][1]=5;
    laberinto[5][2]=-1;
    //Celda 7
    laberinto[6][0]=8;
    laberinto[6][1]=11;
    laberinto[6][2]=-1;
    //Celda 8
    laberinto[7][0]=4;
    laberinto[7][1]=7;
    laberinto[7][2]=-1;
    //Celda 9
    laberinto[8][0]=5;
    laberinto[8][1]=10;
    laberinto[8][2]=-1;
    //Celda 10
    laberinto[9][0]=9;
    laberinto[9][1]=14;
    laberinto[9][2]=-1;
    //Celda 11
    laberinto[10][0]=7;
    laberinto[10][1]=12;
    laberinto[10][2]=-1;
    //Celda 12
    laberinto[11][0]=11;
    laberinto[11][1]=16;
    laberinto[11][2]=-1;
    //Celda 13
    laberinto[12][0]=14;
    laberinto[12][1]=-1;
    laberinto[12][2]=-1;
    //Celda 14
    laberinto[13][0]=10;
    laberinto[13][1]=13;
    laberinto[13][2]=-1;
    //Celda 15
    laberinto[14][0]=14;
    laberinto[14][1]=-1;
    laberinto[14][2]=-1;
    //Celda 16
    laberinto[15][0]=12;
    laberinto[15][1]=-1;
    laberinto[15][2]=-1;
}

cola crearCola(){
    cola c=(cola)malloc(sizeof(Cola));
    c->frente=NULL;
    c->final=NULL;
    c->tam=0;

    if(c==NULL){exit(1);}

    return c;
}

nodo crearNodo(){
    nodo nuevo;
    nuevo=(nodo)malloc(sizeof(Nodo));

    nuevo->numNodo=0;
    nuevo->estado=0;
    nuevo->padre=0;
    nuevo->costo=0;
    nuevo->profundidad=0;
    nuevo->camino=crearArreglo();
    nuevo->camino->datos[0]=0;
    nuevo->siguiente=NULL;
     
    return nuevo;
}

int vacia(cola c){
    return c->frente==NULL? 1 : 0;
}

void encolar(cola c,nodo n){
    nodo nuevo;
    nuevo=(nodo)malloc(sizeof(Nodo));
    nuevo=crearNodo();
    nuevo=n;

    if(c->frente==NULL){
        c->frente=nuevo;
    }else{
        c->final->siguiente=nuevo;
    }
    c->tam+=1;
    c->final=nuevo;
}

int sacar(cola c){
    int numNodo;
    nodo nuevo;
    nuevo=(nodo)malloc(sizeof(Nodo));

    if(c->frente==NULL){
        printf("\nCola vacía\n");
        exit(1);
    }

    nuevo=c->frente;
    numNodo=nuevo->numNodo;
    c->frente=nuevo->siguiente;
    free(nuevo);
    c->tam-=1;
    return numNodo;
}

void mostrarNodo(nodo n){
    int i=0;
    printf("\nNodo:\t%d\n",n->numNodo);
    printf("\tEstado:\t%d\n",n->estado);
    printf("\tPadre:\t%d\n",n->padre);
    printf("\tCosto:\t%d\n",n->costo);
    printf("\tProfundidad:\t%d\n",n->profundidad);
    printf("\tCamino:\t[");
    while(n->camino->datos[i]!=0){
        printf("%d ",n->camino->datos[i]);
        i++;
    }
    printf("]\n");
}

arreglo crearArreglo(){
	arreglo a;

	a = (arreglo)malloc(sizeof(Arreglo));

	a->datos = (int*)malloc(sizeof(int));

	return a;
}

void mostrarArreglo(arreglo a){
	int i;

	for(i = 0;a->datos[i];i++){
        if(a->datos[i]==1){
            printf("|%d|",a->datos[i]-1);
        }else{
		    printf("|%d|",a->datos[i]);
        }
	}
}

void pop(arreglo c){
    int tam,i;
    tam=(sizeof(c->datos)/sizeof(*c->datos));

    for(i=0;i<tam;i++){
        c->datos[i]=c->datos[i+1];
    }
    c->datos[i]=0;
}

void push(arreglo c, int n){
    int i=0;
    while(c->datos[i]){
        i++;
    }
    c->datos[i]=n;
}

int obtenerCosto(cola nodos, int padre){
    nodo actual;
    actual=nodos->frente;

    if(padre==1)
        padre=0;
    while(actual!=NULL){
        if(actual->numNodo==padre)
            return actual->costo;
        actual=actual->siguiente;
    }
}

int obtenerProfundidad(cola nodos, int padre){
    nodo actual;
    actual=nodos->frente;

    if(padre==1)
        padre=0;
    while(actual!=NULL){
        if(actual->numNodo==padre)
            return actual->costo;
        actual=actual->siguiente;
    }
}

arreglo obtenerCamino(cola nodos, int padre){
    nodo actual;
    actual=nodos->frente;

    if(padre==1)
        padre=0;
    while(actual!=NULL){
        if(actual->numNodo==padre)
            return actual->camino;
        actual=actual->siguiente;
    }
}
