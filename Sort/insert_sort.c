#include <stdio.h>
#include <stdlib.h>

// função insertion sort com contagem de comparações
int insert_sort(int array[], int n) {
    int i, key, j;
    int comparacoes = 0;
    for (i = 1; i < n; i++) {
        key = array[i];
        j = i - 1;

        // compara e desloca enquanto necessário
        while (j >= 0) {
            comparacoes++; // conta a comparação
            if (array[j] > key) {
                array[j+1] = array[j];
                j = j - 1;
            } else {
                break; // se não precisa trocar, sai do while
            }
        }
        array[j + 1] = key;
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
    comparacoes = insert_sort(arr, n);
    printf("Caso medio: %d\n", comparacoes);

    /* MELHOR CASO (já ordenado) */
    for (i = 0; i < n; i++) {
        arr[i] = i;
    }
    comparacoes = insert_sort(arr, n);
    printf("Melhor caso: %d\n", comparacoes);

    /* PIOR CASO (ordenado decrescente) */
    for (i = 0; i < n; i++) {
        arr[i] = n - i;
    }
    comparacoes = insert_sort(arr, n);
    printf("Pior caso: %d\n", comparacoes);

    free(arr);
    return 0;
}
// finitude: A cada iteração do loop externo, o índice 'i' é incrementado, garantindo que o loop termine após 'n-1' iterações.
// corretude: O algoritmo insere cada elemento na posição correta dentro da sublista ordenada à esquerda, garantindo que o array esteja ordenado ao final do processo.
// complexidade: No pior caso (array ordenado em ordem decrescente), a complexidade é O(n^2). No melhor caso (array já ordenado), a complexidade é O(n). A complexidade média também é O(n^2).
//custo de memoria: O algoritmo utiliza espaço adicional constante O(1), já que a ordenação é feita in-place, sem necessidade de estruturas auxiliares proporcionais ao tamanho do array.