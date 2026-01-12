#include <stdio.h> // biblioteca padrão de entrada e saída

int i, j, S;

void função3 (int n){
    S = 0;
    for (i = 2; i < n; i++){
        for (j =i; j<n ; j++ ){
            S = S + 1;
        }
    }
}