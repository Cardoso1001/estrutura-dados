#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define Max 20

enum tipo_escolar {Diretor = 1, Secretaria, Coordenador, Professor, Estagiario, Aluno} ;

typedef struct {
    int id;
    char nome[20];
    enum tipo_escolar tipoUser;
}User;


void printUser(User user) {
        printf("ID: %d", user.id );
        printf(" | Tipo: ");
        switch (user.tipoUser) {
            case Diretor:
                printf("Diretor");
                break;
            case Secretaria:
                printf("Secretaria");
                break;
            case Coordenador:
                printf("Coordenador");
                break;
            case Professor:
                printf("Professor");
                break;
            case Estagiario:
                printf("Estagiario");
                break;
            case Aluno:
                printf("Aluno");
                break;
        }
        printf(" | Nome: %s", user.nome);
}
User addUser(int contUser, const char* nome, int tipo) {
    User user;

    user.id = contUser;
    strcpy(user.nome, nome);
    user.tipoUser = tipo;

    return user;
}


int main() {
    setlocale(LC_ALL, "");
    User usuarios[Max];
    int contUser = 0;
    int opcao;
    do {printf("\nMenu de opções:\n");
    printf("1 - Cadastrar usuário.\n");
    printf("2 - Visualizar usuarios.\n");
    printf("3 - Sair.\n");
    scanf("%d", &opcao);
        switch (opcao) {
            case 1: {
                printf("\nCadastrando o %d usuario.\n", contUser+1);
                getchar();
                printf("\nNome: ");
                char nome[20];
                fgets(nome, 20, stdin);
                int tipo;
                do {
                    printf("\n1 - Diretor.");
                    printf("\n2 - Secretaria.");
                    printf("\n3 - Coordenador.");
                    printf("\n4 - Professor.");
                    printf("\n5 - Estagiário.");
                    printf("\n6 - Aluno.");
                    printf("\nEscolha: ");
                    scanf("%d", &tipo);
                    if (tipo < 1 || tipo > 6) {
                        printf("\nEscreva um número valido.\n");
                    }
                } while (tipo < 1 || tipo > 6);
                usuarios[contUser++] = addUser(contUser, nome, tipo);
                printUser(usuarios[contUser-1]);
                break;
            }
            case 2: {
                contUser == 0 ? printf("Não há usuários cadastrados!") : printf("Usuários:\n");
                for (int i = 0; i < contUser; i++) {
                    printUser(usuarios[i]);
                }
                break;
            }
            case 3: {
                printf("Saindo do programa...\n");
                break;
            }
                default:
                printf("Opção invalida, tente novamente!\n");
        }
    } while (opcao != 3);
    return 0;
}