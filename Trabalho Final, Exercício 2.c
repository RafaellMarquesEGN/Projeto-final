#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura para representar um veículo
typedef struct Veiculo {
    char proprietario[50];
    char combustivel[10];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[10];
    struct Veiculo* proximo;
} Veiculo;

// Função para inicializar a lista encadeada
Veiculo* inicializarLista() {
    return NULL;
}

// Função para adicionar um veículo no início da lista
Veiculo* adicionarVeiculo(Veiculo* lista, const char* proprietario, const char* combustivel,
                          const char* modelo, const char* cor, const char* chassi,
                          int ano, const char* placa) {
    Veiculo* novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL) {
        printf("Erro ao alocar memória para o veículo.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(novoVeiculo->proprietario, proprietario);
    strcpy(novoVeiculo->combustivel, combustivel);
    strcpy(novoVeiculo->modelo, modelo);
    strcpy(novoVeiculo->cor, cor);
    strcpy(novoVeiculo->chassi, chassi);
    novoVeiculo->ano = ano;
    strcpy(novoVeiculo->placa, placa);
    novoVeiculo->proximo = lista;

    return novoVeiculo;
}

// a. Função que lista proprietários de carros do ano de 2010 ou posterior e movidos a diesel
void listarProprietariosAnoDiesel(Veiculo* lista) {
    printf("\nProprietários de carros do ano de 2010 ou posterior e movidos a diesel:\n");
    while (lista != NULL) {
        if (lista->ano >= 2010 && strcmp(lista->combustivel, "diesel") == 0) {
            printf("%s\n", lista->proprietario);
        }
        lista = lista->proximo;
    }
}

// b. Função que lista placas que comecam com a letra J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários
void listarPlacasJ(Veiculo* lista) {
    printf("\nPlacas que começam com a letra J e terminam com 0, 2, 4 ou 7 e seus proprietários:\n");
    while (lista != NULL) {
        int tamanhoPlaca = strlen(lista->placa);
        if (lista->placa[0] == 'J' && (lista->placa[tamanhoPlaca - 1] == '0' || lista->placa[tamanhoPlaca - 1] == '2' ||
                                       lista->placa[tamanhoPlaca - 1] == '4' || lista->placa[tamanhoPlaca - 1] == '7')) {
            printf("%s: %s\n", lista->placa, lista->proprietario);
        }
        lista = lista->proximo;
    }
}

// c. Função que lista modelo e cor dos veículos cujas placas possuem como segunda letra uma vogal
//    e cuja soma dos valores numéricos fornece um número par
void listarModeloCorPlacasVogalSomaPar(Veiculo* lista) {
    printf("\nModelo e cor dos veículos cujas placas têm segunda letra uma vogal e soma numérica é par:\n");
    while (lista != NULL) {
        char segundaLetraPlaca = lista->placa[1];
        int somaNumerica = atoi(lista->placa + 3); // Converte os caracteres numéricos para inteiro
        if ((segundaLetraPlaca == 'A' || segundaLetraPlaca == 'E' ||
             segundaLetraPlaca == 'I' || segundaLetraPlaca == 'O' || segundaLetraPlaca == 'U') &&
            somaNumerica % 2 == 0) {
            printf("Modelo: %s, Cor: %s\n", lista->modelo, lista->cor);
        }
        lista = lista->proximo;
    }
}

// d. Função que permite a troca de proprietário com o fornecimento do número do chassi
//    apenas para carros com placas que não possuam nenhum dígito igual a zero
void trocarProprietarioPorChassi(Veiculo* lista, const char* chassi, const char* novoProprietario) {
    while (lista != NULL) {
        // Verifica se o chassi corresponde e se a placa não possui dígito igual a zero
        if (strcmp(lista->chassi, chassi) == 0 && strpbrk(lista->placa, "0") == NULL) {
            strcpy(lista->proprietario, novoProprietario);
            printf("Proprietário trocado com sucesso!\n");
            return;
        }
        lista = lista->proximo;
    }
    printf("Veículo com chassi não encontrado ou placa possui dígito igual a zero.\n");
}

// Função para liberar a memória alocada pela lista encadeada
void liberarLista(Veiculo* lista) {
    Veiculo* atual = lista;
    while (atual != NULL) {
        Veiculo* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

// Função para exibir o menu
void exibirMenu() {
    printf("\n----- Menu -----\n");
    printf("1. Listar proprietarios de carros do ano de 2010 ou posterior e movidos a diesel\n");
    printf("2. Listar placas que comecam com a letra J e terminam com 0, 2, 4 ou 7\n");
    printf("3. Listar modelo e cor dos veiculos cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numericos fornece um numero par\n");
    printf("4. Trocar proprietario com fornecimento do numero do chassi\n");
    printf("5. Sair\n");
    printf("Escolha uma opcao (1-5): ");
}

int main() {
    Veiculo* listaVeiculos = inicializarLista();

    // Adicionar alguns veículos para teste
    listaVeiculos = adicionarVeiculo(listaVeiculos, "Proprietario1", "diesel", "Modelo1", "Cor1", "Chassi1", 2010, "J123ABC");
    listaVeiculos = adicionarVeiculo(listaVeiculos, "Proprietario2", "gasolina", "Modelo2", "Cor2", "Chassi2", 2012, "J456DEF");
    listaVeiculos = adicionarVeiculo(listaVeiculos, "Proprietario3", "diesel", "Modelo3", "Cor3", "Chassi3", 2015, "J789GHI");
    listaVeiculos = adicionarVeiculo(listaVeiculos, "Proprietario4", "alcool", "Modelo4", "Cor4", "Chassi4", 2019, "J012JKL");
    listaVeiculos = adicionarVeiculo(listaVeiculos, "Proprietario5", "diesel", "Modelo5", "Cor5", "Chassi5", 2011, "J345MNO");

    int escolha;
    do {
        exibirMenu();
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                listarProprietariosAnoDiesel(listaVeiculos);
                break;
            case 2:
                listarPlacasJ(listaVeiculos);
                break;
            case 3:
                listarModeloCorPlacasVogalSomaPar(listaVeiculos);
                break;
            case 4: {
                char chassi[20];
                char novoProprietario[50];

                printf("Digite o numero do chassi: ");
                scanf("%s", chassi);

                printf("Digite o novo proprietario: ");
                scanf("%s", novoProprietario);

                trocarProprietarioPorChassi(listaVeiculos, chassi, novoProprietario);
                break;
            }
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

    } while (escolha != 5);

    // Liberar a memória alocada pela lista encadeada
    liberarLista(listaVeiculos);

    return 0;
}

