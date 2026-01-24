// codigo dado de exemplo para resolução da P2 

#include <stdio.h>

int sort(int arr[], int n)
{
    int comparacoes = 0;//cria a variavel que irá contar as comparacoes
    int i;
    for (i = 0; i < n-1; i++)
    {
      /*codigo*/
        for (int j = i+1; j < n; j++){
          comparacoes++;/*antes da comparacao acontecer
                      incrementamos a variavel de contagem*/
          if (arr[j] < arr[i]){
            /*codigo*/
          }
        }
        /*codigo*/
    }
    //ao terminar de ordenar, retorna o numero de comparacoes
    return comparacoes;
}


int main()
{
    int comparacoes, i, n, r;
    n = 100;              //tamanho do vetor
    int arr[n];           //cria um vetor de tamanho n

    /*CASO MEDIO*/
    for (i = 0; i < n; i++) {
      r = rand()%1000;    //cria um aleatorio entre 0 e 999
      arr[i] = r;         //coloca o aleatorio no vetor
    }
    comparacoes = sort(arr, n);/*chama a ordenacao para o array criado
                        guarda o retorno na variavel comparacoes*/
    printf("Caso medio: %d\n", comparacoes);//imprime o numero de comparacoes

    /*MELHOR CASO*/
    for (i = 0; i < n; i++) {
      arr[i] = i;
    }
    comparacoes = sort(arr, n);
    printf("Melhor caso: %d\n", comparacoes);

    /*PIOR CASO*/
    for (i = 0 ; i < n; i++) {
      arr[i] = n-i;
    }
    comparacoes = sort(arr, n);
    printf("Pior caso: %d\n", comparacoes);

    return 0;
}