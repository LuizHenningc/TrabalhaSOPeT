// esteira2.h
#ifndef ESTEIRA2_H
#define ESTEIRA2_H

#include <pthread.h>

typedef struct {
    int count;
    float weight;
    pthread_mutex_t mutex;
} Esteira2Data;

void *esteira2(void *arg);
void initEsteira2(Esteira2Data *data);
int getEsteira2Count(Esteira2Data *data);
float getEsteira2Weight(Esteira2Data *data);

#endif /* ESTEIRA2_H */
