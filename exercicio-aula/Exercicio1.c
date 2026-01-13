#include <stdio.h> // biblioteca padrão de entrada e saída
#include <stdlib.h> // biblioteca padrão

// função para imprimir o array
void printArray(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);  // imprime o elemento atual do array
    }
    printf("\n"); // quebra de linha no final
}

// função de ordenação (insertion sort)
void funcao_exercicio1(int A[], int n) {
    int j, i, ch;
    for (j = 1; j < n; j++) {   
        ch = A[j];
        i = j - 1;
        while (i >= 0 && A[i] > ch) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = ch;
    }
    printArray(A, n);
}

int main() {
    int n; 
    // entrada do tamanho do vetor 
    printf("Digite o tamanho do vetor: "); 
    scanf("%d", &n);

    // alocação dinâmica 
    int *A = (int*) malloc(n * sizeof(int));
     if (A == NULL) { 
        printf("Erro ao alocar memória!\n"); 
        return 1; 
    }

    // entrada dos elementos do vetor 
    printf("Digite %d elementos:\n", n); 
    for (int i = 0; i < n; i++) {
        scanf("%d", &A[i]); 
    }

    // chama a função de ordenação 
    funcao_exercicio1(A, n); 

    free(A); // libera memória
    return 0; 
}

// complexidade de tempo: O(n^2) -> for alinhado com while, no pior caso pode percorrer quase todo vetor [O(n) × O(n) = O(n²)]
// complexidade de espaço: O(1) -> constante, usa apenas variaveis simples além do vetor de entrada