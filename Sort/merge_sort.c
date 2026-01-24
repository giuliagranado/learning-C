// função merge sort
/* divide o array em subarrays até que cada subarray tenha um único elemento, depois mescla os subarrays ordenados */
#include <stdio.h>
#include <stdlib.h>

// função auxiliar para mesclar dois subarrays
int merge(int array[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = 0;
    int comparacoes = 0;
    int size = right - left + 1;
    int *temp = (int*) malloc(size * sizeof(int));

    while (i <= mid && j <= right) {
        comparacoes++;
        if (array[i] <= array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = array[i++];
    }
    while (j <= right) {
        temp[k++] = array[j++];
    }
    for (i = 0; i < size; i++) {
        array[left + i] = temp[i];
    }
    free(temp);
    return comparacoes;
}

// função recursiva do merge sort
int merge_sort(int array[], int left, int right) {
    int comparacoes = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        comparacoes += merge_sort(array, left, mid);
        comparacoes += merge_sort(array, mid + 1, right);
        comparacoes += merge(array, left, mid, right);
    }
    return comparacoes;
}

// função para imprimir o array
void printArray(int array[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// função principal
int main() {
    int comparacoes, i, r;
    int n = 100;
    int *arr = (int*) malloc(n * sizeof(int));

    /* CASO MÉDIO */
    for (i = 0; i < n; i++) {
        r = rand() % 1000;
        arr[i] = r;
    }
    comparacoes = merge_sort(arr, 0, n - 1);
    printf("Caso medio: %d\n", comparacoes);

    /* MELHOR CASO (já ordenado) */
    for (i = 0; i < n; i++) {
        arr[i] = i;
    }
    comparacoes = merge_sort(arr, 0, n - 1);
    printf("Melhor caso: %d\n", comparacoes);

    /* PIOR CASO (ordenado decrescente) */
    for (i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    comparacoes = merge_sort(arr, 0, n - 1);
    printf("Pior caso: %d\n", comparacoes);

    free(arr);
    return 0;
}

// finitude: A cada chamada recursiva, o array é dividido em duas metades, reduzindo o tamanho do problema até que cada subarray tenha um único elemento.
// corretude: A função merge combina dois subarrays ordenados em um único array ordenado, garantindo que o array final esteja em ordem crescente.
// complexidade: A complexidade de tempo do merge sort é O(n log n) em todos os casos (melhor, médio e pior), devido à divisão do array em metades (log n) e à mesclagem dos elementos (n).
// custo memorial: O(n), pois o algoritmo utiliza um array temporário para armazenar os elementos durante a mesclagem, cujo tamanho é proporcional ao tamanho do array original.