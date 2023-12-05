#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura para armazenar informações do produto
typedef struct {
    int codigo;
    char descricao[50];
    int quantidade;
    float valor;
} Produto;

// Estrutura para armazenar um nó da lista de estoque
typedef struct Nodo {
    Produto produto;
    struct Nodo* proximo;
} Nodo;

// Estrutura para representar a lista de estoque
typedef struct {
    Nodo* inicio;
} ListaEstoque;

// Função para inicializar a lista de estoque
ListaEstoque inicializarLista() {
    ListaEstoque lista;
    lista.inicio = NULL;
    return lista;
}

// Função para adicionar um novo produto à lista de estoque
void adicionarProduto(ListaEstoque* lista) {
    Nodo* novoNodo = (Nodo*)malloc(sizeof(Nodo));
    printf("Digite o codigo do produto: ");
    scanf("%d", &novoNodo->produto.codigo);
    printf("Digite a descricao do produto: ");
    scanf("%s", novoNodo->produto.descricao);
    printf("Digite a quantidade do produto: ");
    scanf("%d", &novoNodo->produto.quantidade);
    printf("Digite o valor do produto: ");
    scanf("%f", &novoNodo->produto.valor);

    novoNodo->proximo = lista->inicio;
    lista->inicio = novoNodo;

    printf("Produto adicionado com sucesso!\n");
}

// Função para imprimir um relatório de produtos
void imprimirRelatorio(ListaEstoque lista) {
    Nodo* atual = lista.inicio;

    while (atual != NULL) {
        printf("Codigo: %d, Descricao: %s, Quantidade: %d, Valor: %.2f\n",
               atual->produto.codigo, atual->produto.descricao,
               atual->produto.quantidade, atual->produto.valor);

        atual = atual->proximo;
    }
}

// Função para pesquisar um produto pelo código
void pesquisarProduto(ListaEstoque lista) {
    int codigo;
    printf("Digite o codigo do produto: ");
    scanf("%d", &codigo);

    Nodo* atual = lista.inicio;
    while (atual != NULL) {
        if (atual->produto.codigo == codigo) {
            printf("Produto encontrado:\n");
            printf("Codigo: %d, Descricao: %s, Quantidade: %d, Valor: %.2f\n",
                   atual->produto.codigo, atual->produto.descricao,
                   atual->produto.quantidade, atual->produto.valor);
            return;
        }
        atual = atual->proximo;
    }

    printf("Produto nao encontrado.\n");
}

// Função para remover um produto do estoque
void removerProduto(ListaEstoque* lista) {
    int codigo;
    printf("Digite o codigo do produto a ser removido: ");
    scanf("%d", &codigo);

    Nodo* atual = lista->inicio;
    Nodo* anterior = NULL;

    while (atual != NULL) {
        if (atual->produto.codigo == codigo) {
            if (anterior == NULL) {
                // Remover o primeiro elemento da lista
                lista->inicio = atual->proximo;
            } else {
                // Remover um elemento no meio ou no final da lista
                anterior->proximo = atual->proximo;
            }

            free(atual);
            printf("Produto removido com sucesso!\n");
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("Produto nao encontrado.\n");
}

// Função para liberar a memória alocada para a lista
void liberarLista(ListaEstoque* lista) {
    Nodo* atual = lista->inicio;
    Nodo* proximo;

    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    lista->inicio = NULL;
}

int main() {
    ListaEstoque lista = inicializarLista();
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar produto\n");
        printf("2. Imprimir relatorio\n");
        printf("3. Pesquisar produto\n");
        printf("4. Remover produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto(&lista);
                break;
            case 2:
                imprimirRelatorio(lista);
                break;
            case 3:
                pesquisarProduto(lista);
                break;
            case 4:
                removerProduto(&lista);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    liberarLista(&lista);

    return 0;
}

