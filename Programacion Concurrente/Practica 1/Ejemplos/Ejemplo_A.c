/*
** fork1.c -- demuestra el uso de fork() y wait()
** Objetivo : ?
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int valor_salida, n = 3, i;
    
    
    for( i = 0; i < n; i++) {
        pid = fork();
        if (pid == 0) {
            printf("Hola mundo soy %d y mi padre es %d\n", getpid(), getppid());
            exit(i);
        }
    }

    for( i = 0; i < n; i++) {
        pid = wait(&valor_salida);
        printf("El proceso hijo %d termino con el valor %d \n",  pid, WEXITSTATUS(valor_salida));
    }

}