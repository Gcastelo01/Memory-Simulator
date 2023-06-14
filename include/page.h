#ifndef PAGE_H
#define PAGE_H

/**
 * @brief Estrutura que representa uma página da memória virtual.
 * 
 * @param id Número da página
 * @param size Tamanho da página
 * @param valid Bit de validade da página (pode ser 0 ou 1)
*/
struct Page{
    unsigned id;
    unsigned size;

    int valid;
} page;


#endif