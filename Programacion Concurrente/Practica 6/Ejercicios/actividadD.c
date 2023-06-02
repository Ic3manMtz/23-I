/*
** pipe.c -- un ejemplo de uso de pipe para 
**            comunicar procesos por envío de mensajes
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define WRITE 1
#define READ  0

int main() {
    int emisor_receptor[2];
    int receptor_emisor[2];
    char buf[30];
    int status, pid;

    status = pipe(emisor_receptor);
    if (status == -1) {
        printf("ERROR al crear el pipe emisor_receptor");
        exit(1);
    }

    status = pipe(receptor_emisor);
    if (status == -1) {
        printf("ERROR al crear el pipe receptor_emisor");
        exit(1);
    }

    if ((pid = fork()) == -1) {
        printf("ERROR al clonar el proceso");
        exit(1);
    }

    if (pid == 0) {
        close(emisor_receptor[WRITE]);
        close(receptor_emisor[READ]);

        while (1) {
            // Leer mensaje del proceso emisor
            read(emisor_receptor[READ], buf, sizeof(buf));
            printf("Receptor: recibido \"%s\"\n", buf);

            // Verificar si el mensaje es "exit"
            if (strcmp(buf, "terminar") == 0) {
                break;
            }

            // Enviar respuesta al proceso emisor
            write(receptor_emisor[WRITE], "Mensaje recibido", sizeof("Mensaje recibido"));
        }

        close(emisor_receptor[READ]);
        close(receptor_emisor[WRITE]);
        printf("Receptor: termino\n");
        exit(0);
    } else {
        close(emisor_receptor[READ]);
        close(receptor_emisor[WRITE]);

        while (1) {
            // Leer mensaje desde la entrada estándar
            printf("Emisor: ingrese un mensaje ('terminar' para salir): ");
            fgets(buf, sizeof(buf), stdin);
            buf[strcspn(buf, "\n")] = '\0';  // Eliminar el salto de línea

            // Enviar mensaje al proceso receptor
            write(emisor_receptor[WRITE], buf, sizeof(buf));

            // Verificar si el mensaje es "exit"
            if (strcmp(buf, "terminar") == 0) {
                break;
            }

            // Leer respuesta del proceso receptor
            read(receptor_emisor[READ], buf, sizeof(buf));
            printf("Emisor: respuesta recibida \"%s\"\n", buf);
        }

        close(emisor_receptor[WRITE]);
        close(receptor_emisor[READ]);
        printf("Emisor: termino\n");
        wait(NULL);
    }

    return 0;
}
