#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

/**
 * @brief Estrutura que representa uma página da memória virtual.
 * 
 * @param id Indice da página
 * @param dirty Bit de sujo da página (pode ser 0 ou 1)
 * @param second_chance Bit de segunda chance da página (pode ser 0 ou 1)
 * @param timer Timer para o LRU
 * @param ref_bit Bit de referência (pode ser 0 ou 1)
*/
struct Page
{
    int id;
    int dirty;
    int second_chance;
    int timer;
    int ref_bit;
};

/**
 * @brief Estrutura que representa um Recorder de informações.
 * 
 * @param configuracao Vetor qua guarda o Algoritimo, Arquivo, Tamanho da página e da memória 
 * @param page_faults Inteiro para armazenar quantidade de Page Faults
 * @param dirty_writes Inteiro para armazenar quantidade de escritas em páginas sujas
*/
struct Recorder
{
    char *configuracao[4];
    int page_faults;
    int dirty_writes;
};

#endif