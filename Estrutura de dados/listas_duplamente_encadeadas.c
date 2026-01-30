//lista duplamente encadeada - falta

#include <stdio.h>
#include <stdlib.h>

// Essa é uma versão de programa para listas duplamente encadeadas.
// Não implementei todas as funções como fiz na encadeadas simples
// Fica como exercício o aluno fazer estes complementos.


// Estrutura do Nó Duplamente Encadeado
struct No {
    int valor;
    struct No* proximo;
    struct No* anterior; // DIFERENÇA: Ponteiro para o nó de trás
};

struct No* head = NULL;

// --- Protótipos das Funções ---
void inserirNoInicio(int valor);
void inserirNoFinal(int valor);
//void inserirNaPosicao(int valor, int indice); // falta add
void removerDoInicio();
void removerDoFinal();
//void removerNaPosicao(int indice); // falta add
//void removerPorValor(int valor); // falta add
void buscarValor(int valor);
void imprimirLista();
void limparLista();
//int acharTamanhoIterativo(); // falta add
//int acharTamanhoRecursivo(struct No* atual); // falta add

// --- Implementação das Funções ---

void inserirNoInicio(int novoValor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = novoValor;
    
    novoNo->proximo = head;
    novoNo->anterior = NULL; // DIFERENÇA: Como é o novo primeiro, o anterior é NULL

    if (head != NULL) {
        head->anterior = novoNo; // DIFERENÇA: O antigo primeiro agora aponta para trás para o novo
    }
    
    head = novoNo;
    printf("Valor %d inserido no inicio.\n", novoValor);
}

void inserirNoFinal(int novoValor) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = novoValor;
    novoNo->proximo = NULL;

    if (head == NULL) {
        novoNo->anterior = NULL;
        head = novoNo;
    } else {
        struct No* atual = head;
        while (atual->proximo != NULL) atual = atual->proximo;
        
        atual->proximo = novoNo;
        novoNo->anterior = atual; // DIFERENÇA: O novo nó aponta para trás para o antigo último
    }
    printf("Valor %d inserido no final.\n", novoValor);
}

void removerDoInicio() {
    if (head == NULL) return;

    struct No* temp = head;
    head = head->proximo;

    if (head != NULL) {
        head->anterior = NULL; // DIFERENÇA: O novo primeiro nó não tem ninguém atrás dele
    }

    printf("Valor %d removido do inicio.\n", temp->valor);
    free(temp);
}

void removerDoFinal() {
    if (head == NULL) return;

    if (head->proximo == NULL) {
        free(head);
        head = NULL;
        return;
    }

    struct No* atual = head;
    while (atual->proximo != NULL) atual = atual->proximo;

    // DIFERENÇA: Não precisamos de atual->proximo->proximo.
    // O penúltimo é simplesmente atual->anterior.
    struct No* penultimo = atual->anterior;
    penultimo->proximo = NULL;

    printf("Valor %d removido do final.\n", atual->valor);
    free(atual);
}

void buscarValor(int valorProcurado) {
    struct No* atual = head;
    int i = 0;
    while (atual != NULL) {
        if (atual->valor == valorProcurado) {
            printf("Encontrado na posicao %d.\n", i);
            return;
        }
        atual = atual->proximo;
        i++;
    }
    printf("Valor nao encontrado.\n");
}

void imprimirLista() {
    struct No* atual = head;
    printf("\nLISTA ATUAL: ");
    if (atual == NULL) printf("A lista esta vazia.\n");
    while (atual != NULL) {
        printf("[%d] <=> ", atual->valor); // Representação visual da conexão dupla
        atual = atual->proximo;
    }
    printf("NULL\n");
}

void limparLista() {
    while (head != NULL) {
        removerDoFinal();
    }
}

// --- add (ou tentando) o restante das funções ---

void inserirNaPosicao(int novoValor, int indice) {
    // 1. Alocação do novo nó
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = novoValor;
    novoNo->anterior = NULL;

    // 2. CASO A: Lista Vazia
    if (head == NULL) {
        printf("Lista vazia! Inserindo o valor %d no inicio (posicao 0).\n", novoValor);
        novoNo->proximo = NULL;
        novoNo->anterior = NULL;
        head = novoNo;
        return;
    }

    // 3. CASO B: Inserção no índice 0 (mesmo com lista não vazia)
    if (indice <= 0) {
        novoNo->proximo = head;
        novoNo->anterior = NULL;
        head->anterior = novoNo;
        head = novoNo;
        printf("Inserido %d na cabeca (indice 0).\n", novoValor);
        return;
    }

    // 4. CASO C: Percorrer para encontrar a posição ou o fim da lista
    struct No* atual = head;
    int i = 0;

    // Queremos parar no nó ANTERIOR à posição desejada (indice - 1)
    // OU parar no último nó disponível
    while (i < indice - 1 && atual->proximo != NULL
    ) {
        atual = atual->proximo;

        i++;
    }

    // Verificação de Fallback: Se paramos porque a lista acabou antes do índice
    if (atual->proximo == NULL && i < indice - 1) {
        printf("A lista possui menos de %d elementos. Inserindo %d no final (posicao %d).\n", indice, novoValor, i + 1);
        novoNo->proximo = NULL;
        atual->proximo = novoNo;
    } 
    // Inserção Normal no meio da lista
    else {
        novoNo->proximo = atual->proximo;
        atual->proximo = novoNo;
        printf("Sucesso: Valor %d inserido na posicao %d.\n", novoValor, indice);
    }
}








// --- Menu Interativo ---

int main() {
    int opcao, valor;

    do {
        system("clear");
        printf("--- MENU LISTA DUPLAMENTE ENCADEADA ---\n");
        imprimirLista();
        printf("\n1. Inserir no Inicio\n2. Inserir no Final\n");
        printf("3. Remover do Inicio\n4. Remover do Final\n");
        printf("5. Buscar Valor\n0. Sair\n");
        printf("\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: printf("Valor: "); scanf("%d", &valor); inserirNoInicio(valor); break;
            case 2: printf("Valor: "); scanf("%d", &valor); inserirNoFinal(valor); break;
            case 3: removerDoInicio(); break;
            case 4: removerDoFinal(); break;
            case 5: printf("Busca: "); scanf("%d", &valor); buscarValor(valor); break;
            case 0: limparLista(); break;
        }
        
        if (opcao != 0) {
            printf("\nEnter para continuar...");
            getchar(); getchar();
        }
    } while (opcao != 0);

    return 0;
}