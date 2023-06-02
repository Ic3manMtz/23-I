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

int secuencia_collatz(long long int n);

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

        long long int num;
        int longitud_max = 0;
        int numero_max = 0;

        while (1) {
            // Leer número del proceso emisor
            read(emisor_receptor[READ], &num, sizeof(num));

            // Verificar si el número es 0 (señal de finalización)
            if (num == 0) {
                break;
            }

            // Calcular la longitud de la secuencia de Collatz para el número
            int length = secuencia_collatz(num);

            // Verificar si la longitud actual es la máxima
            if (length > longitud_max) {
                longitud_max = length;
                numero_max = num;
            }
        }

        // Enviar el número con la secuencia más larga al proceso emisor
        write(receptor_emisor[WRITE], &numero_max, sizeof(numero_max));

        close(emisor_receptor[READ]);
        close(receptor_emisor[WRITE]);
        printf("Receptor: terminó\n");
        exit(0);
    } else {
        close(emisor_receptor[READ]);
        close(receptor_emisor[WRITE]);

        long long int num;

        while (1) {
            // Leer número desde la entrada estándar
            printf("Emisor: ingrese un número (0 para salir): ");
            scanf("%lld", &num);

            // Enviar el número al proceso receptor
            write(emisor_receptor[WRITE], &num, sizeof(num));

            // Verificar si el número es 0 (señal de finalización)
            if (num == 0) {
                break;
            }
        }

        // Leer el número con la secuencia más larga del proceso receptor
        int numero_max;
        read(receptor_emisor[READ], &numero_max, sizeof(numero_max));
        printf("Emisor: el número con la secuencia de Collatz más larga es %d\n", numero_max);

        close(emisor_receptor[WRITE]);
        close(receptor_emisor[READ]);
        printf("Emisor: terminó\n");
        wait(NULL);
    }

    return 0;
}

int secuencia_collatz(long long int n){
    int count = 0;

    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = (3 * n) + 1;
        }
        count++;
    }

    return count;
}
