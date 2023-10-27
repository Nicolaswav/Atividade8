#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// ... Código anterior ...

int lista_verificar_existencia(No* L, char valor_busca) {
    if (L != NULL) {
        if (L->valor == valor_busca) {
            return 1; // Encontrou o valor
        }
        return lista_verificar_existencia(L->proximo_no, valor_busca);
    }
    return 0; // Valor não encontrado
}

int lista_verificar_ocorrencias(No* L, char valor_busca) {
    if (L != NULL) {
        int ocorrencias = 0;
        if (L->valor == valor_busca) {
            ocorrencias++;
        }
        return ocorrencias + lista_verificar_ocorrencias(L->proximo_no, valor_busca);
    }
    return 0; // Valor não encontrado
}

void lista_imprimir_inversa(No* L) {
    if (L != NULL) {
        lista_imprimir_inversa(L->proximo_no);
        printf("%c ", L->valor);
    }
}

void lista_inserir_no_i(No* L, int i, char valor) {
    if (i == 0) {
        No* novo_no = no(valor, L->proximo_no);
        L->proximo_no = novo_no;
    } else if (L != NULL) {
        lista_inserir_no_i(L->proximo_no, i - 1, valor);
    }
}

void lista_remover_no_i(No* L, int i) {
    if (i == 0 && L != NULL && L->proximo_no != NULL) {
        No* temp = L->proximo_no;
        L->proximo_no = L->proximo_no->proximo_no;
        free(temp);
    } else if (L != NULL) {
        lista_remover_no_i(L->proximo_no, i - 1);
    }
}

void lista_remover_no(No* L, char valor_busca) {
    if (L == NULL) {
        return;
    }
    
    if (L->proximo_no != NULL && L->proximo_no->valor == valor_busca) {
        No* temp = L->proximo_no;
        L->proximo_no = L->proximo_no->proximo_no;
        free(temp);
        lista_remover_no(L, valor_busca);
    } else {
        lista_remover_no(L->proximo_no, valor_busca);
    }
}

int main() {
    No* lista = no('A', NULL);
    lista_inserir_no(lista, no('B', NULL));
    lista_inserir_no(lista, no('A', NULL));
    lista_inserir_no(lista, no('C', NULL));

    // Testando as novas funções
    printf("Existe 'B' na lista: %d\n", lista_verificar_existencia(lista, 'B'));
    printf("Quantidade de 'A' na lista: %d\n", lista_verificar_ocorrencias(lista, 'A'));

    printf("Lista original: ");
    lista_imprimir(lista);
    printf("\nLista inversa: ");
    lista_imprimir_inversa(lista);
    printf("\n");

    lista_inserir_no_i(lista, 2, 'X');
    printf("Inserindo 'X' na posição 2: ");
    lista_imprimir(lista);
    printf("\n");

    lista_remover_no_i(lista, 1);
    printf("Removendo nó na posição 1: ");
    lista_imprimir(lista);
    printf("\n");

    lista_remover_no(lista, 'A');
    printf("Removendo todos os nós com valor 'A': ");
    lista_imprimir(lista);
    printf("\n");

    lista_liberar(lista); // Liberar memória alocada
    return 0;
}
