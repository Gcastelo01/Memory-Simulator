#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Page
{
    int id;
    int dirty;
    int second_chance;
    int timer;
    int ref_bit;
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
    printf("Executando o simulador... \nTécnica de reposição: %s\nArquivo de entrada: %s\nTamanho das Páginas: %sKB\nTamanho da memória usada: %sKB\n", rec.configuracao[0], rec.configuracao[1], rec.configuracao[2], rec.configuracao[3]);
    printf("Page faults: %d\n", rec.page_faults);
    printf("Páginas sujas escritas: %d\n", rec.dirty_writes);
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
    page_table[idx].dirty = 1;
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
    if (file == NULL)
    {
        printf("ERRO: Não abriu o arquivo");
    }

    int timer = 0;
    int lru = 0;

    while (fscanf(file, "%x %c", &addr, &rw) == 2)
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

void simulate_2a(struct Page *page_table, int size, char *filename, int s)
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

            // Caso a página não esteja na memória, "Carregamos" ela do disco
            if (!hit)
            {
                rec.page_faults++;

                if (used_adresses < size)
                {
                    add(page_table, used_adresses, id_calculator(addr, s), timer);
                    page_table[used_adresses].ref_bit = 1;
                    used_adresses++;
                }
                else // Segunda Chance
                {

                    for (int i = 0; i < size; i++)
                    {
                        if (page_table[i].ref_bit)
                        {
                            page_table[i].ref_bit = 0;
                        }
                        else
                        {
                            add(page_table, i, id_calculator(addr, s), timer);
                            page_table[i].ref_bit = 1;
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            if (used_adresses < size)
            {
                add(page_table, used_adresses, id_calculator(addr, s), timer);
                page_table[used_adresses].ref_bit = 1;

                used_adresses++;
            }
            else
            {
                rec.dirty_writes++;

                for (int i = 0; i < size; i++)
                {
                    if (page_table[i].ref_bit)
                    {
                        page_table[i].ref_bit = 0;
                    }
                    else
                    {
                        add(page_table, i, id_calculator(addr, s), timer);
                        page_table[i].ref_bit = 1;
                        break;
                    }
                }
            }
        }
    };

    fclose(file);
}

void simulate_random(struct Page *page_table, int size, char *filename, int s)
{
    srand(time(NULL));
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
                else // Random
                {
                    int r = rand() % size;
                    add(page_table, r, id_calculator(addr, s), timer);
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
            else
            {
                rec.dirty_writes++;
                int r = rand() % size;
                add(page_table, r, id_calculator(addr, s), timer);
            }
        }
    };

    fclose(file);
}

int main(int argc, char *argv[])
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
    else if (strcmp(alg, "2a") == 0)
    {
        simulate_2a(page_table, size, filename, s);
    }
    else if (strcmp(alg, "fifo") == 0)
    {
        simulate_fifo(page_table, size, filename, s);
    }
    else if (strcmp(alg, "random") == 0)
    {
        simulate_random(page_table, size, filename, s);
    }
    else
    {
        printf("Erro, algoritmo inválido.\n");
        return 1;
    }

    free(page_table);
    
    print_results();

    return 0;
}