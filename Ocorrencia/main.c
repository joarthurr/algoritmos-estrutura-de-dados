
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "lista_estatica.h"
#include "lista_dinamica.h"
#include "ordenacao_estatica.h"
#include "ordenacao_dinamica.h"

// GERAÇÃO DE GRÁFICOS
void salvar_dados_csv(const char *nome_arquivo, int n, int estrutura, int algoritmo, int tipo, double tempo_ms, long long int comparacoes) {
    FILE *file = fopen(nome_arquivo, "a");
    if (file == NULL) return;
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fprintf(file, "N;Estrutura;Algoritmo;TipoDados;Tempo_ms;Comparacoes\n");
    }
    fprintf(file, "%d;%d;%d;%d;%.4f;%lld\n", n, estrutura, algoritmo, tipo, tempo_ms, comparacoes);
    fclose(file);
}

// GERAÇÃO DE DADOS
Ocorrencia gerarOcorrencia(int id) {
    Ocorrencia o;
    o.id = id;
    o.prioridade = rand() % 5 + 1;
    o.distancia = (float)(rand() % 2000) / 100;
    o.tempoEspera = rand() % 120;
    return o;
}

Ocorrencia gerarOcorrenciaInversa(int id, int n) {
    Ocorrencia o;
    o.id = id;
    // Pior caso: Gera prioridades menores primeiro (ex: 1, 1, 2...) 
    o.prioridade = 1 + ((id - 1) * 5 / n); 
    if(o.prioridade > 5) o.prioridade = 5;
    o.distancia = id * 0.1f;
    o.tempoEspera = n - id;
    return o;
}

Ocorrencia gerarOcorrenciaOrdenada(int id, int n) {
    Ocorrencia o;
    o.id = id;
    // Melhor caso: Gera prioridades maiores primeiro (5, 5, 4...)
    o.prioridade = 5 - ((id - 1) * 5 / n); 
    if(o.prioridade < 1) o.prioridade = 1;
    o.distancia = (n - id) * 0.1f;
    o.tempoEspera = id;
    return o;
}

int main() {
    srand(time(NULL));
    int n, tipo, estrutura, algoritmo;
    const int REPETICOES = 100; 

<<<<<<< HEAD
    printf("\nANALISE DE DESEMPENHO: ORDENACAO DE OCORRENCIAS\n");
=======
    printf("Ordenacao de prioridade das Ocorencias:\n\n");
>>>>>>> 0a4fa11a5e81ead4d73cf2ad9951c288ce63cb9c
    printf("Estrutura (1-Estatica, 2-Dinamica): ");
    scanf("%d", &estrutura);
    printf("Algoritmo (1-Bubble, 2-Insertion, 3-Selection, 5-Merge): ");
    scanf("%d", &algoritmo);
    printf("Quantidade de dados (N): ");
    scanf("%d", &n);
    printf("Tipo (0-Aleatoria, 1-Inversa, 2-Ordenada): ");
    scanf("%d", &tipo);

    //TESTE 
    if (n <= 20) {
        long int comp_teste = 0;
<<<<<<< HEAD
        printf("\nVISUALIZACAO TESTE:");
=======
        printf("\n--- VISUALIZACAO TESTE ---");
>>>>>>> 0a4fa11a5e81ead4d73cf2ad9951c288ce63cb9c
        if (estrutura == 1) {
            ListaEstatica le;
            inicializar_estatica(&le);
            for(int i=0; i<n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_estatica(&le, o);
            }
<<<<<<< HEAD
            printf("\nLISTA ANTES:\n"); imprimir_estatica(&le);
=======
            printf("\nLista antes:\n"); imprimir_estatica(&le);
>>>>>>> 0a4fa11a5e81ead4d73cf2ad9951c288ce63cb9c
            if (algoritmo == 1) bubbleSortEstatica(&le, &comp_teste);
            else if (algoritmo == 2) insertionSortEstatica(&le, &comp_teste);
            else if (algoritmo == 3) selectionSortEstatica(&le, &comp_teste);
            else if (algoritmo == 5) mergeSortEstatica(&le, &comp_teste);
<<<<<<< HEAD
            printf("\nLISTA DEPOIS:\n"); imprimir_estatica(&le);
=======
            printf("\nLista depois:\n"); imprimir_estatica(&le);
>>>>>>> 0a4fa11a5e81ead4d73cf2ad9951c288ce63cb9c
        } else {
            NoDinamico *ld = NULL;
            for(int i=0; i<n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_dinamica(&ld, o);
            }
<<<<<<< HEAD
            printf("\nLISTA ANTES:"); imprimir_dinamica(ld);
=======
            printf("\nLista antes:"); imprimir_dinamica(ld);
>>>>>>> 0a4fa11a5e81ead4d73cf2ad9951c288ce63cb9c
            if (algoritmo == 1) bubbleSortDinamica(ld, &comp_teste);
            else if (algoritmo == 2) insertionSortDinamica(&ld, &comp_teste);
            else if (algoritmo == 3) selectionSortDinamica(ld, &comp_teste);
            else if (algoritmo == 5) mergeSortDinamica(&ld, &comp_teste);
<<<<<<< HEAD
            printf("\nLISTA DEPOIS:"); imprimir_dinamica(ld);
            liberar_dinamica(ld);
        }
        printf("\nComparacoes no teste: %ld", comp_teste);
        printf("\nFIM DO MODO TESTE\n\n");
=======
            printf("\nLista depois:"); imprimir_dinamica(ld);
            liberar_dinamica(ld);
        }
        printf("\nComparacoes no teste: %ld", comp_teste);
        printf("\n--- FIM DO MODO TESTE ---\n\n");
>>>>>>> 0a4fa11a5e81ead4d73cf2ad9951c288ce63cb9c
    }

    //TESTE DE PERFORMANCE
    double tempo_total = 0;
<<<<<<< HEAD
    long long int total_comparacoes = 0; 
    
    printf("Executando %d repeticoes para N=%d...\n", REPETICOES, n);
=======
    long long int total_comparacoes = 0; // Usando long long para evitar overflow em N grande
    printf("Calculando media para %d repeticoes...\n", REPETICOES);
>>>>>>> 0a4fa11a5e81ead4d73cf2ad9951c288ce63cb9c

    for (int r = 0; r < REPETICOES; r++) {
        long int comp_rodada = 0;
        
        if (estrutura == 1) {
            ListaEstatica le;
            inicializar_estatica(&le);
            for(int i = 0; i < n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_estatica(&le, o);
            }

            clock_t start = clock();
            if (algoritmo == 1) bubbleSortEstatica(&le, &comp_rodada);
            else if (algoritmo == 2) insertionSortEstatica(&le, &comp_rodada);
            else if (algoritmo == 3) selectionSortEstatica(&le, &comp_rodada);
            else if (algoritmo == 5) mergeSortEstatica(&le, &comp_rodada);
            clock_t end = clock();

            tempo_total += ((double)(end - start)) / CLOCKS_PER_SEC;
            total_comparacoes += comp_rodada;

        } else {
            NoDinamico *ld = NULL;
            for(int i = 0; i < n; i++) {
                Ocorrencia o = (tipo == 0) ? gerarOcorrencia(i+1) : (tipo == 1 ? gerarOcorrenciaInversa(i+1, n) : gerarOcorrenciaOrdenada(i+1, n));
                inserir_dinamica(&ld, o);
            }

            clock_t start = clock();
            if (algoritmo == 1) bubbleSortDinamica(ld, &comp_rodada);
            else if (algoritmo == 2) insertionSortDinamica(&ld, &comp_rodada);
            else if (algoritmo == 3) selectionSortDinamica(ld, &comp_rodada);
            else if (algoritmo == 5) mergeSortDinamica(&ld, &comp_rodada);
            clock_t end = clock();

            tempo_total += ((double)(end - start)) / CLOCKS_PER_SEC;
            total_comparacoes += comp_rodada;
            liberar_dinamica(ld);
        }
    }

    double media_ms = (tempo_total / REPETICOES) * 1000.0;
    long long int media_comp = total_comparacoes / REPETICOES;

<<<<<<< HEAD
    // Salva os resultados 
    salvar_dados_csv("resultados_ordenacao.csv", n, estrutura, algoritmo, tipo, media_ms, media_comp);

    printf("\n========================================");
    printf("\nRESULTADO FINAL PARA N = %d", n);
    printf("\nTempo Medio: %.4f ms", media_ms);
    printf("\nComparacoes Medias: %lld", media_comp);
    printf("\nDados exportados para 'resultados_ordenacao.csv'");
=======
    printf("\n========================================");
    printf("\nRESULTADOS (MEDIAS) PARA N = %d", n);
    printf("\nTempo Medio: %f ms", media_ms);
    printf("\nComparacoes Medias: %lld", media_comp); 
>>>>>>> 0a4fa11a5e81ead4d73cf2ad9951c288ce63cb9c
    printf("\n========================================\n");

    return 0;
}