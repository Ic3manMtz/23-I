/*
** pipe.c -- un ejemplo de uso de pipe para 
**            comunicar procesos por env�o de mensajes
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define WRITE 1
#define READ  0

int main(){
    int hijo_padre[2];
    char buf[30];
    int status, pid;


    status = pipe(hijo_padre);
    if (status == -1 ){
        printf("ERROR al crear el pipe");
        exit(1);
    }

    if ((pid = fork()) == -1 ) {
        printf("ERROR al clonar el proceso");
        exit(1);
    }

    if (pid == 0) {
        close(hijo_padre[READ]); // Cierra el que no va a usar
        printf(" Hijo: Escribo en la tuberia\n");
        write(hijo_padre[WRITE], "test", 5);
        close(hijo_padre[WRITE]);
        printf(" Hijo: termino\n");
        exit(0);
    } else {
        close(hijo_padre[WRITE]); // Cierra el que no va a usar
        printf("Padre: leyendo de la tuberia\n");
        read(hijo_padre[READ], buf, 5);
        printf("Padre lei: read \"%s\"\n", buf);
        printf("Padre : termino\n");
        wait(NULL);
        close(hijo_padre[READ]);
    }
    return 0;
}
