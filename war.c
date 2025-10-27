#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ------------------- STRUCT -------------------
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ------------------- FUNÇÕES -------------------

// Cadastra os territórios
void cadastrarTerritorios(Territorio* mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);
        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe todos os territórios
void exibirTerritorios(Territorio* mapa, int qtd) {
    printf("\n=== Territórios cadastrados ===\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d) %-20s | Cor: %-10s | Tropas: %d\n", i + 1,
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Função que simula o ataque entre os territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("O território defensor pertence ao mesmo exército! Ataque inválido.");
        return;
    }

    if (atacante->tropas < 2) {
        printf("O atacante precisa de pelo menos 2 tropas para atacar!");
        return;
    }

    // Rolagem dos dados
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf(" Rolagem de dados:");
    printf("%s (atacante): %d\n", atacante->nome, dadoAtacante);
    printf("%s (defensor): %d\n", defensor->nome, dadoDefensor);

    // Resultado da batalha
    if (dadoAtacante > dadoDefensor) {
        printf("\n %s venceu o ataque contra %s!\n", atacante->nome, defensor->nome);

        // O defensor muda de dono e perde metade das tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

        // O atacante perde uma tropa após a batalha
        atacante->tropas -= 1;

        printf("\n %s agora pertence ao exército %s!\n", defensor->nome, defensor->cor);
    } else if (dadoAtacante < dadoDefensor) {
        printf("\n %s defendeu com sucesso!\n", defensor->nome);
        atacante->tropas -= 1;
    } else {
        printf("\n Empate! Nenhum território muda de controle.\n");
    }

    // Exibe situação depois do combate
    printf("\n Situação depois do combate:\n");
    printf("Atacante: %s | Cor: %s | Tropas: %d\n",
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s | Cor: %s | Tropas: %d\n",
           defensor->nome, defensor->cor, defensor->tropas);
}

// Libera a memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\n🧹 Memória liberada com sucesso!\n");
}

//  - FUNÇÃO PRINCIPAL -
int main() {
    srand(time(NULL));
    int qtd, opc, atacante, defensor;
    Territorio* mapa = NULL;

    printf("==== JOGO WAR - FASE DE ATAQUE ====\n\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação dinâmica de memória
    mapa = (Territorio*) calloc(qtd, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    do {
        printf("\n=== MENU ===\n");
        printf("1. Exibir territórios\n");
        printf("2. Atacar território\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        switch (opc) {
            case 1:
                exibirTerritorios(mapa, qtd);
                break;

            case 2:
                exibirTerritorios(mapa, qtd);
                printf("\nEscolha o número do território atacante: ");
                scanf("%d", &atacante);
                printf("Escolha o número do território defensor: ");
                scanf("%d", &defensor);

                // Valida escolha
                if (atacante < 1 || atacante > qtd || defensor < 1 || defensor > qtd) {
                    printf("\n Escolha inválida!\n");
                } else {
                    atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
                }
                break;

            case 0:
                liberarMemoria(mapa);
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opc != 0);

    return 0;
}
