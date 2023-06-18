#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Page
{
    int id;
    int dirty;
    int second_chance;
    int timer;
};

struct Recorder
{
    char *configuracao[4];
    unsigned page_faults;
    unsigned dirty_writes;
};

struct Recorder rec;

void print_results()
{
    printf("Executando o simulador... \n\tTécnica de reposição: %s\n\tArquivo de entrada: %s\n\tTamanho das Páginas: %sKB\n\tTamanho da memória usada: %sKB\n", rec.configuracao[0], rec.configuracao[1], rec.configuracao[2], rec.configuracao[3]);
    printf("\tPage faults: %u\n", rec.page_faults);
    printf("\tPáginas sujas escritas: %u", rec.dirty_writes);
}

int size_calculator(int page_size)
{
    int tmp = page_size, s = 0;
    while (tmp > 1)
    {
        tmp = tmp >> 1;
        s++;
    }
    return s + 10;
};

unsigned id_calculator(unsigned addr, int s)
{
    return addr >> s;
}

void add(struct Page *page_table, int idx, unsigned addr, int timer)
{
    page_table[idx].id = addr;
    page_table[idx].timer = timer;
}

int find(struct Page *page_table, int size, unsigned id, int timer)
{
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        if (id == page_table[i].id)
        {
            res = 1;
            page_table[i].timer = timer;
        }
    }
    return res;
}

void simulate_lru(struct Page *page_table, int size, char *filename, int s)
{
    unsigned addr;
    char rw;
    int hit;

    int used_adresses = 0;

    FILE *file = fopen(filename, "r");

    int timer = 0;
    int lru = 0;

    unsigned addr;
    char rw;

    while (fscanf(file, "%x %c ", &addr, &rw) == 2)
    {
        timer++;

        if (rw == 'R')
        {
            hit = find(page_table, size, id_calculator(addr, s), timer);
            if (!hit)
            {
                rec.page_faults++;

                if (used_adresses < size) // Se tem espaço vazio
                {
                    add(page_table, used_adresses, id_calculator(addr, s), timer);
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
                    add(page_table, aux, id_calculator(addr, s), timer);
                }
            }
        }
        else
        {
            if (used_adresses < size) // Se tem espaço vazio
            {
                add(page_table, used_adresses, id_calculator(addr, s), timer);
                used_adresses++;
            }
            else // LRU
            {
                rec.dirty_writes++; // Escrita de página suja

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
                add(page_table, aux, id_calculator(addr, s), timer);
            }
        }
    };

    fclose(file);
}

void simulate_fifo(struct Page *page_table, int size, char *filename, int s)
{
    unsigned addr;
    char rw;
    int hit;

    int used_adresses = 0;

    FILE *file = fopen(filename, "r");

    int timer = 0;

    while (fscanf(file, "%x %c", &addr, &rw) == 2)
    {
        if (rw == 'R')
        {
            hit = find(page_table, size, id_calculator(addr, s), timer);
            if (!hit)
            {
                rec.page_faults++;

                if (used_adresses < size) // Se tem espaço vazio
                {
                    add(page_table, used_adresses, id_calculator(addr, s), timer);
                    used_adresses++;
                }
                else // FIFO
                {
                }
            }
        }
        else
        {
            if (used_adresses < size) // Se tem espaço vazio
            {
                add(page_table, used_adresses, id_calculator(addr, s), timer);
                used_adresses++;
            }
            else // FIFO
            {
            }
        }
    };

    fclose(file);
}

int main(int argc, char* argv[])
{

    // Parâmetros passados
    char *alg = argv[1];
    char *filename = argv[2];
    int page_size = atoi(argv[3]);
    int mem_size = atoi(argv[4]);

    // Definição da tabela e tamanhos
    int size = mem_size / page_size;
    struct Page *page_table = (struct Page *)malloc(size * sizeof(struct Page));
    if (page_table == NULL)
    {
        printf("Falha na alocação de memória!\n");
        return 1;
    }

    int s = size_calculator(page_size);

    // Configurando o recorder
    rec.dirty_writes = 0;
    rec.page_faults = 0;
    rec.configuracao[0] = argv[1];
    rec.configuracao[1] = argv[2];
    rec.configuracao[2] = argv[3];
    rec.configuracao[3] = argv[4];

    if (strcmp(alg, "lru") == 0)
    {
        simulate_lru(page_table, size, filename, s);
    }
    else
    {
        printf("Erro, algoritmo inválido.\n");
        return 1;
    }
    print_results();

    return 0;
}