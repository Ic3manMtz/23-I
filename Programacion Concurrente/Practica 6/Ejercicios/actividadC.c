/*
** pipe.c -- un ejemplo de uso de pipe para 
**            comunicar procesos por envío de mensajes
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define WRITE 1
#define READ  0

int main() {
    int hijo_padre[2];
    char buf[30];
    int status, pid, iteracion;
    iteracion = 0;

    status = pipe(hijo_padre);
    if (status == -1) {
        printf("ERROR al crear el pipe");
        exit(1);
    }

    if ((pid = fork()) == -1) {
        printf("ERROR al clonar el proceso");
        exit(1);
    }

    if (pid == 0) {
        close(hijo_padre[READ]); // Cierra el que no va a usar
        do {
            printf(" Hijo: Escribo en la tuberia el caracter %d\n", iteracion);

            // Convierte el número en una cadena de caracteres
            snprintf(buf, sizeof(buf), "%d", iteracion);

            // Escribe el mensaje en la tubería
            write(hijo_padre[WRITE], buf, sizeof(buf));
            iteracion++;
        } while (iteracion < 10);  //Cambiar este número por la cantidad deseada de mensajes

        close(hijo_padre[WRITE]);
        printf(" Hijo: termino\n");
        exit(0);
    } else {
        close(hijo_padre[WRITE]); // Cierra el que no va a usar
        printf("Padre: leyendo de la tuberia\n");
        while (read(hijo_padre[READ], buf, sizeof(buf)) > 0) {
            printf("Padre lei: read \"%s\"\n", buf);
        }
        printf("Padre: termino\n");
        wait(NULL);
        close(hijo_padre[READ]);
    }
    return 0;
}
