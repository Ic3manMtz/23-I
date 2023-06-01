#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <winbgim.h>

struct Node{
    int data;
    struct Node * up;
    struct Node * down;
    struct Node * left;
    struct Node * right;
    struct Node * back;
    struct Node * front;
};


struct Node * create_Node(int data);
void createRow(struct Node * start);
void bind_Rows(struct Node * row_1, struct Node * row_2);
void create_Face(struct Node * first, struct Node * second, struct Node * third, struct Node * fourth, struct Node * fifth);
void show_Row(struct Node * start);
void draw_Face(struct Node * first);


int main(int argc, char *argv[]){
    struct Node * first,* second,* third, *fourth, * fifth;
    int number,i;

    number=0;

    first= create_Node(number++);
    second= create_Node(number++ * 10);
    third= create_Node(number++ * 10);
    fourth= create_Node(number++ * 10);
    fifth= create_Node(number++ * 10);

    for(i=0;i<5;i++) {
        createRow(first);
        createRow(second);
        createRow(third);
        createRow(fourth);
        createRow(fifth);
    }

        bind_Rows(first,second);
        bind_Rows(second,third);
        bind_Rows(third,fourth);
        bind_Rows(fourth,fifth);
        draw_Face(first);

    return 0;
}

struct Node * create_Node(int data){
    struct Node * nw;
    nw=(struct Node *)malloc(sizeof(Node));

    nw->data=data;
    nw->down=NULL;
    nw->up=NULL;
    nw->left=NULL;
    nw->right=NULL;
    nw->back=NULL;
    nw->front=NULL;
}

void createRow(struct Node * start){
    struct Node * nw, *current;
    int i;

    current=start;

    for(i=0;i<4;i++){
        nw= create_Node(start->data + i + 1);
        nw->left=current;
        current->right=nw;
        current=current->right;
    }
}

void bind_Rows(struct Node * row_1, struct Node * row_2){
    struct Node * current_1,*current_2;
    int i;

    current_1=row_1;
    current_2=row_2;

    for(i=0;i<5;i++){
        current_1->down=current_2;
        current_2->up=current_1;
        current_1=current_1->right;
        current_2=current_2->right;
    }
}

void show_Row(struct Node * start){
    int i;
    struct Node * current;

    current=start;
    while(current!=NULL){
        printf("%d ",current->data);
        current=current->right;
    }
    printf("\n");
}

void draw_Face(struct Node * first){
    struct Node * current,*start;
    char str[120];
    char number[10];
    int i,j;
    initwindow(600,600);
    setbkcolor(0);
    setcolor(9);

    current=first;
    strcpy(str," ");
    for(i=0;i<5;i++){
        start=current->down;
        setcolor(9);
        line(18,50*(i+1)+5,38,50*(i+1)+5);
        for(j=0;j<5;j++){
            itoa(current->data,number,10);
            strcat(str,number);
            moveto(50*(j+1),50*(i+1));
            setcolor(7);
            outtext(str);
            current=current->right;
            strcpy(str,"");

            if(j<4){
                line(50*(j+1)+20,50*(i+1),50*(j+1)+40,50*(i+1));
                line(50*(j+1)+20,50*(i+1)+7,50*(j+1)+40,50*(i+1)+7);
            }else{
                line(50*(j+1)+20,50*(i+1)+5,50*(j+1)+40,50*(i+1)+5);
            }

            if(i<4){
                line(50*(j+1),50*(i+1)+20,50*(j+1),50*(i+1)+40);
                line(50*(j+1)+7,50*(i+1)+20,50*(j+1)+7,50*(i+1)+40);
            }
        }
        current=start;
    }
    getch();
}

