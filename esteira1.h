// esteira1.h
#ifndef ESTEIRA1_H
#define ESTEIRA1_H

#include <pthread.h>

typedef struct {
    int count;
    float weight;
    pthread_mutex_t mutex;
} Esteira1Data;

void *esteira1(void *arg);
void initEsteira1(Esteira1Data *data);
int getEsteira1Count(Esteira1Data *data);
float getEsteira1Weight(Esteira1Data *data);

#endif /* ESTEIRA1_H */
