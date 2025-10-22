#include <stdio.h>
#include <string.h>

// struct que representa um território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;     
};

// Entrada de dados
int main() {
    struct Territorio territorios[5];
    int i;

    printf("=== CADASTRO DE TERRITÓRIOS ===\n\n");

    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }
    
    // Exibição dos dados cadastrados
    printf("\n=== LISTA DE TERRITÓRIOS CADASTRADOS ===\n");
    for (i = 0; i < 5; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    printf("\nCadastro finalizado com sucesso!\n");

    return 0;
}
