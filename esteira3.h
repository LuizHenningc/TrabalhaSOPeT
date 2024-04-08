// esteira3.h
#ifndef ESTEIRA3_H
#define ESTEIRA3_H

#include <pthread.h>

typedef struct {
    int count;
    float weight;
    pthread_mutex_t mutex;
} Esteira3Data;

void *esteira3(void *arg);
void initEsteira3(Esteira3Data *data);
int getEsteira3Count(Esteira3Data *data);
float getEsteira3Weight(Esteira3Data *data);

#endif /* ESTEIRA3_H */
