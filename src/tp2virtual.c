#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recorder.h"


int main(int argc, char* argv[]){
    /*Leitura e configuração*/
    struct Recorder rec;

    char* alg = argv[1];
    char* filename = argv[2];

    unsigned page_size = atoi(argv[3]);
    unsigned mem_size = atoi(argv[4]);

    printf("%s, %s, %d, %d", alg, filename, page_size, mem_size);

    /*switch de algoritmos*/
    if (strcmp(alg, "lru") == 0) {


    } else if(strcmp(alg, "2a")){


    } else if(strcmp(alg, "fifo")){


    } else if(strcmp(alg, "random")) {
        

    } else {
        printf("Erro, algoritmo inválido.");

    }
    
    return 0;
}