#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define Vertice char
#define MAX_VERTICES 26
#define MAX_ARESTAS 100 // Definindo um limite para a lista de arestas

typedef struct {
    Vertice ponta_inicial;
    Vertice ponta_final;
    int peso;
} ARCO;

typedef struct {
    int numVertices;
    int numArestas;    // Contador de arestas na lista
    int eDirecionado;
    int temPeso;
    ARCO listaArestas[MAX_ARESTAS]; // A estrutura agora é uma lista (array) de arcos
    bool existeVertice[MAX_VERTICES];
} Grafo;

// --- Funções de Suporte ---

int v2i(Vertice v) {
    return toupper(v) - 'A';
}

Vertice i2v(int i) {
    return i + 'A';
}

// --- Implementação com Edge List ---

Grafo* IniciaGrafo(int dir, int peso) {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->eDirecionado = dir;
    g->temPeso = peso;
    g->numVertices = 0;
    g->numArestas = 0;
    for(int i=0; i<MAX_VERTICES; i++) {
        g->existeVertice[i] = false;
    }
    return g;
}

void InsereArco(Grafo* g, ARCO arco) {
    if (g->numArestas >= MAX_ARESTAS) {
        printf("[!] Erro: Capacidade maxima de arestas atingida.\n");
        return;
    }

    int u = v2i(arco.ponta_inicial);
    int v = v2i(arco.ponta_final);

    // Gerencia contagem de vértices únicos
    if (!g->existeVertice[u]) { g->existeVertice[u] = true; g->numVertices++; }
    if (!g->existeVertice[v]) { g->existeVertice[v] = true; g->numVertices++; }

    // Adiciona o arco na lista
    g->listaArestas[g->numArestas] = arco;
    g->numArestas++;
}

bool BuscaArco(Grafo* g, ARCO arco) {
    for (int i = 0; i < g->numArestas; i++) {
        // Verifica conexão direta
        if (g->listaArestas[i].ponta_inicial == arco.ponta_inicial && 
            g->listaArestas[i].ponta_final == arco.ponta_final) {
            return true;
        }
        // Se não for direcionado, verifica a volta
        if (!g->eDirecionado) {
            if (g->listaArestas[i].ponta_inicial == arco.ponta_final && 
                g->listaArestas[i].ponta_final == arco.ponta_inicial) {
                return true;
            }
        }
    }
    return false;
}

void RemoveArco(Grafo* g, ARCO arco) {
    for (int i = 0; i < g->numArestas; i++) {
        bool match = false;
        
        if (g->listaArestas[i].ponta_inicial == arco.ponta_inicial && 
            g->listaArestas[i].ponta_final == arco.ponta_final) {
            match = true;
        } else if (!g->eDirecionado && 
                   g->listaArestas[i].ponta_inicial == arco.ponta_final && 
                   g->listaArestas[i].ponta_final == arco.ponta_inicial) {
            match = true;
        }

        if (match) {
            // Move a última aresta para a posição da removida (otimização de array)
            g->listaArestas[i] = g->listaArestas[g->numArestas - 1];
            g->numArestas--;
            printf("Arco removido.\n");
            return;
        }
    }
    printf("Arco nao encontrado para remocao.\n");
}

Grafo* CopiaGrafo(Grafo* g) {
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
    printf("\n--- Edge List (Lista de Arestas) ---\n");
    printf("Vertices ativos: ");
    for(int i=0; i<MAX_VERTICES; i++) if(g->existeVertice[i]) printf("%c ", i2v(i));
    
    printf("\nArestas (%d):\n", g->numArestas);
    for(int i = 0; i < g->numArestas; i++) {
        printf("[%d] %c -> %c", i+1, g->listaArestas[i].ponta_inicial, g->listaArestas[i].ponta_final);
        if(g->temPeso) printf(" (Peso: %d)", g->listaArestas[i].peso);
        printf("\n");
    }
}

// --- Menu e Main permanecem iguais ---
int main() {
    Grafo *meuGrafo = NULL, *copia = NULL;
    int opcao, dir, pesoOp;
    ARCO tempArco;

    do {
        printf("\n========== MENU GRAFOS (EDGE LIST) ==========\n");
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