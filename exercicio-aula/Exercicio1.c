#include <stdio.h> // biblioteca padrão de entrada e saída
#include <stdlib.h> // biblioteca padrão

void função_exercicio1(int A[], int n) {
int j, i, ch;
for (j = 2; j < n; j++) {
    ch = A[j];
    i = j-1;
    while (i>= 1 && A[i] > ch){
        A[i+1] = A[i];
        i = i-1;
    }
    A[i+1] = ch;
}
printArray(A, n);
}

// para exibir o array
 void printArray(int A[], int n) {
    int i;   //declara variavel p o loop
    for (i = 0; i< n; i++) {
        printf("%d ", A[i]);  // imprime o elemento atual do array
    }
 }

