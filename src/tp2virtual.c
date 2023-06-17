#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "recorder.h"
#include "page.h"


/**
 * @brief Procura um determinado endereço de memória na tabela de páginas. 
 * 
 * @param page_table Tabela de páginas
 * @param size Tamanho da tabela de páginas
 * @param id Endereço lógico de memória
 * @param timer Timer para atualizar page_table
 *
 * @return Bit indicador de hit (1 caso tenha encontrado, 0 caso não).
 */
int find(Page* page_table[], int size, unsigned id, int timer)
{

    int res = 0;
    for (int i = 0; i < size; i++)
    {
        if (id == page_table[i]->id)
        {
            res = 1;
            page_table[i]->timer = timer;
        }
    }
    printf("res = %d\n", res);
    return res;
}

/**
 *
 * @brief Adiciona um determiando endereço na tabela de páginas
 *
 * @param page_table Tabela de páginas
 * @param idx Índice de 
 *
 *
 */
int add(Page* page_table[], int idx, unsigned addr, int timer)
{
    page_table[idx]->id = addr;
    page_table[idx]->timer = timer;
}

/**
 * @brief Calcula o offset S das páginas, com base no tamanho.
 *
 * @param page_size Tamanho da página.
 *
 * @return S, o offset.
 */
unsigned size_calculator(unsigned page_size)
{
    unsigned tmp, s;

    s = 0;
    tmp = page_size;

    while (tmp > 1)
    {
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
unsigned id_calculator(unsigned addr, int s)
{
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
void simulate_lru(struct Recorder* rec, Page page_table[], int size, char *filename, int s)
{
    int hit = 0;

    int used_adresses = 0;

    FILE *file = fopen(filename, "r");

    int timer = 0;
    int lru = 0;

    unsigned addr;
    char rw;

    while (fscanf(file, "%x %c ", &addr, &rw) == 2)
    {
        timer++;
        
        if (strcmp("R", &rw))
        {
            unsigned adrress = id_calculator(addr, s);

            hit = find(&page_table, size, adrress, timer);
            printf("hit = %d\n", hit);

            if (!hit)
            {
                printf("djasfhaksdf");
                if (used_adresses < size)// Se tem espaco vazio
                {
                    add(&page_table, used_adresses, id_calculator(addr, s), timer);
                    used_adresses++;
                }
                else // LRU
                {
                    int aux;
                    lru = page_table[0].timer; // menos usado
                    for (int i = 1; i < size; i++)
                    {
                        if (page_table[i].timer < lru)
                        {
                            lru = page_table[i].timer;
                            aux = i;
                        }
                    }
                    add(&page_table, aux, id_calculator(addr, s), timer);
                }
            }
        }
        else
        {
            if (used_adresses < size) // Se tem espaco vazio
            {
                add(&page_table, used_adresses, id_calculator(addr, s), timer);
                used_adresses++;
            }
            else // LRU
            {
                int aux;
                lru = page_table[0].timer; // menos usado
                for (int i = 1; i < size; i++)
                {
                    if (page_table[i].timer < lru)
                    {
                        lru = page_table[i].timer;
                        aux = i;
                    }
                }
                add(&page_table, aux, id_calculator(addr, s), timer);
            }
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
void simulate_2a(struct Recorder *rec, Page page_table[], int size, char *filename, int s)
{
    unsigned addr;
    char rw;

    FILE *file = fopen(filename, "r");

    while (fscanf(file, "%x %c", &addr, &rw) == 2)
    {

        if (strcmp("R", rw))
        {
        }
        else
        {
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
void simulate_fifo(struct Recorder *rec, Page page_table[], int size, char *filename, int s)
{
    unsigned addr;
    char rw;

    FILE *file = fopen(filename, "r");

    while (fscanf(file, "%x %c", &addr, &rw) == 2)
    {

        if (strcmp("R", rw))
        {
        }
        else
        {
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
void simulate_random(struct Recorder *rec, Page page_table[], int size, char *filename, int s)
{
    unsigned addr;
    char rw;

    FILE *file = fopen(filename, "r");

    while (fscanf(file, "%x %c", &addr, &rw) == 2)
    {

        if (strcmp("R", rw))
        {
        }
        else
        {
        }
    };
}

int main(int argc, char* argv[])
{
    struct Recorder rec;

    char *alg = argv[1]; 
    char *filename = argv[2];

    unsigned page_size = atoi(argv[3]);
    unsigned mem_size = atoi(argv[4]);


    int size = mem_size / page_size;
    
    Page page_table[size];

    const unsigned s = size_calculator(page_size);

    set_config(&rec, argv);

    if (strcmp(alg, "lru") == 0)
    {
        simulate_lru(&rec, page_table, size, filename, s);
        
    }
    else if (strcmp(alg, "2a") == 0)
    {
        simulate_2a(&rec, page_table, size, filename, s);
    }
    else if (strcmp(alg, "fifo") == 0)
    {
        simulate_fifo(&rec, page_table, size, filename, s);
    }
    else if (strcmp(alg, "random") == 0)
    {
        simulate_random(&rec, page_table, size, filename, s);
    }
    else
    {
        printf("Erro, algoritmo inválido.");
    }

    print_results(&rec);

    return 0;
}