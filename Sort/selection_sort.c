#include <stdio.h>
#include <stdlib.h>

// função para trocar dois elementos de posição
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// selection sort com contagem de comparações
int selectionSort(int array[], int n) {
    int i, j, min_idx;
    int comparacoes = 0;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            comparacoes++; // conta a comparação
            if (array[j] < array[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            trocar(&array[min_idx], &array[i]);
        }
    }
    return comparacoes;
}

// função auxiliar para imprimir o array
void imprimirArray(int array[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int comparacoes, i, r;
    int n = 100;
    int *arr = (int*) malloc(n * sizeof(int));

    /* CASO MÉDIO */
    for (i = 0; i < n; i++) {
        r = rand() % 1000;
        arr[i] = r;
    }
    comparacoes = selectionSort(arr, n);
    printf("Caso medio: %d\n", comparacoes);

    /* MELHOR CASO (já ordenado) */
    for (i = 0; i < n; i++) {
        arr[i] = i;
    }
    comparacoes = selectionSort(arr, n);
    printf("Melhor caso: %d\n", comparacoes);

    /* PIOR CASO (ordenado decrescente) */
    for (i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    comparacoes = selectionSort(arr, n);
    printf("Pior caso: %d\n", comparacoes);

    free(arr);
    return 0;
}
// finitude: O algoritmo termina após n-1 iterações, onde n é o número de elementos no array, garantindo que todos os elementos sejam ordenados.
// corretude: A cada iteração, o menor elemento do subarray não ordenado é selecionado e colocado na posição correta, garantindo que o array esteja ordenado ao final do processo.
// complexidade: A complexidade de tempo do selection sort é O(n^2) em todos os casos (melhor, médio e pior), devido aos dois loops aninhados que percorrem o array.
//custo memorial: O algoritmo utiliza O(1) espaço adicional, pois a ordenação é feita in-place, sem necessidade de estruturas de dados auxiliares significativas.