#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define Vertice char
#define MAX_VERTICES 26

typedef struct {
    Vertice ponta_inicial;
    Vertice ponta_final;
    int peso;
} ARCO;

typedef struct {
    int numVertices;
    int eDirecionado;
    int temPeso;
    int matriz[MAX_VERTICES][MAX_VERTICES];
    bool existeVertice[MAX_VERTICES];
} Grafo;

// --- Funções de Suporte (ID e Mapeamento) ---

int v2i(Vertice v) {
    return toupper(v) - 'A';
}

Vertice i2v(int i) {
    return i + 'A';
}

// --- Implementação das Operações Solicitadas ---

Grafo* IniciaGrafo(int dir, int peso) {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->eDirecionado = dir;
    g->temPeso = peso;
    g->numVertices = 0;
    for(int i=0; i<MAX_VERTICES; i++) {
        g->existeVertice[i] = false;
        for(int j=0; j<MAX_VERTICES; j++) g->matriz[i][j] = 0;
    }
    return g;
}

void InsereArco(Grafo* g, ARCO arco) {
    int u = v2i(arco.ponta_inicial);
    int v = v2i(arco.ponta_final);
    if (!g->existeVertice[u]) { g->existeVertice[u] = true; g->numVertices++; }
    if (!g->existeVertice[v]) { g->existeVertice[v] = true; g->numVertices++; }
    
    g->matriz[u][v] = arco.peso;
    if (!g->eDirecionado) g->matriz[v][u] = arco.peso;
}

bool BuscaArco(Grafo* g, ARCO arco) {
    int u = v2i(arco.ponta_inicial);
    int v = v2i(arco.ponta_final);
    return (g->matriz[u][v] != 0);
}

void RemoveArco(Grafo* g, ARCO arco) {
    int u = v2i(arco.ponta_inicial);
    int v = v2i(arco.ponta_final);
    g->matriz[u][v] = 0;
    if (!g->eDirecionado) g->matriz[v][u] = 0;
}

Grafo* CopiaGrafo(Grafo* g) { //Incompleto
    if (!g) return NULL;
    Grafo* copia = (Grafo*)malloc(sizeof(Grafo));
    *copia = *g;
    return copia;
}

void DestroiGrafo(Grafo** g) {
    if (*g) {
        free(*g);
        *g = NULL;
    }
}

void ExibirGrafo(Grafo* g) {
    if (!g || g->numVertices == 0) {
        printf("\n[!] Grafo vazio ou nao inicializado.\n");
        return;
    }
    printf("\n--- Estado Atual do Grafo ---\n  ");
    for(int i=0; i<MAX_VERTICES; i++) if(g->existeVertice[i]) printf("%c ", i2v(i));
    printf("\n");
    for(int i=0; i<MAX_VERTICES; i++) {
        if(g->existeVertice[i]) {
            printf("%c ", i2v(i));
            for(int j=0; j<MAX_VERTICES; j++) {
                if(g->existeVertice[j]) printf("%d ", g->matriz[i][j]);
            }
            printf("\n");
        }
    }
}

// --- Menu e Main ---

int main() {
    Grafo *meuGrafo = NULL, *copia = NULL;
    int opcao, dir, pesoOp;
    ARCO tempArco;

    do {
        printf("\n========== MENU GRAFOS ==========\n");
        printf("1. Iniciar Novo Grafo\n");
        printf("2. Inserir Arco (Aresta)\n");
        printf("3. Buscar Arco\n");
        printf("4. Remover Arco\n");
        printf("5. Copiar Grafo\n");
        printf("6. Visualizar Grafo\n");
        printf("7. Destruir Grafo\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                if(meuGrafo) DestroiGrafo(&meuGrafo);
                printf("Direcionado? (1-Sim, 0-Nao): "); scanf("%d", &dir);
                printf("Com peso? (1-Sim, 0-Nao): "); scanf("%d", &pesoOp);
                meuGrafo = IniciaGrafo(dir, pesoOp);
                printf("Grafo inicializado!\n");
                break;

            case 2:
                if(!meuGrafo) { printf("Inicie o grafo primeiro!\n"); break; }
                printf("Origem (Letra): "); scanf(" %c", &tempArco.ponta_inicial);
                printf("Destino (Letra): "); scanf(" %c", &tempArco.ponta_final);
                tempArco.peso = 1;
                if(meuGrafo->temPeso) {
                    printf("Peso: "); scanf("%d", &tempArco.peso);
                }
                InsereArco(meuGrafo, tempArco);
                break;

            case 3:
                if(!meuGrafo) break;
                printf("Buscar - Origem: "); scanf(" %c", &tempArco.ponta_inicial);
                printf("Buscar - Destino: "); scanf(" %c", &tempArco.ponta_final);
                if(BuscaArco(meuGrafo, tempArco)) printf("Arco existe!\n");
                else printf("Arco nao encontrado.\n");
                break;

            case 4:
                if(!meuGrafo) break;
                printf("Remover - Origem: "); scanf(" %c", &tempArco.ponta_inicial);
                printf("Remover - Destino: "); scanf(" %c", &tempArco.ponta_final);
                RemoveArco(meuGrafo, tempArco);
                break;

            case 5:
                copia = CopiaGrafo(meuGrafo);
                printf("Copia efetuada na memoria.\n");
                break;

            case 6:
                ExibirGrafo(meuGrafo);
                break;

            case 7:
                DestroiGrafo(&meuGrafo);
                printf("Grafo removido da memoria.\n");
                break;

            case 0:
                DestroiGrafo(&meuGrafo);
                if(copia) DestroiGrafo(&copia);
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}