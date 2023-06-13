#include "recorder.h"
#include <stdio.h>

void set_config(struct Recorder* recorder, char* argv[]) {
    recorder->configuracao[0] = argv[1];
    recorder->configuracao[1] = argv[2];
    recorder->configuracao[2] = argv[3];
    recorder->configuracao[3] = argv[4];
}

void increase_page_fault(struct Recorder* recorder) {
    recorder->page_faults++;
}

void increase_dirty_pages(struct Recorder* recorder) {
    recorder->dirty_pages++;
}

void increase_acessos(struct Recorder* recorder) {
    recorder->acessos++;
}

void print_results(struct Recorder* recorder) {
    // Implementação da função print_results
    printf("Page faults: %u\n", recorder->page_faults);
    printf("Dirty pages: %u\n", recorder->dirty_pages);
    printf("Acessos: %u\n", recorder->acessos);
}
