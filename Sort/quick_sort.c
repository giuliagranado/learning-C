// função quick sort
/* escolhe um pivô e particiona o array em dois subarrays: elementos menores e outro com elementos maiores */
#include <stdio.h>
#include <stdlib.h>

// função auxiliar para particionar o array
int partition(int array[], int low, int high, int *comparacoes) {
    int pivot = array[high]; // escolhe o último elemento como pivô
    int i = low - 1;
    int temp;

    for (int j = low; j < high; j++) {
        (*comparacoes)++;
        if (array[j] <= pivot) {
            i++;
            temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    temp = array[i+1];
    array[i+1] = array[high];
    array[high] = temp;

    return i+1;
}

// função recursiva do quick sort
void quick_sort(int array[], int low, int high, int *comparacoes) {
    if (low < high) {
        int pi = partition(array, low, high, comparacoes);
        quick_sort(array, low, pi - 1, comparacoes);
        quick_sort(array, pi + 1, high, comparacoes);
    }
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
    comparacoes = 0;
    quick_sort(arr, 0, n - 1, &comparacoes);
    printf("Caso medio: %d\n", comparacoes);

    /* MELHOR CASO (já ordenado) */
    for (i = 0; i < n; i++) {
        arr[i] = i;
    }
    comparacoes = 0;
    quick_sort(arr, 0, n - 1, &comparacoes);
    printf("Melhor caso: %d\n", comparacoes);

    /* PIOR CASO (ordenado decrescente) */
    for (i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    comparacoes = 0;
    quick_sort(arr, 0, n - 1, &comparacoes);
    printf("Pior caso: %d\n", comparacoes);

    free(arr);
    return 0;
}

// finitude: A cada chamada recursiva, o array é particionado em subarrays menores, garantindo que o tamanho do problema diminui a cada passo até atingir o caso base.
// corretude: O algoritmo organiza os elementos em ordem crescente ao garantir que todos os elementos menores que o pivô fiquem à esquerda e os maiores à direita, repetindo esse processo recursivamente.
// complexidade: No pior caso, a complexidade é O(n^2) quando o array já está ordenado ou quase ordenado. No melhor e médio caso, a complexidade é O(n log n) devido à divisão equilibrada dos subarrays.