// Lista encadeada Simples - todas as funções

#include <stdio.h>
#include <stdlib.h>

/* * Definição da estrutura do nó.
 * Utilizamos 'struct No' para que o ponteiro 'proximo' 
 * possa referenciar o próprio tipo de dado.
 */
struct No {
    int valor;              // Informação inteira armazenada
    struct No* proximo;     // Ponteiro para o próximo elemento da lista
};

/* * A variável 'head' (cabeça) é o ponto de entrada da lista.
 * Se head for NULL, a lista está vazia.
 */
struct No* head = NULL;

// --- Protótipos das Funções ---
void inserirNoInicio(int valor);
void inserirNoFinal(int valor);
void inserirNaPosicao(int valor, int indice);
void removerDoInicio();
void removerDoFinal();
void removerNaPosicao(int indice);
void removerPorValor(int valor);
void buscarValor(int valor);
void imprimirLista();
void limparLista();
int acharTamanhoIterativo();
int acharTamanhoRecursivo(struct No* atual);

// --- Implementação das Funções ---

void imprimirLista() {
    // Criamos um ponteiro auxiliar para não perder o início da lista
    struct No* atual = head;

    // Verificação solicitada: a lista está vazia?
    if (atual == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    printf("Elementos da lista: ");
    // Enquanto o ponteiro não chegar ao final (NULL)...
    while (atual != NULL) {
        printf("%d -> ", atual->valor);
        atual = atual->proximo; // Move o ponteiro para o próximo nó
    }
    printf("NULL\n");
}

void inserirNoInicio(int novoValor) {
    // 1. Alocar memória dinamicamente para o novo nó usando malloc
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));

    // 2. Atribuir o valor recebido ao campo 'valor' do novo nó
    novoNo->valor = novoValor;

    // 3. O 'proximo' do novo nó deve apontar para onde a 'head' aponta
    // no momento.
    // Se a lista estiver vazia, novoNo->proximo será NULL.
    // Se a lista já tiver elementos, novoNo->proximo apontará para o 
    // antigo primeiro elemento.
    novoNo->proximo = head;

    // 4. A 'head' agora é atualizada para apontar para o novo nó, 
    // tornando-o o início.
    head = novoNo;
    
    printf("Inserido o valor %d no inicio da lista.\n", novoValor);
}

void removerDoInicio() {
    // 1. Verificar se a lista está vazia
    if (head == NULL) {
        printf("Erro: A lista esta vazia. Nao ha o que remover.\n");
        return;
    }

    // 2. Criar um ponteiro temporário para guardar o nó que será 
    // removido.
    // Isso é necessário para podermos dar o 'free' nele depois.
    struct No* temp = head;

    // 3. Atualizar a head para apontar para o segundo elemento da lista.
    // Se só houver um elemento, head passará a ser NULL.
    head = head->proximo;

    // 4. Informar o valor que está sendo removido (opcional, para 
    // feedback)
    printf("Sucesso: Valor %d removido da lista.\n", temp->valor);

    // 5. Liberar a memória do nó que foi "desconectado"
    free(temp);
}

void inserirNoFinal(int novoValor) {
    // 1. Alocar memória para o novo nó
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = novoValor;
    novoNo->proximo = NULL; // Como ele será o último, o próximo dele será NULL

    // 2. Tratar o caso de lista vazia
    if (head == NULL) {
        printf("A lista estava vazia. O valor %d foi inserido como primeiro e ultimo (head).\n", novoValor);
        head = novoNo;
        return;
    }

    // 3. Se a lista não estiver vazia, precisamos encontrar o último nó
    // Usamos um ponteiro auxiliar para percorrer a lista sem perder a head
    struct No* atual = head;

    // Enquanto o "proximo" do nó atual não for NULL, ainda não chegamos no fim
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }

    // 4. Ao sair do while, 'atual' aponta para o último nó.
    // Agora, fazemos o 'proximo' desse último nó apontar para o nosso novo nó.
    atual->proximo = novoNo;

    printf("Sucesso: Valor %d inserido na ultima posicao.\n", novoValor);
}

void removerDoFinal() {
    // 1. Tratamento para lista vazia (igual à remoção no início)
    if (head == NULL) {
        printf("Erro: A lista esta vazia. Nao ha o que remover no final.\n");
        return;
    }

    // 2. Tratamento para lista com apenas UM elemento
    // Se head->proximo é NULL, o único elemento é a própria head
    if (head->proximo == NULL) {
        printf("Sucesso: Valor %d (unico elemento) removido.\n", head->valor);
        free(head);   // Libera o único nó
        head = NULL;  // Reseta a head para vazia
        return;
    }

    // 3. Caso a lista tenha 2 ou mais elementos:
    // Precisamos de um ponteiro para percorrer a lista 
    // e parar no PENÚLTIMO nó.
    struct No* atual = head;
    
    // Enquanto o "proximo do proximo" não for NULL, ainda não chegamos no penúltimo
    while (atual->proximo->proximo != NULL) {
        atual = atual->proximo;
    }

    // 4. Ao sair do loop, 'atual' é o PENÚLTIMO nó.
    // 'atual->proximo' é o ÚLTIMO nó (o que queremos remover).
    struct No* ultimo = atual->proximo;
    
    printf("Sucesso: Valor %d removido do final.\n", ultimo->valor);

    // 5. Liberar a memória do último nó
    free(ultimo);

    // 6. O penúltimo agora se torna o último, apontando para NULL
    atual->proximo = NULL;
}

void inserirNaPosicao(int novoValor, int indice) {
    // 1. Alocação do novo nó
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    novoNo->valor = novoValor;

    // 2. CASO A: Lista Vazia
    if (head == NULL) {
        printf("Lista vazia! Inserindo o valor %d no inicio (posicao 0).\n", novoValor);
        novoNo->proximo = NULL;
        head = novoNo;
        return;
    }

    // 3. CASO B: Inserção no índice 0 (mesmo com lista não vazia)
    if (indice <= 0) {
        novoNo->proximo = head;
        head = novoNo;
        printf("Inserido %d na cabeca (indice 0).\n", novoValor);
        return;
    }

    // 4. CASO C: Percorrer para encontrar a posição ou o fim da lista
    struct No* atual = head;
    int i = 0;

    // Queremos parar no nó ANTERIOR à posição desejada (indice - 1)
    // OU parar no último nó disponível
    while (i < indice - 1 && atual->proximo != NULL) {
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

void removerNaPosicao(int indice) {
    // 1. Tratamento para lista vazia
    if (head == NULL) {
        printf("Erro: A lista esta vazia. Nao ha o que remover.\n");
        return;
    }

    // 2. Caso especial: Remoção do índice 0 (head)
    if (indice <= 0) {
        struct No* temp = head;
        head = head->proximo;
        printf("Sucesso: Indice 0 removido (Valor: %d).\n", temp->valor);
        free(temp);
        return;
    }

    // 3. Percorrer a lista para encontrar o nó ANTERIOR ao que será removido
    struct No* atual = head;
    int i = 0;

    // Precisamos parar no nó (indice - 1) OU no penúltimo nó
    while (i < indice - 1 && atual->proximo != NULL && atual->proximo->proximo != NULL) {
        atual = atual->proximo;
        i++;
    }

    // 4. Verificação: O índice solicitado existe?
    // Se paramos porque a lista acabou antes de chegar no índice
    if (i < indice - 1 || atual->proximo == NULL) {
        printf("Aviso: Indice %d inexistente. Chamando remocao do final...\n", indice);
        removerDoFinal(); // Reaproveita a lógica de remover o último
    } 
    else {
        // 5. Remoção padrão no meio da lista
        // 'atual' é o nó anterior ao que queremos remover
        struct No* alvo = atual->proximo; // Este é o nó que vai sair
        
        // O anterior aponta para o próximo do alvo (pula o alvo)
        atual->proximo = alvo->proximo;
        
        printf("Sucesso: Valor %d removido da posicao %d.\n", alvo->valor, indice);
        
        // Libera a memória do nó excluído
        free(alvo);
    }
}

void buscarValor(int valorProcurado) {
    // 1. Verificar se a lista está vazia antes de começar
    if (head == NULL) {
        printf("Busca: A lista esta vazia. O valor %d nao existe.\n", valorProcurado);
        return;
    }

    struct No* atual = head;
    int indice = 0;
    int encontrado = 0; // Variável "flag" para controle

    // 2. Percorrer a lista
    while (atual != NULL) {
        // Se o valor do nó atual for o que estamos buscando
        if (atual->valor == valorProcurado) {
            printf("Sucesso: O valor %d foi encontrado na posicao %d.\n", valorProcurado, indice);
            encontrado = 1;
            break; // Para a busca assim que encontrar a primeira ocorrência
        }
        
        // Move para o próximo nó e incrementa o contador de índice
        atual = atual->proximo;
        indice++;
    }

    // 3. Se percorreu tudo e não encontrou nada
    if (!encontrado) {
        printf("Busca: O valor %d nao foi encontrado na lista.\n", valorProcurado);
    }
}

void removerPorValor(int valorParaRemover) {
    // 1. Verificar se a lista está vazia
    if (head == NULL) {
        printf("Erro: Lista vazia. Nao e possivel remover o valor %d.\n", valorParaRemover);
        return;
    }

    // 2. Caso especial: O valor está logo na cabeça (head)
    if (head->valor == valorParaRemover) {
        struct No* temp = head;
        head = head->proximo;
        printf("Sucesso: Valor %d encontrado na head e removido.\n", valorParaRemover);
        free(temp);
        return;
    }

    // 3. Busca pelo valor nas outras posições
    // Precisamos manter o rastro do nó ANTERIOR para poder religar a lista
    struct No* atual = head;
    struct No* anterior = NULL;

    while (atual != NULL && atual->valor != valorParaRemover) {
        anterior = atual;   // Guarda o atual como anterior
        atual = atual->proximo; // Avança para o próximo
    }

    // 4. Se o loop terminou e 'atual' é NULL, o valor não foi encontrado
    if (atual == NULL) {
        printf("Aviso: O valor %d nao foi encontrado para remocao.\n", valorParaRemover);
        return;
    }

    // 5. Se chegou aqui, o valor foi encontrado!
    // O 'anterior' agora pula o 'atual' e aponta para o próximo dele
    anterior->proximo = atual->proximo;

    printf("Sucesso: Valor %d encontrado e removido da lista.\n", valorParaRemover);
    free(atual); // Libera a memória do nó encontrado
}

void limparLista() {
    // 1. Verificação inicial: se já está vazia, avisa o usuário.
    if (head == NULL) {
        printf("A lista ja esta vazia.\n");
        return;
    }

    printf("Iniciando a limpeza da lista...\n");

    // 2. Enquanto a cabeça da lista não for NULL, significa que ainda há nós.
    while (head != NULL) {
        // Chamamos a função que remove o último elemento
        removerDoFinal();
    }

    printf("Sucesso: Toda a memoria foi liberada e a lista esta limpa.\n");
}

int acharTamanhoIterativo() {
    int contador = 0;           // 1. Inicializa o contador em zero
    struct No* atual = head;    // 2. Começa a varredura pela cabeça da lista

    // 3. Enquanto o ponteiro não chegar ao fim (NULL)
    while (atual != NULL) {
        contador++;             // Incrementa o contador para o nó atual
        atual = atual->proximo; // Salta para o próximo nó da corrente
    }

    // 4. Retorna o total acumulado
    return contador;
}

int acharTamanhoRecursivo(struct No* atual) {
    // Caso Base: Se o ponteiro for NULL, chegamos ao fim e o tamanho é 0.
    if (atual == NULL) {
        return 0;
    }

    // Passo Recursivo: 1 (este nó) + o tamanho do próximo nó em diante.
    return 1 + acharTamanhoRecursivo(atual->proximo);
}

// --- Menu Principal ---

int main() {
    int opcao, valor, pos;

    do {
        system("clear"); // Limpa a tela no Linux
        printf("--- MENU LISTA ENCADEADA ---\n");
        imprimirLista();
        printf("\nTamanho (Iterativo): %d", acharTamanhoIterativo());
        printf("\nTamanho (Recursivo): %d", acharTamanhoRecursivo(head));
        printf("\n\n1. Inserir no Inicio\n2. Inserir no Final\n3. Inserir por Posicao\n");
        printf("4. Remover do Inicio\n5. Remover do Final\n6. Remover por Posicao\n");
        printf("7. Buscar Valor\n0. Sair e Limpar\n");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                printf("Valor: "); scanf("%d", &valor);
                inserirNoInicio(valor);
                break;
            case 2:
                printf("Valor: "); scanf("%d", &valor);
                inserirNoFinal(valor);
                break;
            case 3:
                printf("Valor: "); scanf("%d", &valor);
                printf("Posicao: "); scanf("%d", &pos);
                inserirNaPosicao(valor, pos);
                break;
            case 4:
                removerDoInicio();
                break;
            case 5:
                removerDoFinal();
                break;
            case 6:
                printf("Posicao: "); scanf("%d", &pos);
                removerNaPosicao(pos);
                break;
            case 7:
                printf("Valor para busca: "); scanf("%d", &valor);
                buscarValor(valor);
                break;
            case 0:
                limparLista();
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar(); getchar(); // Pausa para leitura antes de limpar a tela
        }

    } while (opcao != 0);

    return 0;
}