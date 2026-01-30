// Pilhas e Filas
// feito pelo prof
/* Implementado com lista duplamente encadeada,

Que tal pegar o programa e melhorar o algoritmo para usar lista simples?
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Control;

// --- Funções de Base ---

Control* criar() {
    Control *c = (Control*)malloc(sizeof(Control));
    c->head = NULL;
    c->tail = NULL;
    return c;
}

void inserir_no_fim(Control *c, int valor) {
    Node *novo = (Node*)malloc(sizeof(Node));
    novo->data = valor;
    novo->next = NULL;
    novo->prev = c->tail;

    if (c->tail != NULL) {
        c->tail->next = novo;
    } else {
        c->head = novo;
    }
    c->tail = novo;
}

int remover_do_inicio(Control *c) {
    if (c->head == NULL) return -1;

    Node *temp = c->head;
    int valor = temp->data;
    c->head = temp->next;

    if (c->head != NULL) c->head->prev = NULL;
    else c->tail = NULL;

    free(temp);
    return valor;
}

int remover_do_fim(Control *c) {
    if (c->tail == NULL) return -1;

    Node *temp = c->tail;
    int valor = temp->data;
    c->tail = temp->prev;

    if (c->tail != NULL) c->tail->next = NULL;
    else c->head = NULL;

    free(temp);
    return valor;
}

// --- Novas Funções de Impressão ---

void imprimir_pilha(Control *c) {
    if (c->tail == NULL) {
        printf("\n[Erro]: Pilha vazia!\n");
        return;
    }
    printf("\n--- TOPO ---\n");
    Node *atual = c->tail; // Começa pelo último inserido
    while (atual != NULL) {
        printf("|  %d  |\n", atual->data);
        atual = atual->prev;
    }
    printf("------------\n");
}

void imprimir_fila(Control *c) {
    if (c->head == NULL) {
        printf("\n[Erro]: Fila vazia!\n");
        return;
    }
    printf("\nINICIO: ");
    Node *atual = c->head;
    while (atual != NULL) {
        printf("[%d] ", atual->data);
        if (atual->next != NULL) printf("-> ");
        atual = atual->next;
    }
    printf(": FIM\n");
}

// --- Funções de Limpeza Iterativa ---

void limpar_estrutura(Control *c, int tipo, int silencioso) {
    if (!silencioso && c->head == NULL) {
        printf("\nEstrutura ja esta vazia.\n");
        return;
    }
    
    if (!silencioso) printf("\nLimpando estrutura...\n");
    while (c->head != NULL) {
        int v = (tipo == 1) ? remover_do_fim(c) : remover_do_inicio(c);
        if (!silencioso) printf("Removendo: %d\n", v);
    }
}

// --- Menus ---

void menu_operacoes(Control *c, int tipo) {
    int opcao, valor;
    char *nome = (tipo == 1) ? "PILHA" : "FILA";

    do {
        printf("\n>>> MENU %s <<<\n", nome);
        printf("1. Inserir (Push/Enqueue)\n");
        printf("2. Remover (Pop/Dequeue)\n");
        printf("3. Imprimir Estrutura\n");
        printf("4. Limpar e Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Valor: ");
                scanf("%d", &valor);
                inserir_no_fim(c, valor);
                break;
            case 2:
                valor = (tipo == 1) ? remover_do_fim(c) : remover_do_inicio(c);
                if (valor != -1) printf("Removido com sucesso: %d\n", valor);
                else printf("\n[Erro]: Nao ha elementos para remover!\n");
                break;
            case 3:
                if (tipo == 1) imprimir_pilha(c);
                else imprimir_fila(c);
                break;
            case 4:
                limpar_estrutura(c, tipo, 0);
                break;
            default:
                if(opcao != 4) printf("Opcao invalida!\n");
        }
    } while (opcao != 4);
}

int main() {
    int opcao;
    Control *pilha = criar();
    Control *fila = criar();

    do {
        printf("\n=============================\n");
        printf("    GERENCIADOR DE MEMORIA\n");
        printf("=============================\n");
        printf("1. Pilha (LIFO)\n");
        printf("2. Fila (FIFO)\n");
        printf("3. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) menu_operacoes(pilha, 1);
        else if (opcao == 2) menu_operacoes(fila, 2);

    } while (opcao != 3);

    // Limpeza final obrigatória ao sair
    limpar_estrutura(pilha, 1, 1);
    limpar_estrutura(fila, 2, 1);
    free(pilha);
    free(fila);

    printf("\nMemoria liberada. Ate logo!\n");
    return 0;
}