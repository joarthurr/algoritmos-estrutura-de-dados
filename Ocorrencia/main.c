#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista_estatica.h"
#include "lista_dinamica.h"
#include "ordenacao_estatica.h"
#include "ordenacao_dinamica.h"

/* ===== FUNÇÕES DE GERAÇÃO DE DADOS ===== */

// Aleatória
Ocorrencia gerarOcorrencia(int id) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = rand() % 5 + 1;
    o.distancia = (float)(rand() % 2000) / 100; // 0.0 a 20.0
    o.tempoEspera = rand() % 120;
    return o;
}

// Inverson (pior caso) 
Ocorrencia gerarOcorrenciaInversa(int id, int n) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = 5 - ((id - 1) * 5 / n); 
    if(o.prioridade < 1) o.prioridade = 1;
    o.distancia = id * 0.1f;
    o.tempoEspera = n - id;
    return o;
}

// Ordenada
Ocorrencia gerarOcorrenciaOrdenada(int id, int n) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = 1 + ((id - 1) * 5 / n);
    if(o.prioridade > 5) o.prioridade = 5;
    o.distancia = (n - id) * 0.1f;
    o.tempoEspera = id;
    return o;
}

/* ===== MAIN ===== */

int main() {
    srand(time(NULL));
    int n, tipo, estrutura, algoritmo;
    const int REPETICOES = 100; // Exigência para suavizar as curvas [cite: 45]

    printf("--- Simulador de Desempenho (Analise Experimental) ---\n");
    
    // 1. Escolha da Estrutura [cite: 23]
    printf("Escolha a estrutura:\n 1-Lista Estatica (Vetor)\n 2-Lista Dinamica (Encadeada)\nOpcao: ");
    scanf("%d", &estrutura);

    // 2. Escolha do Algoritmo 
    printf("\nEscolha o Algoritmo de Ordenacao:\n");
    printf(" 1-Bubble Sort\n 2-Insertion Sort\n 3-Selection Sort\n 4-Quick Sort\n 5-Merge Sort\nEscolha: ");
    scanf("%d", &algoritmo);

    // 3. Volume de Dados [cite: 30]
    printf("\nQuantidade de dados (N - Ex: 100, 1000, 10000): ");
    scanf("%d", &n);

    // 4. Cenário de Entrada [cite: 36]
    printf("\nTipo de geracao:\n 0-Aleatoria\n 1-Inversa (Pior Caso)\n 2-Ordenada (Melhor Caso)\nOpcao: ");
    scanf("%d", &tipo);

    double tempo_total = 0;
    printf("\nProcessando %d repeticoes para coletar a media...\n", REPETICOES);

    for (int r = 0; r < REPETICOES; r++) {
        if (estrutura == 1) {
            ListaEstatica le;
            inicializar_estatica(&le);
            for(int i = 0; i < n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_estatica(&le, o);
            }

            clock_t start = clock();
            // Seleção do Algoritmo Estático
            switch(algoritmo) {
                case 1: bubbleSortEstatica(&le); break;
                // case 2: insertionSortEstatica(&le); break; // Implementar futuramente
                case 3: selectionSortEstatica(&le); break;
                default: printf("Algoritmo ainda nao implementado para Estatica.\n"); return 0;
            }
            clock_t end = clock();
            tempo_total += ((double)(end - start)) / CLOCKS_PER_SEC;

        } else {
            NoDinamico *ld = NULL;
            for(int i = 0; i < n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_dinamica(&ld, o);
            }

            clock_t start = clock();
            // Seleção do Algoritmo Dinâmico
            switch(algoritmo) {
                case 1: bubbleSortDinamica(ld); break;
                // case 2: insertionSortDinamica(ld); break; // Implementar futuramente
                case 3: selectionSortDinamica(ld); break;
                default: printf("Algoritmo ainda nao implementado para Dinamica.\n"); return 0;
            }
            clock_t end = clock();
            tempo_total += ((double)(end - start)) / CLOCKS_PER_SEC;
            liberar_dinamica(ld);
        }
    }

    double media_ms = (tempo_total / REPETICOES) * 1000.0;
    printf("\n========================================");
    printf("\nRESULTADO DA MEDIA (Metrica: Tempo de Execucao)");
    printf("\nTempo Medio: %f ms", media_ms);
    printf("\n========================================\n");

    return 0;
}
