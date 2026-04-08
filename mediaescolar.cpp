 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #define MAX 100

 typedef struct {
 char nome[50];
 float nota;
 } Aluno;

 Aluno turma[MAX];
 int totalAlunos = 0;

 // Função para cadastrar aluno
 void cadastrar() {
 if (totalAlunos >= MAX) {
 printf("Limite de alunos atingido!\n");
 return;
 }

 printf("\n--- Cadastro de Aluno ---\n");

 printf("Nome: ");
 fgets(turma[totalAlunos].nome, 50, stdin);
 //fgets() lê texto (string) do teclado ou de arquivo e é mais segura que

scanf("%s");

 turma[totalAlunos].nome[strcspn(turma[totalAlunos].nome, "\n")] = '\0';

 printf("Nota: ");
 scanf("%f", &turma[totalAlunos].nota);
 getchar(); // limpa buffer

 totalAlunos++;
 printf("Aluno cadastrado com sucesso!\n");
 }

 // Função para listar alunos
 void listar() {
 if (totalAlunos == 0) {
 printf("\nNenhum aluno cadastrado.\n");
 return;
 }

 printf("\n--- Lista de Alunos ---\n");

 for (int i = 0; i < totalAlunos; i++) {
 printf("%d - %s | Nota: %.2f", i + 1, turma[i].nome, turma[i].nota);

 if (turma[i].nota >= 6)
 printf(" | Aprovado\n");
 else
 printf(" | Reprovado\n");
 }
 }

 // Função para calcular média
 void mediaTurma() {
 if (totalAlunos == 0) {
 printf("\nNenhum aluno cadastrado.\n");
 return;
 }

 float soma = 0;

 for (int i = 0; i < totalAlunos; i++) {
 soma += turma[i].nota;
 }

 printf("\nMédia da turma: %.2f\n", soma / totalAlunos);
 }

 int main() {

 int opcao;

 do {
 printf("\n===== SISTEMA DE ALUNOS =====\n");
 printf("1 - Cadastrar aluno\n");
 printf("2 - Listar alunos\n");
 printf("3 - Média da turma\n");
 printf("4 - Sair\n");
 printf("Escolha uma opção: ");
 scanf("%d", &opcao);
 getchar(); // limpa buffer

 switch(opcao) {
 case 1:
 cadastrar();
 break;
 case 2:
 listar();
 break;
 case 3:
 mediaTurma();
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