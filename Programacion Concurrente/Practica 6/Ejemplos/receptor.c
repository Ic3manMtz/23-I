/*  Proceso receptor */
/*  Lee del pipe nombrado */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int desc_tub;
    char buf[10];
    
    /*  Se abre la tuber�a */
    if ((desc_tub = open("canal",O_RDONLY)) == -1){    
        perror("No se pudo abrir el pipe");
	exit(-1);
    }

    /* Se lee el mensaje de la tuberia */ 
    printf("Receptor: Leo de la tuberia\n");
    read(desc_tub, &buf, 4); 
    buf[4]= '\0';
    printf("Lei %s \n", buf);
    printf("Receptor: termino\n");
    close(desc_tub);
    exit(0);
}

