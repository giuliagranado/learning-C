// busca binaria

#include <stdio.h>
int busca_sequencial (int x, int v[], int p, int r){
    while (p <= r){
        int m = (p+ r)/2;
        if (x == v[m]) return m;
        if (x < v[m]) r = m -1;
        else p = m + 1;
    }
    return -1;
}

// finitude: quando encontrar o x no vetor ou tiver percorrido todo ele (p > r)  
// corretude: : v[p-1] < x < v[r+1], se x estiver no vetor, retorna a posição correta; se não, retorna -1
// complexidade: no pior caso O(lg n). No melhor caso O(1) - constante, se o elemento  é encontrado na primeira iteração