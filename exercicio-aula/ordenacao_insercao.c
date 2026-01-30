// ordenação por inserção

#include <stdio.h>
// função para imprimir o vetor
void imprimirVetor(int v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// função de ordenação por inserção
void insertionSort(int v[], int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = v[i];      // elemento a ser inserido
        j = i - 1;
        // desloca os elementos maiores que a chave para frente
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        // insere a chave na posição correta
        v[j + 1] = chave;
    }
}

int main() {
    int vetor[] = {5, 3, 1, 4, 2};
    int n = sizeof(vetor) / sizeof(vetor[0]);

    printf("Vetor antes da ordenação: ");
    imprimirVetor(vetor, n);
    insertionSort(vetor, n);
    printf("Vetor depois da ordenação: ");
    imprimirVetor(vetor, n);
    return 0;
}

// finitude:  diminui a cada iteração e o vaor inicial é i = j -1 >= 1 . Logo, o laço termina devido ao teste  condicional 
// corretude: no final, o vetor estará em ordem crescente. Cada elemento é inserido na posição correta dentro da parte já ordenada, processo que repete até que todos os elementos estejam posicionados.
// complexidade: no pior caso O(n^2), vetor em ordem descrescente. No melhor caso O(n), vetor em ordem crescente, 0 movimentações