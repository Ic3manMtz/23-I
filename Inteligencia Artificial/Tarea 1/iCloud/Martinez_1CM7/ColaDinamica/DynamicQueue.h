//Gustavo Garcia Sanchez
//Martinez Buenrostro Jorge Lupito

#ifndef _queue_
#define _queue_


typedef struct Node{
	int e;
	struct Node * next;
}Node;

typedef struct{
	struct Node * front;
	struct Node * rear;
	int size;
}Queue;

typedef Queue * queue;
typedef Node * node;

queue createQueue();
int isEmpty(queue q);
void enqueue(queue q, int e);
int dequeue(queue q);
void require(queue q);
void display(queue q);
void error(int e);

#endif