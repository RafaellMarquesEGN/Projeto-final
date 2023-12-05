#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defini��o da estrutura para representar um ve�culo
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

// Fun��o para inicializar a lista encadeada
Veiculo* inicializarLista() {
    return NULL;
}

// Fun��o para adicionar um ve�culo no in�cio da lista
Veiculo* adicionarVeiculo(Veiculo* lista, const char* proprietario, const char* combustivel,
                          const char* modelo, const char* cor, const char* chassi,
                          int ano, const char* placa) {
    Veiculo* novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
    if (novoVeiculo == NULL) {
        printf("Erro ao alocar mem�ria para o ve�culo.\n");
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

// a. Fun��o que lista propriet�rios de carros do ano de 2010 ou posterior e movidos a diesel
void listarProprietariosAnoDiesel(Veiculo* lista) {
    printf("\nPropriet�rios de carros do ano de 2010 ou posterior e movidos a diesel:\n");
    while (lista != NULL) {
        if (lista->ano >= 2010 && strcmp(lista->combustivel, "diesel") == 0) {
            printf("%s\n", lista->proprietario);
        }
        lista = lista->proximo;
    }
}

// b. Fun��o que lista placas que comecam com a letra J e terminam com 0, 2, 4 ou 7 e seus respectivos propriet�rios
void listarPlacasJ(Veiculo* lista) {
    printf("\nPlacas que come�am com a letra J e terminam com 0, 2, 4 ou 7 e seus propriet�rios:\n");
    while (lista != NULL) {
        int tamanhoPlaca = strlen(lista->placa);
        if (lista->placa[0] == 'J' && (lista->placa[tamanhoPlaca - 1] == '0' || lista->placa[tamanhoPlaca - 1] == '2' ||
                                       lista->placa[tamanhoPlaca - 1] == '4' || lista->placa[tamanhoPlaca - 1] == '7')) {
            printf("%s: %s\n", lista->placa, lista->proprietario);
        }
        lista = lista->proximo;
    }
}

// c. Fun��o que lista modelo e cor dos ve�culos cujas placas possuem como segunda letra uma vogal
//    e cuja soma dos valores num�ricos fornece um n�mero par
void listarModeloCorPlacasVogalSomaPar(Veiculo* lista) {
    printf("\nModelo e cor dos ve�culos cujas placas t�m segunda letra uma vogal e soma num�rica � par:\n");
    while (lista != NULL) {
        char segundaLetraPlaca = lista->placa[1];
        int somaNumerica = atoi(lista->placa + 3); // Converte os caracteres num�ricos para inteiro
        if ((segundaLetraPlaca == 'A' || segundaLetraPlaca == 'E' ||
             segundaLetraPlaca == 'I' || segundaLetraPlaca == 'O' || segundaLetraPlaca == 'U') &&
            somaNumerica % 2 == 0) {
            printf("Modelo: %s, Cor: %s\n", lista->modelo, lista->cor);
        }
        lista = lista->proximo;
    }
}

// d. Fun��o que permite a troca de propriet�rio com o fornecimento do n�mero do chassi
//    apenas para carros com placas que n�o possuam nenhum d�gito igual a zero
void trocarProprietarioPorChassi(Veiculo* lista, const char* chassi, const char* novoProprietario) {
    while (lista != NULL) {
        // Verifica se o chassi corresponde e se a placa n�o possui d�gito igual a zero
        if (strcmp(lista->chassi, chassi) == 0 && strpbrk(lista->placa, "0") == NULL) {
            strcpy(lista->proprietario, novoProprietario);
            printf("Propriet�rio trocado com sucesso!\n");
            return;
        }
        lista = lista->proximo;
    }
    printf("Ve�culo com chassi n�o encontrado ou placa possui d�gito igual a zero.\n");
}

// Fun��o para liberar a mem�ria alocada pela lista encadeada
void liberarLista(Veiculo* lista) {
    Veiculo* atual = lista;
    while (atual != NULL) {
        Veiculo* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
}

// Fun��o para exibir o menu
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

    // Adicionar alguns ve�culos para teste
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

    // Liberar a mem�ria alocada pela lista encadeada
    liberarLista(listaVeiculos);

    return 0;
}

