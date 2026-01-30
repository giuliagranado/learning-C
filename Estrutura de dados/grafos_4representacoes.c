#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Definição de tipo para representar o vértice como um caractere (A, B, C...)
#define Vertice char
#define MAX_VERTICES 26

/**
 * REPRESENTAÇÃO 1: EDGE LIST (LISTA DE ARCOS)
 * Estrutura física que armazena o arco original com nomes (letras) e o peso.
 */
typedef struct {
    Vertice ponta_inicial;
    Vertice ponta_final;
    int peso;
} ARCO;

/**
 * REPRESENTAÇÃO 2: LISTA DE ADJACÊNCIA
 * Cada índice do vetor representa um vértice que aponta para uma lista de vizinhos.
 */
typedef struct Node {
    int vertice_idx; 
    int peso;
    struct Node* proximo;
} Node;

/**
 * ESTRUTURA PRINCIPAL DO GRAFO
 * Agrega as 4 representações e gerencia a memória de forma dinâmica.
 */
typedef struct {
    int numVerticesAtivos; 
    int numArestasAtual;   
    int capacidadeArestas; 
    int eDirecionado;
    int temPeso;
    
    // Controle de existência (A-Z) para filtrar a impressão
    bool existeVertice[MAX_VERTICES];

    // Estruturas em memória (Ponteiros para alocação dinâmica)
    int** matrizAdjacencia;   // Representação 3 (VxV)
    int** matrizIncidencia;   // Representação 4 (VxA)
    Node** listaAdjacencia;   // Representação 2 (Listas encadeadas)
    ARCO* listaArcos;         // Representação 1 (Vetor de estruturas)
} Grafo;

// --- Funções de Mapeamento (A ponte entre a lógica humana e a memória) ---

int v2i(Vertice v) { return toupper(v) - 'A'; }
Vertice i2v(int i) { return i + 'A'; }

Node* criarNo(int v_idx, int peso) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if(novo) { novo->vertice_idx = v_idx; novo->peso = peso; novo->proximo = NULL; }
    return novo;
}

/**
 * OPÇÃO 1: Inicializa o grafo com alocação dinâmica.
 */
Grafo* IniciaGrafo(int dir, int peso) {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->eDirecionado = dir;
    g->temPeso = peso;
    g->numVerticesAtivos = 0;
    g->numArestasAtual = 0;
    g->capacidadeArestas = 10; 

    g->matrizAdjacencia = (int**)calloc(MAX_VERTICES, sizeof(int*));
    g->matrizIncidencia = (int**)calloc(MAX_VERTICES, sizeof(int*));
    g->listaAdjacencia = (Node**)calloc(MAX_VERTICES, sizeof(Node*));
    g->listaArcos = (ARCO*)malloc(g->capacidadeArestas * sizeof(ARCO));

    for(int i=0; i<MAX_VERTICES; i++) {
        g->existeVertice[i] = false;
        g->matrizAdjacencia[i] = (int*)calloc(MAX_VERTICES, sizeof(int));
        g->matrizIncidencia[i] = (int*)calloc(g->capacidadeArestas, sizeof(int));
        g->listaAdjacencia[i] = NULL;
    }
    return g;
}

/**
 * OPÇÃO 2: Insere Arco com gestão de PESO em todas as estruturas.
 */
void InsereArco(Grafo* g, ARCO arco) {
    if (g->numArestasAtual >= g->capacidadeArestas) {
        g->capacidadeArestas *= 2;
        g->listaArcos = (ARCO*)realloc(g->listaArcos, g->capacidadeArestas * sizeof(ARCO));
        for(int i=0; i<MAX_VERTICES; i++) {
            g->matrizIncidencia[i] = (int*)realloc(g->matrizIncidencia[i], g->capacidadeArestas * sizeof(int));
            for(int j=g->numArestasAtual; j<g->capacidadeArestas; j++) g->matrizIncidencia[i][j] = 0;
        }
    }

    int u = v2i(arco.ponta_inicial);
    int v = v2i(arco.ponta_final);
    int idx = g->numArestasAtual;

    if (!g->existeVertice[u]) { g->existeVertice[u] = true; g->numVerticesAtivos++; }
    if (!g->existeVertice[v]) { g->existeVertice[v] = true; g->numVerticesAtivos++; }

    g->matrizAdjacencia[u][v] = arco.peso;
    if (!g->eDirecionado) g->matrizAdjacencia[v][u] = arco.peso;

    if (g->eDirecionado) {
        g->matrizIncidencia[u][idx] = arco.peso;
        g->matrizIncidencia[v][idx] = (arco.peso * -1);
    } else {
        g->matrizIncidencia[u][idx] = arco.peso;
        g->matrizIncidencia[v][idx] = arco.peso;
    }

    Node* novo = criarNo(v, arco.peso);
    novo->proximo = g->listaAdjacencia[u];
    g->listaAdjacencia[u] = novo;
    if(!g->eDirecionado) {
        Node* nInv = criarNo(u, arco.peso);
        nInv->proximo = g->listaAdjacencia[v];
        g->listaAdjacencia[v] = nInv;
    }

    g->listaArcos[idx] = arco;
    g->numArestasAtual++;
}

/**
 * OPÇÃO 4: Remover Arco (REMOÇÃO COMPLETA NAS 4 REPRESENTAÇÕES)
 */
void RemoveArco(Grafo* g, ARCO arco) {
    if(!g) return;
    int u = v2i(arco.ponta_inicial);
    int v = v2i(arco.ponta_final);
    int idxRemover = -1;

    // 1. Encontrar o índice da aresta na Edge List para sincronizar com Matriz Incidência
    for(int i = 0; i < g->numArestasAtual; i++) {
        if(g->listaArcos[i].ponta_inicial == arco.ponta_inicial && g->listaArcos[i].ponta_final == arco.ponta_final) {
            idxRemover = i;
            break;
        }
    }

    if(idxRemover == -1) { printf("Arco nao encontrado.\n"); return; }

    // 2. Limpar Matriz de Adjacência
    g->matrizAdjacencia[u][v] = 0;
    if (!g->eDirecionado) g->matrizAdjacencia[v][u] = 0;

    // 3. Limpar da Lista de Adjacência
    Node *atual = g->listaAdjacencia[u], *ant = NULL;
    while(atual) {
        if(atual->vertice_idx == v) {
            if(!ant) g->listaAdjacencia[u] = atual->proximo;
            else ant->proximo = atual->proximo;
            free(atual); break;
        }
        ant = atual; atual = atual->proximo;
    }
    if(!g->eDirecionado) { // Se não for direcionado, remove o caminho de volta
        atual = g->listaAdjacencia[v]; ant = NULL;
        while(atual) {
            if(atual->vertice_idx == u) {
                if(!ant) g->listaAdjacencia[v] = atual->proximo;
                else ant->proximo = atual->proximo;
                free(atual); break;
            }
            ant = atual; atual = atual->proximo;
        }
    }

    // 4. Reorganizar Matriz de Incidência e Edge List (Shift para a esquerda)
    for(int j = idxRemover; j < g->numArestasAtual - 1; j++) {
        g->listaArcos[j] = g->listaArcos[j+1]; // Shift na Edge List
        for(int i = 0; i < MAX_VERTICES; i++) {
            g->matrizIncidencia[i][j] = g->matrizIncidencia[i][j+1]; // Shift nas colunas da Matriz Inc
        }
    }
    
    // Limpar a última coluna que sobrou
    for(int i = 0; i < MAX_VERTICES; i++) g->matrizIncidencia[i][g->numArestasAtual-1] = 0;
    
    g->numArestasAtual--;
    printf("Arco removido com sucesso de todas as representacoes.\n");
}

/**
 * OPÇÃO 6: Visualização Filtrada e Completa
 */
void VisualizarGrafo(Grafo* g) {
    if (!g || g->numVerticesAtivos == 0) { printf("\nGrafo vazio.\n"); return; }

    printf("\n--- 1. EDGE LIST ---\n");
    for(int i=0; i<g->numArestasAtual; i++)
        printf("A%d: %c --(p:%d)--> %c\n", i, g->listaArcos[i].ponta_inicial, g->listaArcos[i].peso, g->listaArcos[i].ponta_final);

    printf("\n--- 2. LISTA ADJ ---\n");
    for(int i=0; i<MAX_VERTICES; i++) {
        if(g->existeVertice[i]) {
            printf("[%c]", i2v(i));
            Node* t = g->listaAdjacencia[i];
            while(t) { printf(" -> %c(p:%d)", i2v(t->vertice_idx), t->peso); t = t->proximo; }
            printf(" -> NULL\n");
        }
    }

    printf("\n--- 3. MATRIZ ADJ (VxV) ---\n  ");
    for(int i=0; i<MAX_VERTICES; i++) if(g->existeVertice[i]) printf("%c ", i2v(i));
    printf("\n");
    for(int i=0; i<MAX_VERTICES; i++) {
        if(g->existeVertice[i]) {
            printf("%c ", i2v(i));
            for(int j=0; j<MAX_VERTICES; j++) if(g->existeVertice[j]) printf("%d ", g->matrizAdjacencia[i][j]);
            printf("\n");
        }
    }

    printf("\n--- 4. MATRIZ INC (VxA) ---\n    ");
    for(int j=0; j<g->numArestasAtual; j++) printf("A%d ", j);
    printf("\n");
    for(int i=0; i<MAX_VERTICES; i++) {
        if(g->existeVertice[i]) {
            printf("%c: ", i2v(i));
            for(int j=0; j<g->numArestasAtual; j++) printf("%2d ", g->matrizIncidencia[i][j]);
            printf("\n");
        }
    }
}

// Funções de Busca, Cópia e Destruição (Mantidas conforme solicitado)

bool BuscaArco(Grafo* g, ARCO arco) {
    if(!g) return false;
    return (g->matrizAdjacencia[v2i(arco.ponta_inicial)][v2i(arco.ponta_final)] != 0);
}

Grafo* CopiaGrafo(Grafo* g) {
    if (!g) return NULL;
    Grafo* copia = IniciaGrafo(g->eDirecionado, g->temPeso);
    for (int i = 0; i < g->numArestasAtual; i++) InsereArco(copia, g->listaArcos[i]);
    return copia;
}

void DestroiGrafo(Grafo** g) {
    if (*g == NULL) return;
    for(int i=0; i < MAX_VERTICES; i++) {
        free((*g)->matrizAdjacencia[i]); free((*g)->matrizIncidencia[i]);
        Node* atual = (*g)->listaAdjacencia[i];
        while(atual) { Node* prox = atual->proximo; free(atual); atual = prox; }
    }
    free((*g)->matrizAdjacencia); free((*g)->matrizIncidencia);
    free((*g)->listaAdjacencia); free((*g)->listaArcos);
    free(*g); *g = NULL;
}

int main() {
    Grafo *meuGrafo = NULL, *copia = NULL;
    int opcao, dir, pesoOp;
    ARCO tempArco;

    do {
        printf("\n========== MENU GRAFOS (REMOÇAO COMPLETA) ==========\n");
        printf("1. Iniciar Novo Grafo\n2. Inserir Arco\n3. Buscar Arco\n4. Remover Arco\n");
        printf("5. Copiar Grafo\n6. Visualizar Tudo\n7. Destruir Grafo\n0. Sair\nEscolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Direcionado (1-S, 0-N): "); scanf("%d", &dir);
                printf("Com peso (1-S, 0-N): "); scanf("%d", &pesoOp);
                meuGrafo = IniciaGrafo(dir, pesoOp); break;
            case 2:
                if(!meuGrafo) break;
                printf("Origem/Destino (Letras): "); scanf(" %c %c", &tempArco.ponta_inicial, &tempArco.ponta_final);
                tempArco.peso = 1; if(meuGrafo->temPeso) { printf("Peso: "); scanf("%d", &tempArco.peso); }
                InsereArco(meuGrafo, tempArco); break;
            case 3:
                if(!meuGrafo) break;
                printf("Busca (Origem Destino): "); scanf(" %c %c", &tempArco.ponta_inicial, &tempArco.ponta_final);
                if(BuscaArco(meuGrafo, tempArco)) printf("Existe!\n"); else printf("Nao existe.\n"); break;
            case 4:
                if(!meuGrafo) break;
                printf("Remover (Origem Destino): "); scanf(" %c %c", &tempArco.ponta_inicial, &tempArco.ponta_final);
                RemoveArco(meuGrafo, tempArco); break;
            case 5:
                copia = CopiaGrafo(meuGrafo); printf("Copia realizada.\n"); break;
            case 6: VisualizarGrafo(meuGrafo); break;
            case 7: DestroiGrafo(&meuGrafo); printf("Memoria limpa.\n"); break;
        }
    } while(opcao != 0);
    return 0;
}