// esteira1.c
#include "esteira1.h"
#include <unistd.h>

void *esteira1(void *arg) {
    Esteira1Data *data = (Esteira1Data *)arg;
    float weightPerItem = 5.0; // Peso de cada item na esteira 1

    while (1) {
        usleep(1000000); // Aguarda 1 segundo
        pthread_mutex_lock(&data->mutex);
        data->count++;
        data->weight += weightPerItem;
        pthread_mutex_unlock(&data->mutex);
    }

    return NULL;
}

void initEsteira1(Esteira1Data *data) {
    data->count = 0;
    data->weight = 0.0;
    pthread_mutex_init(&data->mutex, NULL);
}

int getEsteira1Count(Esteira1Data *data) {
    return data->count;
}

float getEsteira1Weight(Esteira1Data *data) {
    return data->weight;
}
