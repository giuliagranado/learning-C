#include <stdio.h>
 #include <stdlib.h>
 
void adicionarElemento(int **p, int x) {
 (**p) = x;
 (*p)++;
 }

void mostrarElementos(int *p, int t){
 for(int i =0; i < t; i ++){
 printf("%d\n", *p);
 p++;
 }
 }
 void removerElemento(int **p){
 (*p)--;
 }

int main(void) {
 int *p, t, *inic;

 if (scanf("%d", &t) != 1 || t < 2) {
 fprintf(stderr, "Informe um tamanho de vetor maior ou igual a 2.\n");
 return EXIT_FAILURE;
 }

 p = malloc(sizeof(*p) * (size_t)t);
 if (p == NULL) {
 fprintf(stderr, "Nao foi possivel alocar memoria.\n");
 return EXIT_FAILURE;
 }

 inic = p;
 adicionarElemento(&p, 20);
 adicionarElemento(&p, 30);
 mostrarElementos(inic,t);
 // printf("%d %d\n", inic[0], inic[1]);
 free(inic);
