// busca sequencial

#include <stdio.h>
int busca_sequencial (int x, int v[], int p, int r){
    int j = p;
    while (j<= r && v[j] < x) ++j;
    if (j <= r && v[j] == x) return j;
    else return -1;
}

// finitude: quando encontrar o x no vetor ou  tiver percorrido todo ele (j > r)
// corretude: se x estiver no vetor, retorna a posição correta; se não, retorna -1 
// complexidade: no pior caso O(n)- linear , pois pode ser necessário percorrer todo o vetor. No melhor caso O(1) - constante, se o elemento estiver na primeira posição