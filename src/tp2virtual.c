#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recorder.h"
#include "page.h"


/**
 * @brief Calcula o offset S das páginas, com base no tamanho.
 * 
 * @param page_size Tamanho da página.
 * 
 * @return S, o offset.
*/
unsigned size_calculator(unsigned page_size){
    unsigned tmp, s;

    s = 0;
    tmp = page_size;
    
    while (tmp > 1) {
        tmp = tmp >> 1;
        s++;
    } 

    return s;
}; 


/**
 * @brief Calcula o índice da página na tabela de páginas.
 * 
 * @param addr Endereço lógico
 * @param s Offset 
 * 
 * @return Índice da tabela de páginas
*/
unsigned id_calculator(unsigned addr, unsigned s){
    return addr >> s;
}


/**
 * @brief Simula o funcionamento de uma memória virtual através do algoritmo LRU
 * 
 * @param rec Ponteiro para o registrador de atividades 
 * @param page_size Tamanho da página (em KB)
 * @param mem_size Tamanho da memória total disponível
 * @param filename Arquivo .log com todos os acessos de leitura e escrita da memória
*/
void simulate_lru(struct Recorder* rec, unsigned page_size, unsigned mem_size, char* filename){
    unsigned addr;
    char rw;
    
    FILE* file = fopen(filename, "r");    

    while(fscanf(file,"%x %c",&addr,&rw) == 2){
        if(strcmp("R", rw)){
            

        } else {


        }
    };
}


/**
 * @brief Simula o funcionamento de uma memória virtual através do algoritmo Segunda Chance
 * 
 * @param rec Ponteiro para o registrador de atividades 
 * @param page_size Tamanho da página (em KB)
 * @param mem_size Tamanho da memória total disponível
 * @param filename Arquivo .log com todos os acessos de leitura e escrita da memória
*/
void simulate_2a(struct Recorder* rec, unsigned page_size, unsigned mem_size, char* filename){
    unsigned addr;
    char rw;
    
    FILE* file = fopen(filename, "r");

    while(fscanf(file,"%x %c",&addr,&rw) == 2){
        
        if(strcmp("R", rw)){
            

        } else {


        }
    };
}


/**
 * @brief Simula o funcionamento de uma memória virtual através do algoritmo FIFO
 * 
 * @param rec Ponteiro para o registrador de atividades 
 * @param page_size Tamanho da página (em KB)
 * @param mem_size Tamanho da memória total disponível
 * @param filename Arquivo .log com todos os acessos de leitura e escrita da memória
*/
void simulate_fifo(struct Recorder* rec, unsigned page_size, unsigned mem_size, char* filename){
    unsigned addr;
    char rw;
    
    FILE* file = fopen(filename, "r");

    while(fscanf(file,"%x %c",&addr,&rw) == 2){
        
        if(strcmp("R", rw)){
            

        } else {


        }
    };
}


/**
 * @brief Simula o funcionamento de uma memória virtual através do algoritmo Random
 * 
 * @param rec Ponteiro para o registrador de atividades 
 * @param page_size Tamanho da página (em KB)
 * @param mem_size Tamanho da memória total disponível
 * @param filename Arquivo .log com todos os acessos de leitura e escrita da memória
*/
void simulate_random(struct Recorder* rec, unsigned page_size, unsigned mem_size, char* filename){
    unsigned addr;
    char rw;
    
    FILE* file = fopen(filename, "r");

    while(fscanf(file,"%x %c",&addr,&rw) == 2){
        
        if(strcmp("R", rw)){
            

        } else {


        }
    };
}


int main(int argc, char* argv[]){
    /*Leitura e configuração*/
    struct Recorder rec;

    char* alg = argv[1];
    char* filename = argv[2];

    unsigned page_size = atoi(argv[3]);
    unsigned mem_size = atoi(argv[4]);

    const unsigned s = size_calculator(page_size);

    set_config(&rec, argv);


    /*switch de algoritmos*/
    if (strcmp(alg, "lru") == 0) {
        simulate_lru(&rec, page_size, mem_size, filename);

    } else if(strcmp(alg, "2a") == 0){
        simulate_2a(&rec, page_size, mem_size, filename);

    } else if(strcmp(alg, "fifo") == 0){
        simulate_fifo(&rec, page_size, mem_size, filename);

    } else if(strcmp(alg, "random") == 0) {
        simulate_random(&rec, page_size, mem_size, filename);

    } else {
        printf("Erro, algoritmo inválido.");

    }
    
    print_results(&rec);
    return 0;
}