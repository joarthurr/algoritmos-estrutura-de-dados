#include <stdio.h>
#include "lista_estatica.h"
#include "lista_dinamica.h"
#include "ocorrencia.h"

void testarListaEstatica() {
    ListaEstatica lista;
    inicializar_estatica(&lista);

    Ocorrencia o1 = {1, 5, 3.2, 10};
    Ocorrencia o2 = {2, 2, 1.5, 5};
    Ocorrencia o3 = {3, 4, 2.8, 7};

    inserir_estatica(&lista, o1);
    inserir_estatica(&lista, o2);
    inserir_estatica(&lista, o3);

    imprimir_estatica(&lista);

    printf("\nRemovendo a Ocorrencia de ID 2\n");
    remover_estatica(&lista, 2);

    imprimir_estatica(&lista);
}

void testarListaDinamica() {
    NoDinamico *lista = NULL;

    Ocorrencia o1 = {1, 5, 3.2, 10};
    Ocorrencia o2 = {2, 2, 1.5, 5};
    Ocorrencia o3 = {3, 4, 2.8, 7};

    inserir_dinamica(&lista, o1);
    inserir_dinamica(&lista, o2);
    inserir_dinamica(&lista, o3);

    imprimir_dinamica(lista);

    printf("\nRemovendo a Ocorrencia de ID 2\n");
    remover_dinamica(&lista, 2);

    imprimir_dinamica(lista);
    liberar_dinamica(lista);
}

int main() {

    printf("Testando Lista Estatica:\n");
    testarListaEstatica();

    printf("\nTestando Lista Dinamica:\n");
    testarListaDinamica();

    return 0;
}