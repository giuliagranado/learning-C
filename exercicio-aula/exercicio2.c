#include <stdio.h> // biblioteca padrão de entrada e saída
#include <stdlib.h> // biblioteca padrão

void funcao_maximo (int A[], int n) { 
    int max = A[0];
    for(int i =1; i < n; i++){
        if (A[i]> max) {
            max = A[i];
        }
    }
    printf("%d\n", max);
}

int main() {
    int n; 
    // entrada do tamanho do vetor 
    printf("Digite o tamanho do vetor: "); 
    scanf("%d", & n);

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
    funcao_maximo(A, n); 

    free(A); // libera memória
    return 0; 
}

// complexidade de tempo: O(n) -> cresce linearmente com n
// complexidade de espaço: O(1) -> constante, usa apenas a variavel max além do vetor de entrada