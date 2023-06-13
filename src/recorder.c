#include "recorder.h"
#include <stdio.h>

/**
 * @brief Armazena os dados da Configuração do programa, e inicializa as variáveis como 0
 * @param argv Lista de parâmetros.
*/
void set_config(struct Recorder* recorder, char* argv[]) {
    recorder->acessos = 0;
    recorder->dirty_pages = 0;
    recorder->page_faults = 0;
    recorder->configuracao[0] = argv[1];
    recorder->configuracao[1] = argv[2];
    recorder->configuracao[2] = argv[3];
    recorder->configuracao[3] = argv[4];
}

/**
 * @brief Incrementa a contagem de PageFaults
*/
void increase_page_fault(struct Recorder* recorder) {
    recorder->page_faults++;
}


/**
 * @brief Incrementa a contagem de Dirty Pages
*/
void increase_dirty_pages(struct Recorder* recorder) {
    recorder->dirty_pages++;
}

/**
 * @brief Incrementa o número de acessos à memória
*/
void increase_acessos(struct Recorder* recorder) {
    recorder->acessos++;
}

/**
 * @brief Printa os resultados do recorder na saida do programa, como registro das atividades do simulador
*/
void print_results(struct Recorder* recorder) {
    printf("Configurações do programa: \nAlgoritmo: %s\nArquivo processado: %s\nTamanho das Páginas: %s \nTamanho da memória usada: %s\n", recorder->configuracao[0], recorder->configuracao[1], recorder->configuracao[2], recorder->configuracao[3]);
    
    printf("Page faults: %u\n", recorder->page_faults);
    printf("Dirty pages: %u\n", recorder->dirty_pages);
    printf("Acessos: %u\n", recorder->acessos);
}
