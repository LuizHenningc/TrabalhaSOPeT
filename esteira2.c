// esteira2.c
#include "esteira2.h"
#include <unistd.h>

void *esteira2(void *arg) {
    Esteira2Data *data = (Esteira2Data *)arg;
    float weightPerItem = 2.0; // Peso de cada item na esteira 2

    while (1) {
        usleep(500000); // Aguarda 0.5 segundo
        pthread_mutex_lock(&data->mutex);
        data->count++;
        data->weight += weightPerItem;
        pthread_mutex_unlock(&data->mutex);
    }

    return NULL;
}

void initEsteira2(Esteira2Data *data) {
    data->count = 0;
    data->weight = 0.0;
    pthread_mutex_init(&data->mutex, NULL);
}

int getEsteira2Count(Esteira2Data *data) {
    return data->count;
}

float getEsteira2Weight(Esteira2Data *data) {
    return data->weight;
}
