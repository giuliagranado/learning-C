#include <stdio.h> // biblioteca padrão de entrada e saída

#include <stdio.h>

int funcao3(int n) {
    if (n < 4) return 0; // não há pares válidos
    return (n - 3) * (n - 2) / 2;
}

int main() {
    int n;
    printf("Digite um valor para n: ");
    scanf("%d", & n);

    int S = funcao3(n);
    printf("S = %d\n", S);

    return 0;
}
//função que recebe um inteiro n e retorna o número de pares (i, j) tais que 1 ≤ i < j ≤ n e j - i ≥ 3.

// complexidade de tempo: O(1) -> constante, não cresce com n
// complexidade de espaço: O(1) -> usa espaço fixo e apenas variaveis locais