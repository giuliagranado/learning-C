// função bubble sort
/* o maior item borbulha para o final, comparação de 2 em 2  */

#include <stdio.h>     // biblioteca padrão de entrada e saída
#include <stdlib.h>    // biblioteca para rand()

int bubble_sort(int array[], int n) {
    int i, j, temp;
    int comparacoes = 0;   //variavel para contar as comparacoes
    int troca;

 for (i = 0 ; i < n-1; i++) {   //loop p percorrer o array
    troca = 0; //variavel para verificar se houve troca
    for (j = 0; j < n-i-1; j++) { // compara o elemento anterior com o atual
        comparacoes++ ; // incrementa o contador de comparações
        if (array[j] > array[j+1]) { // se for maior, troca a posição
            temp = array[j];
            array[j] = array[j+1];
            array[j+1] = temp;
            troca = 1; // houve uma troca
        }
    }
    if (troca == 0) break;  // array já está ordenado, encerra o loop 
    }
return comparacoes;
}


// para exibir o array
 void printArray(int array[], int n){
    int i;   //declara variavel p o loop
    for (i = 0; i< n; i++) {
        printf("%d ", array[i]);  // imprime o elemento atual do array
    }
    printf("\n");  // quebra de linha
 }

 // função principal
 int main() {
    int comparacoes, i, r;
    int n = 100;              //tamanho do vetor
    int *arr = malloc(n * sizeof(int)); ///cria um vetor de tamanho n
    
    /*CASO MEDIO*/
    for (i = 0; i < n; i++) {
      r = rand()%1000;    //cria um aleatorio entre 0 e 999
      arr[i] = r;         //coloca o aleatorio no vetor
    }
    comparacoes = bubble_sort(arr, n);/*chama a ordenacao para o array criado
                        guarda o retorno na variavel comparacoes*/
    printf("Caso medio: %d\n", comparacoes);//imprime o numero de comparacoes

    /*MELHOR CASO*/
    for (i = 0; i < n; i++) {
      arr[i] = i;
    }
    comparacoes = bubble_sort(arr, n);
    printf("Melhor caso: %d\n", comparacoes);

    /*PIOR CASO*/
    for (i = 0 ; i < n; i++) {
      arr[i] = n-i;
    }
    comparacoes = bubble_sort(arr, n);
    printf("Pior caso: %d\n", comparacoes);

    free(arr);  // libera a memória alocada
    return comparacoes;
}

// finitude: o laço externo executa n-1 vezes e o laço interno executa n-i-1 vezes, garantindo que o número de iterações diminui a cada passagem.
// corretude: após cada iteração do laço externo, o maior elemento não ordenado é colocado na posição correta, garantindo que o array estará ordenado ao final do processo.
// complexidade: no pior caso O(n^2), vetor em ordem descrescente. No melhor caso O(n), vetor em ordem crescente, 0 movimentações. no caso médio, a complexidade é O(n^2) devido aos dois laços aninhados.
// custo memorial: O(1), pois o algoritmo utiliza um número constante de variáveis auxiliares, independentemente do tamanho do array.