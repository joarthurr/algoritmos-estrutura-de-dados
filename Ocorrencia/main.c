#include <stdio.h>
#include "lista.h"
#include "ocorrencia.h"

int main() {
    No *lista = NULL;

    Ocorrencia o1 = {1, 5, 3.2, 10};
    Ocorrencia o2 = {2, 2, 1.5, 5};
    Ocorrencia o3 = {3, 4, 2.8, 7};

    inserir(&lista, o1);
    inserir(&lista, o2);
    inserir(&lista, o3);

    imprimir(lista);

    remover(&lista, 2);

    printf("\nDepois da remocao:\n");
    imprimir(lista);

    liberar(lista);
    return 0;
}
