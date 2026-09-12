#include <stdio.h>

/* =========================================================================
 * RESPOSTAS DAS QUESTOES DE ANALISE
 * =========================================================================
 * 1. Duplica o valor em outra posicao de memoria, não altera a variavel original
 * 2. Não, pois a funcao modifica apenas a cópia local
 * 3. É uma variavel que guarda o endereco de memoria de outra variavel
 * 4. Pega onde a variavel esta na memoria
 * 5. Indica na declaracao que a variavel criada é um ponteiro
 * 6. O endereco de memoria da variavel numero
 * 7. O valor guardado dentro do endereco apontado (o número 10)
 * 8. Porque recebe os enderecos de memoria e usa o * para mudar o valor original
 * 9. O primeiro recebe uma copia, o segundo recebe o endereco e altera o original
 * 10. É simulada, C só passa por copia.
 * ========================================================================= */

// Parte 1
float calcularMedia(float nota1, float nota2) {
    return (nota1 + nota2) / 2.0;
}

// Parte 2
void adicionarPonto(float nota) {
    nota = nota + 1.0;
    printf("Nota dentro da funcao: %.2f\n", nota);
}

// Parte 4
void adicionarPontoReferencia(float *nota) {
    *nota = *nota + 1.0;
}

// Parte 5
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    // Parte 1
    float nota1, nota2;
    printf("Digite a nota 1: ");
    scanf("%f", &nota1);
    printf("Digite a nota 2: ");
    scanf("%f", &nota2);

    float media = calcularMedia(nota1, nota2);
    printf("Nota 1: %.2f\n", nota1);
    printf("Nota 2: %.2f\n", nota2);
    printf("Media: %.2f\n", media);

    if (media >= 6.0) {
        printf("Situacao: Aprovado\n\n");
    } else {
        printf("Situacao: Reprovado\n\n");
    }

    // Parte 2
    printf("Nota antes no main: %.2f\n", media);
    adicionarPonto(media);
    printf("Nota depois no main: %.2f\n\n", media);

    // Parte 3
    float nota = 7.5;
    float *ponteiroNota = &nota;

    printf("1. Valor de nota: %.2f\n", nota);
    printf("2. Endereco de nota: %p\n", &nota);
    printf("3. Endereco no ponteiro: %p\n", ponteiroNota);
    printf("4. Valor pelo ponteiro: %.2f\n\n", *ponteiroNota);

    // Parte 4
    printf("Nota antes no main: %.2f\n", nota);
    adicionarPontoReferencia(&nota);
    printf("Nota depois no main: %.2f\n\n", nota);

    // Parte 5
    int a, b;
    printf("Digite o valor de a: ");
    scanf("%d", &a);
    printf("Digite o valor de b: ");
    scanf("%d", &b);

    printf("Antes: a = %d, b = %d\n", a, b);
    trocar(&a, &b);
    printf("Depois: a = %d, b = %d\n", a, b);

    return 0;
}
