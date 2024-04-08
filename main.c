#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/select.h>
#include <omp.h> //OpenMP
#include "esteira1.h"
#include "esteira2.h"
#include "esteira3.h"

#define NUM_THREADS 3

// Estrutura para armazenar os dados totais de todas as esteiras
typedef struct {
    int total_count;
    float total_weight;
} TotalData;

int kbhit(void) {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == 1;
}

void pausa(Esteira1Data *esteira1_data, Esteira2Data *esteira2_data, Esteira3Data *esteira3_data, int *pause_flag, int *pipe_fd) {
    printf("Pressione 'B' para realizar alguma ação\n");
    while (1) {
        printf("Esteira 1: Contagem = %d, Peso = %.2f Kg\n", getEsteira1Count(esteira1_data), getEsteira1Weight(esteira1_data));
        printf("Esteira 2: Contagem = %d, Peso = %.2f Kg\n", getEsteira2Count(esteira2_data), getEsteira2Weight(esteira2_data));
        printf("Esteira 3: Contagem = %d, Peso = %.2f Kg\n", getEsteira3Count(esteira3_data), getEsteira3Weight(esteira3_data));
        
        sleep(2); // Atualiza a cada 2 segundos

        if (kbhit()) {
            char key = getchar(); // Obtém a tecla pressionada
            if (key == 'b' || key == 'B') { // Verifica se a tecla é 'b' ou 'B'
                printf("\nAperte S para pausar e/ou T para realizar o total das esteiras\n");
                do {
                    key = getchar(); // Aguarda a próxima tecla pressionada
                } while (key != '\n'); // Continua aguardando até que Enter seja pressionado
                
                *pause_flag = 1; // Define a sinalização de pausa
                write(*pipe_fd, "pausa", sizeof("pausa")); // Escreve no pipe para notificar a função principal sobre a pausa
            } else if (key == 't' || key == 'T') {
                // Calcular e exibir o total de contagem e peso de todas as esteiras
                int total_count = getEsteira1Count(esteira1_data) + getEsteira2Count(esteira2_data) + getEsteira3Count(esteira3_data);
                float total_weight = getEsteira1Weight(esteira1_data) + getEsteira2Weight(esteira2_data) + getEsteira3Weight(esteira3_data);
                printf("\nTotal de contagem de todas as esteiras: %d\n", total_count);
                printf("Total de peso de todas as esteiras: %.2f Kg\n", total_weight);
            } else {
                while ((getchar()) != '\n');
                break; // Sai do loop de pausa
            }
        }
    }
}

int main() {
    pthread_t threads[NUM_THREADS];
    Esteira1Data esteira1_data;
    Esteira2Data esteira2_data;
    Esteira3Data esteira3_data;
    int i;
    int pause_flag = 0; // Sinalizador para pausa
    int pipe_fd[2]; // Pipe para comunicação entre threads e a função principal

    // Inicialização das esteiras
    initEsteira1(&esteira1_data);
    initEsteira2(&esteira2_data);
    initEsteira3(&esteira3_data);

    // Criação das threads para cada esteira
    pthread_create(&threads[0], NULL, esteira1, (void *)&esteira1_data);
    pthread_create(&threads[1], NULL, esteira2, (void *)&esteira2_data);
    pthread_create(&threads[2], NULL, esteira3, (void *)&esteira3_data);

    // Chama a função pausa, que controla a contagem e a pausa
    pausa(&esteira1_data, &esteira2_data, &esteira3_data, &pause_flag, pipe_fd);

    // Parar as threads
    if (pause_flag) {
        printf("Parando as esteiras...\n");
        // Realiza alguma ação para parar as esteiras, se necessário
        // Aqui você pode enviar algum sinal para as threads para que elas saiam de seus loops
    }

    // Aguarda a finalização das threads (não será alcançado neste exemplo)
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Soma o peso total das esteiras usando OpenMP
    float total_weight = 0.0;
    #pragma omp parallel for reduction(+:total_weight)
    for (i = 0; i < NUM_THREADS; i++) {
        if (i == 0)
            total_weight += getEsteira1Weight(&esteira1_data);
        else if (i == 1)
            total_weight += getEsteira2Weight(&esteira2_data);
        else if (i == 2)
            total_weight += getEsteira3Weight(&esteira3_data);
    }

    printf("Peso total de todas as esteiras: %.2f Kg\n", total_weight);

    // Fecha o pipe
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
