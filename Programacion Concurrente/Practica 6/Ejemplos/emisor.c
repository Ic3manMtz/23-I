/*  Proceso emisor */
/*  Crea un pipe nombrado y escribe en el */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


int main(){
    int i, desc_tub, num;
        
    /*  Se crea la tuber�a */
    if (mknod("canal", S_IFIFO|0666,0)  == -1){
        perror("No se pudo crear el pipe");
        exit(-1);
    }

    /* Se abre para escritura */
    if ((desc_tub = open("canal",O_WRONLY)) == -1){    
        perror("No se pudo abrir el pipe");
        exit(-1);
    }

    /* Escribe en el pipe */    
    printf("Emisor: Escribo en la tuberia\n");
    write(desc_tub, "test", 4); 
    printf("Emisor: termino\n");
    
    /* Se cierra el pipe */
    close(desc_tub);
    system("rm canal\n");
    exit(0);
}

