// sort_block or giu_sort

/* uma mistura do merge sort e do selection sort, como resposta ao exercicio proposto em aula de criar um algortimo de ordenação  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ---------- Funções de comparação ----------
int cmpInt(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x - y);
}

int cmpFloat(const void* a, const void* b) {
    float x = *(const float*)a;
    float y = *(const float*)b;
    return (x > y) - (x < y); // retorna -1, 0 ou 1
}

int cmpStr(const void* a, const void* b) {
    const char* x = *(const char**)a;
    const char* y = *(const char**)b;
    return strcmp(x, y);
}

// ---------- Funções auxiliares ----------
void swap(void* a, void* b, size_t size) {
    char* temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

// Ordena blocos pequenos com selection sort
int sortBlock(void* arr, int start, int end, size_t size, int (*cmp)(const void*, const void*)) {
    int comparacoes = 0;
    char* base = (char*)arr;
    for (int i = start; i < end; i++) {
        int min_idx = i;
        for (int j = i+1; j <= end; j++) {
            comparacoes++;
            if (cmp(base + j*size, base + min_idx*size) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) swap(base + i*size, base + min_idx*size, size);
    }
    return comparacoes;
}

// Mescla dois blocos ordenados
int mergeBlocks(void* arr, int start, int mid, int end, size_t size, int (*cmp)(const void*, const void*)) {
    int comparacoes = 0;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    char* base = (char*)arr;
    char* L = malloc(n1 * size);
    char* R = malloc(n2 * size);

    memcpy(L, base + start*size, n1*size);
    memcpy(R, base + (mid+1)*size, n2*size);

    int i=0, j=0, k=start;
    while (i<n1 && j<n2) {
        comparacoes++;
        if (cmp(L + i*size, R + j*size) <= 0) {
            memcpy(base + k*size, L + i*size, size);
            i++;
        } else {
            memcpy(base + k*size, R + j*size, size);
            j++;
        }
        k++;
    }
    while (i<n1) {
        memcpy(base + k*size, L + i*size, size);
        i++; k++;
    }
    while (j<n2) {
        memcpy(base + k*size, R + j*size, size);
        j++; k++;
    }

    free(L); free(R);
    return comparacoes;
}

// ---------- Algoritmo híbrido genérico ----------
int blockMergeSort(void* arr, int n, size_t size, int (*cmp)(const void*, const void*)) {
    int comparacoes = 0;

    // Ordena blocos de 4
    for (int i=0; i<n; i+=4) {
        int end = (i+3<n)? i+3 : n-1;
        comparacoes += sortBlock(arr, i, end, size, cmp);
    }

    // Mescla blocos progressivamente
    int blockSize = 4;
    while (blockSize < n) {
        for (int start=0; start<n; start+=2*blockSize) {
            int mid = start + blockSize - 1;
            int end = (start + 2*blockSize - 1 < n)? start + 2*blockSize - 1 : n-1;
            if (mid < end) comparacoes += mergeBlocks(arr, start, mid, end, size, cmp);
        }
        blockSize *= 2;
    }
    return comparacoes;
}

// ---------- Função principal ----------
int main() {
    clock_t inicio, fim;
    double tempo;
    int comparacoes;

    // Teste com inteiros
    //int arrInt[] = {12, 4, 7, 9, 1, 3, 15, 8}; // ordem aleatoria
    int arrInt[] = {15, 12, 9,8, 7, 4, 3, 1};  //descrecente
    //int arrInt[] = {1, 3, 4, 7, 8, 9, 12, 15}; // ordenado
    int nInt = sizeof(arrInt)/sizeof(arrInt[0]);
    inicio = clock();
    comparacoes = blockMergeSort(arrInt, nInt, sizeof(int), cmpInt);
    fim = clock();
    tempo = (double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("\nInteiros ordenados:\n");
    for (int i=0; i<nInt; i++) printf("%d ", arrInt[i]);
    printf("\nComparacoes: %d | Tempo: %f s\n", comparacoes, tempo);

    // Teste com floats
   // float arrFloat[] = {-2.70, 0.00, 1.50, 2.20, 3.14, 9.80}; // ordenado
   float arrFloat[] = {9.80, 3.14, 2.20, 1.50, 0.00 ,-2.70}; // descrecente
    //float arrFloat[] = {3.14, -2.7, 0.0, 1.5, 9.8, 2.2}; // ordem aleatoria
    int nFloat = sizeof(arrFloat)/sizeof(arrFloat[0]);
    inicio = clock();
    comparacoes = blockMergeSort(arrFloat, nFloat, sizeof(float), cmpFloat);
    fim = clock();
    tempo = (double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("\nFloats ordenados:\n");
    for (int i=0; i<nFloat; i++) printf("%.2f ", arrFloat[i]);
    printf("\nComparacoes: %d | Tempo: %f s\n", comparacoes, tempo);

    // Teste com strings
    //char* arrStr[] = {"Ana", "Beatriz", "Carlos", "Daniel", "Joao"}; // ordenado
    char* arrStr[] = {"Joao","Daniel", "Carlos", "Beatriz","Ana" }; // descrecente
    //char* arrStr[] = {"Carlos", "Ana", "Beatriz", "Joao", "Daniel"}; // ordem aleatoria
    int nStr = sizeof(arrStr)/sizeof(arrStr[0]);
    inicio = clock();
    comparacoes = blockMergeSort(arrStr, nStr, sizeof(char*), cmpStr);
    fim = clock();
    tempo = (double)(fim-inicio)/CLOCKS_PER_SEC;
    printf("\nStrings ordenadas:\n");
    for (int i=0; i<nStr; i++) printf("%s ", arrStr[i]);
    printf("\nComparacoes: %d | Tempo: %f s\n", comparacoes, tempo);

    return 0;
}


// finitude: O algoritmo termina porque o tamanho dos blocos aumenta exponencialmente, garantindo que eventualmente todo o array será mesclado em um único bloco ordenado.
// corretude: O algoritmo primeiro ordena pequenos blocos de 4 elementos, garantindo que cada bloco esteja em ordem crescente. Em seguida, mescla esses blocos ordenados, preservando a ordem, até que todo o array esteja ordenado.
// complexidade: A complexidade de tempo do algoritmo é O(n log n) no pior, médio e melhor caso, devido à natureza do merge sort na fase de mesclagem, enquanto a ordenação dos blocos de 4 é O(n).