#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winbgim.h>

//Definicion de la estructura
struct Node{
    int data;
    struct Node * up;
    struct Node * down;
    struct Node * left;
    struct Node * right;
    struct Node * back;
    struct Node * front;
}Node;

typedef struct Node * node;

/***** Prototipos de funciones *****/
node createNode(int data);
void createRow(node first);
void linkRows(node top,node bottom);
void createFace(node first,node second,node third,node fourth,node fifth);
void displayFace(node first);
void linkFaces(node front,node back);
void createCube(node first,node second,node third,node fourth,node fifth);
void displayCube(node first);
void GUI(node first);
void drawNode(int data);
void drawLinks(int x,int y,int i,int j,int k,int color);

/***** Main *****/
int main(int argc, char const *argv[]){
    /***** Declaracion de variables *****/
    //Creacion de la primer cara
    //first_1 : primer nodo de la primer fila de la primer cara
    //second_1 : primer nodo de la segunda fila de la primer cara
    //third_1 : primer nodo de la tercer fila de la primer cara
    //fourth_1 : primer nodo de la cuarta fila de la primer cara
    //fifth_1 : primer nodo de la quinta fila de la primer cara
    //data : numero que tendra cada nodo
    node first_1,second_1,third_1,fourth_1,fifth_1;
    int data;
    data=0;
    first_1=createNode((5*data++)+1);
    second_1=createNode((5*data++)+1);
    third_1=createNode((5*data++)+1);
    fourth_1=createNode((5*data++)+1);
    fifth_1=createNode((5*data++)+1);
    createFace(first_1,second_1,third_1,fourth_1,fifth_1);
    //Creacion de la segunda cara
    //first_2 : primer nodo de la primer fila de la segunda cara
    //second_2 : primer nodo de la segunda fila de la segunda cara
    //third_2 : primer nodo de la tercer fila de la segunda cara
    //fourth_2 : primer nodo de la cuarta fila de la segunda cara
    //fifth_2 : primer nodo de la quinta fila de la segunda cara
    node first_2,second_2,third_2,fourth_2,fifth_2;
    first_2=createNode((5*data++)+1);
    second_2=createNode((5*data++)+1);
    third_2=createNode((5*data++)+1);
    fourth_2=createNode((5*data++)+1);
    fifth_2=createNode((5*data++)+1);
    createFace(first_2,second_2,third_2,fourth_2,fifth_2);
    //Creacion de la tercer cara
    //first_3 : primer nodo de la primer fila de la tercer cara
    //second_3 : primer nodo de la segunda fila de la tercer cara
    //third_3 : primer nodo de la tercer fila de la tercer cara
    //fourth_3 : primer nodo de la cuarta fila de la tercer cara
    //fifth_3 : primer nodo de la quinta fila de la tercer cara
    node first_3,second_3,third_3,fourth_3,fifth_3;
    first_3=createNode((5*data++)+1);
    second_3=createNode((5*data++)+1);
    third_3=createNode((5*data++)+1);
    fourth_3=createNode((5*data++)+1);
    fifth_3=createNode((5*data++)+1);
    createFace(first_3,second_3,third_3,fourth_3,fifth_3);
    //Creacion de la cuarta cara
    //first_4 : primer nodo de la primer fila de la cuarta cara
    //second_4 : primer nodo de la segunda fila de la cuarta cara
    //third_4 : primer nodo de la tercer fila de la cuarta cara
    //fourth_4 : primer nodo de la cuarta fila de la cuarta cara
    //fifth_4 : primer nodo de la quinta fila de la cuarta cara
    node first_4,second_4,third_4,fourth_4,fifth_4;
    first_4=createNode((5*data++)+1);
    second_4=createNode((5*data++)+1);
    third_4=createNode((5*data++)+1);
    fourth_4=createNode((5*data++)+1);
    fifth_4=createNode((5*data++)+1);
    createFace(first_4,second_4,third_4,fourth_4,fifth_4);
    //Creacion de la quinta cara
    //first_5 : primer nodo de la primer fila de la quinta cara
    //second_5 : primer nodo de la segunda fila de la quinta cara
    //third_5 : primer nodo de la tercer fila de la quinta cara
    //fourth_5 : primer nodo de la cuarta fila de la quinta cara
    //fifth_5 : primer nodo de la quinta fila de la quinta cara
    node first_5,second_5,third_5,fourth_5,fifth_5;
    first_5=createNode((5*data++)+1);
    second_5=createNode((5*data++)+1);
    third_5=createNode((5*data++)+1);
    fourth_5=createNode((5*data++)+1);
    fifth_5=createNode((5*data++)+1);
    createFace(first_5,second_5,third_5,fourth_5,fifth_5);
    createCube(first_1,first_2,first_3,first_4,first_5);
    displayCube(first_1);
    GUI(first_1);
    return 0;
}

/***** Funciones *****/
//Asigna espacio de memoria para la estructura
node createNode(int data){
    node nw;
    nw=(node)malloc(sizeof(Node));
    if(nw==NULL){
        printf("Memoria insuficiente\n");
        exit(1);
    }
    nw->data=data;
    nw->up=NULL;
    nw->down=NULL;
    nw->left=NULL;
    nw->right=NULL;
    nw->back=NULL;
    nw->front=NULL;
    return nw;
}

//Crea los nodos necesarios para una fila
void createRow(node first){
    node nw,current;
    int i;
    current=first;
    for(i=0;i<4;i++){
        nw=createNode(current->data+1);
        nw->left=current;
        current->right=nw;
        current=current->right;
    }
}

//Crea los vinculos de dos filas
void linkRows(node top,node bottom){
    node currentTop,currentBottom;
    int i;
    currentTop=top;
    currentBottom=bottom;
    while(currentTop!=NULL){
        currentTop->down=currentBottom;
        currentBottom->up=currentTop;
        currentTop=currentTop->right;
        currentBottom=currentBottom->right;
    }
}

//Vincula todas las filas recibidas para crear una cara
void createFace(node first,node second,node third,node fourth,node fifth){
    createRow(first);
    createRow(second);
    createRow(third);
    createRow(fourth);
    createRow(fifth);
    linkRows(first,second);
    linkRows(second,third);
    linkRows(third,fourth);
    linkRows(fourth,fifth);
}

//Muestra en la terminal los valores de cada nodo de una cara
void displayFace(node first){
    node current,start;
    int i,j;
    current=first;
    for(i=0;i<5;i++){
        start=current->down;
        for(j=0;j<5;j++){
            printf("%d\t",current->data);
            current=current->right;
        }
        printf("\n");
        current=start;
    }
}

//Crea los vinculos de dos caras
void linkFaces(node front,node back){
    node currentFront,currentBack,startFront,startBack;
    int i,j;
    currentFront=front;
    currentBack=back;
    for(i=0;i<5;i++){
        startFront=currentFront->down;
        startBack=currentBack->down;
        for(j=0;j<5;j++){
            currentFront->back=currentBack;
            currentBack->front=currentFront;
            currentFront=currentFront->right;
            currentBack=currentBack->right;
        }
        currentFront=startFront;
        currentBack=startBack;
    }
}

//Vincula todas las caras recibidas para crear un cubo
void createCube(node first,node second,node third,node fourth,node fifth){
    linkFaces(first,second);
    linkFaces(second,third);
    linkFaces(third,fourth);
    linkFaces(fourth,fifth);
}

//Muestra en la terminal los valores de cada nodo de un cubo
void displayCube(node first){
    int i,j,k;
    node current,row,face;
    current=first;
    for(i=0;i<5;i++){
        face=current->back;
        for(j=0;j<5;j++){
            row=current->down;
            for(k=0;k<5;k++){
                printf("%d\t",current->data);
                current=current->right;
            }
            printf("\n");
            current=row;
        }
        printf("\n");
        current=face;
    }
}

//Crea una ventana para dibujar cada nodo de un cubo
void GUI(node first){
    node current,row,face;
    int i,j,k,x,y;
    initwindow(1350,1050);
    setbkcolor(0);
    current=first;
    setcolor(9);
    line(30,200,110,200);
    outtextxy(0,195,"Primero");
    for(i=0;i<5;i++){
        face=current->back;
        for(j=0;j<5;j++){
            row=current->down;
            for(k=0;k<5;k++){
                x=110+(200*k)+(40*i);
                y=200+(200*j)-(40*i);
                moveto(x,y);
                setfillstyle(1,7+i);
                fillellipse(x+5,y+5,10,17);
                drawNode(current->data);
                drawLinks(x,y,i,j,k,7+i);
                current=current->right;
            }
            current=row;
        }
        current=face;
    }
    getch();
}

//Dibuja un nodo
void drawNode(int data){
    setcolor(15);
    char str[120];
    char number[3];
    strcpy(str,"");
    itoa(data,number,10);
    strcat(str,number);
    outtext(str);
}

//Dibuja todos los vinculos de un nodo
void drawLinks(int x,int y,int i,int j,int k,int color){
    if(k<4){
        setcolor(color);
        line(x+20,y,x+190,y);
        line(x+20,y+7,x+190,y+7);
    }else{
        setcolor(9);
        line(x+20,y+5,x+190,y+5);
        outtextxy(x+190,y,"NULL");
    }
    if(j<4){
        setcolor(color);
        line(x,y+20,x,y+190);
        line(x+7,y+20,x+7,y+190);
    }
    if(i<4){
        setcolor(color);
        line(x,y,x+35,y-35);
        line(x+7,y,x+42,y-35);
    }
}