#include "page.h"

#ifndef TABLE_H
#define TABLE_H

#define PAGE_TABLE_SIZE 2097152 // Tamanho da tabela de páginas [2**21]

/**
 * @brief Estrutura que representa uma tabela de páginas
 * 
 * @param page_table Vetor de páginas de tamanho 2**21
*/
struct Table{
    Page page_table[PAGE_TABLE_SIZE];

    /*A estrutura de dados para representar cada quadro físico deve conter campos
      para registrar atributos como páagina referenciada, instante do último acesso,
      página alterada, etc. (os detalhes são parte da implementação e vão depender
      da forma como vocês implementarem cada algoritmo).  
    */

} table;


#endif