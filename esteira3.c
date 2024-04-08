// esteira3.c
#include "esteira3.h"
#include <unistd.h>

void *esteira3(void *arg) {
    Esteira3Data *data = (Esteira3Data *)arg;
    float weightPerItem = 0.5; // Peso de cada item na esteira 3

    while (1) {
        usleep(100000); // Aguarda 0.1 segundo
        pthread_mutex_lock(&data->mutex);
        data->count++;
        data->weight += weightPerItem;
        pthread_mutex_unlock(&data->mutex);
    }

    return NULL;
}

void initEsteira3(Esteira3Data *data) {
    data->count = 0;
    data->weight = 0.0;
    pthread_mutex_init(&data->mutex, NULL);
}

int getEsteira3Count(Esteira3Data *data) {
    return data->count;
}

float getEsteira3Weight(Esteira3Data *data) {
    return data->weight;
}
