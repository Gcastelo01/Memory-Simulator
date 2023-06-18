#ifndef RECORDER_H
#define RECORDER_H

struct Recorder{
    char* configuracao[3];
    unsigned page_faults;
    unsigned dirty_pages;
    unsigned acessos;
};

void set_config(struct Recorder* recorder, char* argv[]);
void increase_page_fault(struct Recorder* recorder);
void increase_dirty_pages(struct Recorder* recorder);
void increase_acessos(struct Recorder* recorder);
void print_results(struct Recorder* recorder);

#endif
