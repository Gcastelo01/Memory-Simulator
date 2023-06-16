#ifndef PAGE_H
#define PAGE_H

/**
 * @brief Estrutura que representa uma página da memória virtual.
 * 
 * @param id Indice da página
 * @param valid Bit de validade da página (pode ser 0 ou 1)
 * @param dirty Bit de sujo da página (pode ser 0 ou 1)
 * @param second_chance Bit de segunda chance da página (pode ser 0 ou 1)
*/
typedef struct Page{
    unsigned id;
    int valid;
    int dirty;
    int second_chance;
    int timer;

}Page;

#endif