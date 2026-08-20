#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char nome[50];
    char nick[30];
    int point;
    int victories;
}Player;

#define playersMAX 20

Player players[playersMAX];

int totalPlayers = 0;

// Função para cadastrar aluno

void cadastrar() {
    if (totalPlayers >= playersMAX) {
        printf("Limite de players atingido!\n");
        return;
    }

    printf("\n--- Cadastro de Player ---\n");

    getchar();
    printf("Nome: ");
    fgets(players[totalPlayers].nome, 50, stdin);
    players[totalPlayers].nome[strcspn(players[totalPlayers].nome, "\n")] = '\0';
    getchar();

    printf("Nick Name: ");
    fgets(players[totalPlayers].nick, 50, stdin);
    players[totalPlayers].nick[strcspn(players[totalPlayers].nick, "\n")] = '\0';
    getchar();

    printf("Point: ");
    scanf("%d", &players[totalPlayers].point);
    getchar();

    printf("Victories: ");
    scanf("%d", &players[totalPlayers].victories);
    getchar();

    totalPlayers++;
    printf("Player cadastrado com sucesso!\n");
}

// Função para listar alunos
void mostrar() {
    if (totalPlayers ==0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    } else {
        printf("\n--- Lista de Players\n");
        for (int i = 0; i <= totalPlayers; i++) {
            printf("%d - Nome: %s | Nick Name: %s | Pontuação: %d | Vitórias: %d\n", i + 1, players[i].nome, players[i].nick, players[i].point, players[i].victories);
        }
    }
}

// Função para mostrar ranking
void ranking() {
    Player ranking;
    ranking = players[0];

    for (int i = 1; i < totalPlayers; i++) {
        if (ranking.point < players[i].point) {
            ranking = players[i];
        }

    }
    printf("\n--- Ranking\n");
    printf("%d - Nome: %s | Nick Name: %s | Pontuação: %d | Vitórias: %d\n", 1, ranking.nome, ranking.nick, ranking.point, ranking.victories);

}




int main() {
    setlocale(LC_ALL, "Portuguese");

    players[0] = {.nome = "Carolinne", .nick = "Carol", .point = 60, .victories = 6};
    players[1] = {.nome = "Arthur", .nick = "Tutu", .point = 10, .victories = 9};
    players[2] = {.nome = "Fabio", .nick = "RecebaGames", .point = 20, .victories = 10};
    players[3] = {.nome = "Angelo", .nick = "pet", .point = 50, .victories = 6};
    players[4] = {.nome = "Cristiano", .nick = "cadastro", .point = 30, .victories = 2};
    players[5] = {.nome = "João Cardoso", .nick = "Taarosh", .point = 100, .victories = 10};
    players[6] = {.nome = "Victor", .nick = "vitinho", .point = 40, .victories = 4};
    players[7] = {.nome = "Felipe", .nick = "politico", .point = 1, .victories = 1};
    players[8] = {.nome = "Mateus", .nick = "astute", .point = 0, .victories = 0};
    totalPlayers = 8;

    int opcao;
    do {
        getchar();
        printf("\n===== SISTEMA DE PLAYERS =====\n");
        printf("1 - Cadastrar player\n");
        printf("2 - Listar players\n");
        printf("3 - Ranking\n");
        printf("4 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrar();
                break;
            case 2:
                mostrar();
                break;
            case 3:
                ranking();
                break;
            case 4:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while(opcao != 4);
    return 0;
}