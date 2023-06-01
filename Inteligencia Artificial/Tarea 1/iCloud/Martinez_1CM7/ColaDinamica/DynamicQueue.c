//Gustavo Garcia Sanchez
//Martinez Buenrostro Jorge Lupito

#include <stdio.h>
#include <stdlib.h>
#include "DynamicQueue.h"


queue createQueue(){

	queue q = (queue)malloc(sizeof(Queue));
	q->front = NULL;
	q->rear = NULL;
	q->size = 0;

	if(q == NULL){
		error(1);
		exit(1);
	}

	return q;

}

int isEmpty(queue q){

	return q->front == NULL ? 1 : 0;

}

void enqueue(queue q, int e){
	node nw;
	nw = (node)malloc(sizeof(Node));
	nw->e = e;
	nw->next = NULL;

	if(q->front == NULL){
		q->front = nw;
	}else{
		q->rear->next = nw;
	}

	q->size += 1;
	q->rear = nw;

}

int dequeue(queue q){
	int e;
	node nw;
	nw = (node)malloc(sizeof(Node));

	if(q->front == NULL){
		error(2);
	}else{
		nw = q->front;
		e = nw->e;
		q->front = nw->next;
		free(nw);
		q->size -= 1;

		return e;
	}
}

void require(queue q){
	int i;
	int n;
	for(i = 0; i < 5; i++){
		printf("Introduzca el elemento %d\n",i+1 );
		scanf("%d", &n);
		enqueue(q,n);
	}
}

void display(queue q){
	int i;
	for(i = 0; i < 5; i++){
		printf("%d,",dequeue(q));
	}
	printf("\b \n");
}

void error(int e){
	char * errors[] = {"No hay memoria suficiente", "La Cola esta vacia"};

	printf("%s\n", errors[e-1]);
}
