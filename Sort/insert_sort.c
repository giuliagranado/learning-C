// função insert sort
#include <stdio.h>     // biblioteca padrão de entrada e saída

void insert_sort(int array[], int n) {
    int i, key, j;

 for (i = 1 ; i < n; i++) {   //loop p percorrer o array
    key = array[i];
    j = i - 1;

    while ( j >= 0 && array[j] > key){ // compara o elemento anterior com o atual - enquanto for maior -> troca
        array[j+1] = array[j];   // se for maior, troca a posição
        j = j - 1;
    }
    array[j + 1] = key;  // insere o key na posição correta
 }
}

// para exibir o array
 void printArray(int array[], int n) {
    int i;   //declara variavel p o loop
    for (i = 0; i< n; i++) {
        printf("%d ", array[i]);  // imprime o elemento atual do array
    }
    printf("\n");  // quebra de linha
 }

 // função principal
 int main() {
    int array[] = {12,11,13,5,6}; // declara e inicia o array
    int n = sizeof(array)/sizeof(array[0]); //calcula n de elementos do array

    printf("Array original: \n");
    printArray(array,n); //chama função p/ imprimir array original

    insert_sort(array,n); // chama a função 

    printf("Array ordernado: \n");
    printArray(array,n); // chama função p/ imprimir o array já ordenado

    return 0;  // retorna 0 p/ indicar q o programa terminou com sucesso

    }