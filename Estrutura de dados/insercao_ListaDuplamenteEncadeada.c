//lista duplamente encadeada - inserção

#include <stdio.h>
#include <stdlib.h>

// Estrutura do Nó Duplamente Encadeado
struct No {
    int valor;
    struct No* next;  // ponteiro para o nó da frente
    struct No* prev; // ponteiro para o nó de trás
};

struct No* head = NULL;

void inserirNoInicio(int valor);
void inserirNoMeio(int valor, int indice);  // + validação de índice 
void imprimirLista();


// --- Funções ---

void inserirNoInicio(int novoValor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = novoValor;
    
    novoNo->next = head;
    novoNo->prev = NULL; // o novo 1º elemento, logo o antecessor é NULL

    if (head != NULL) {
        head->prev = novoNo; // se o head não é null, agora o antigo 1º aponta para o novo 1º 
    }

    head = novoNo;
    printf("Valor %d inserido no inicio.\n", novoValor);
}

void inserirNoMeio(int novoValor, int indice){
    // Alocação do novo nó
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = novoValor;

    // CASO A: Lista Vazia
    if (head == NULL) {
        printf("Lista vazia! Inserindo o valor %d no inicio (posicao 0).\n", novoValor);
        novoNo->next = NULL;
        novoNo->prev = NULL;
        head = novoNo;
        return;
    }

    // CASO B: Inserção no índice 0 
    if (indice <= 0) { 
        novoNo->next = head;
        novoNo->prev = NULL;
        if (head != NULL){
            head->prev = novoNo;
        }
        head = novoNo;
        printf("Inserido %d na cabeca (indice 0).\n", novoValor);
        return;
    }

    // CASO C: Percorrer para encontrar a posição ou o fim da lista
    struct No* atual = head;
    int i = 0;

    while (i < indice - 1 && atual->next != NULL) {
        atual = atual->next;
        i++;
    }

    // Verificação se a posição é válida 
    if (atual->next == NULL && i < indice - 1) {
        printf("Posição %d inválida. Inserindo %d no final.\n", indice, novoValor);
        novoNo->next = NULL;
        novoNo->prev = atual;
        atual->next = novoNo;
    } 
    // Inserção Normal no meio da lista
    else {
        novoNo->next = atual->next;
        atual->next = novoNo;
        if (novoNo->next != NULL) {
            novoNo->next->prev = novoNo; // atualiza o prev do próximo nó
        }
        printf("Sucesso: Valor %d inserido na posicao %d.\n", novoValor, indice);
    }
}

void imprimirLista() {
    struct No* atual = head;

    if (atual == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    printf("Elementos da lista: ");
    while (atual != NULL) {
        printf("%d <-> ", atual->valor);
        atual = atual->next;
    }
    printf("NULL\n");
}

// --- Fim das Funções ---
int main() {
    inserirNoInicio(10);
    inserirNoInicio(20);
    inserirNoMeio(15, 1); // Inserir 15 na posição 1
    inserirNoMeio(5, 0);  // Inserir 5 na posição 0
    inserirNoMeio(25, 10); // Inserir 25 em uma posição inválida (final)

    imprimirLista();

    return 0;
}