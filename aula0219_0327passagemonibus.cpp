// Exemplos de inserção de dados em uma struct :
// #define Pessoa p3 = {.idade = 22, .nome = "Ana"};
// Pessoa p1 = {"Joao Silva", {15, 10, 1990}};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
//Estruturando struct :
/*
Onibus:
- número do ônibus
- capacidade
- placa
- modelo
- ano de fabricação

Passagem:
- número da passagem
- nome do passageiro - Passageiro
- preço - Viagem
- assento
- método de pagamento

Viagem:
- data da viagem(saída) - Data
- horário da viagem(saída) - Horário
- origem - CEP
- data prevista(chegada) - Data
- horário previsto(chegada) - Horário
- destino - CEP
- assentos livres - Onibus
- num dos assentos
- preço

Passageiro:
- nome
- CPF
- telefone
- data de nascimento - Data

CEP: 
- número do CEP
- rua
- bairro
- cidade
- estado
- país

Horário:
- segundos
- minutos
- horas

Data:
- dia
- mês
- ano

*/

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define foreach(item, array, size) \
for (int _i = 0; _i < size && ((item) = (array)[_i], 1); _i++)
//Precisava muito de um foreach

#define MAX_Capacidade 60
enum metodo_Pag {Dinheiro = 1, Boleto, Pix, Debito, Credito, Vauncher, Cheque};
typedef struct {
    int horas;
    int minutos;
    int segundos;
} Horario;
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;
typedef struct {
    char nome[50];
    char CPF[15];
    char telefone[15];
    Data dataNascimento;
} Passageiro;
typedef struct {
    int numOnibus;
    int capacidade;
    char placa[10];
    char modelo[30];
    Data anoFabricacao;
} Onibus;
typedef struct {
    int numCEP;
    char rua[100];
    char bairro[50];
    char cidade[50];
    char estado[30];
    char pais[30];
} CEP;
typedef struct {
    int numViagem;
    Data dataSaida;
    Horario horarioSaida;
    CEP origem;
    Data dataPrevistaChegada;
    Horario horarioPrevistoChegada;
    CEP destino;
    Onibus onibus;
    int numAss[MAX_Capacidade]; // 0 livre e 1 ocupado
    int assLivres;
    float preco;
} Viagem;
typedef struct {
    int numPassagem;
    Passageiro passageiro;
    int numViagem;
    int numAss;
    metodo_Pag metodoPag;
} Passagem;

//Funções para imprimir cada struct
void printHorario(Horario h) {
    printf("%02d:%02d:%02d", h.horas, h.minutos, h.segundos);
}
void printData(Data d) {
    printf("%02d/%02d/%d", d.dia, d.mes, d.ano);
}
void printCEP(CEP c) {
    printf("CEP: %d\n", c.numCEP);
    printf("Rua: %s. ", c.rua);
    printf("Bairro: %s\n", c.bairro);
    printf("Cidade: %s, ", c.cidade);
    printf("%s, ", c.estado);
    printf("%s\n", c.pais);
}
void printOnibus(Onibus o) {
    printf("\nOnibus: %d\n", o.numOnibus);
    printf("Placa: %s. ", o.placa);
    printf("Modelo: %s. ", o.modelo);
    printf("Ano Fabricacao: ");
    printData(o.anoFabricacao);
    printf("\nCapacidade: %d\n", o.capacidade);

}
void printAssentos(Viagem v) {
    for(int i = 0; i < v.onibus.capacidade; i += 4) {
        if(i < v.onibus.capacidade)
            printf("[%02d %c]", i+1, v.numAss[i] ? 'X':'L');
        if(i+1 < v.onibus.capacidade)
            printf("[%02d %c]   ", i+2, v.numAss[i+1] ? 'X':'L');
        if(i+2 < v.onibus.capacidade)
            printf("[%02d %c]", i+3, v.numAss[i+2] ? 'X':'L');
        if(i+3 < v.onibus.capacidade)
            printf("[%02d %c]", i+4, v.numAss[i+3] ? 'X':'L');
        printf("\n");
    }
}
void printViagem(Viagem v) {
    printf("\n\n=============================================================================================================");
    printf("\n=== VIAGEM No. %d ===\n", v.numViagem);

    printf("\n--- Onibus ---\n");
    printOnibus(v.onibus);

    printf("\n--- Saida ---\n");
    printf("Data: ");
    printData(v.dataSaida);
    printf("\nHorario: ");
    printHorario(v.horarioSaida);
    printf("\n");

    printf("\n--- Origem ---\n");
    printCEP(v.origem);

    printf("\n--- Chegada Prevista ---\n");
    printf("Data: ");
    printData(v.dataPrevistaChegada);
    printf("\nHorario: ");
    printHorario(v.horarioPrevistoChegada);
    printf("\n");

    printf("\n--- Destino ---\n");
    printCEP(v.destino);

    printf("\n===== MAPA DO ONIBUS =====\n");
    printf("L = Livre | X = Ocupado\n\n");

    printAssentos(v);

    printf("\n>> Total de Assentos Disponiveis: %d <<\n", v.assLivres);

    printf(">> Preco da passagem: R$ %.2f <<\n", v.preco);

    printf("=============================================================================================================\n\n");
}
void printPassageiro(Passageiro p) {
    printf("\n=== PASSAGEIRO ===\n");

    printf("Nome: %s\n", p.nome);
    printf("CPF: %s\n", p.CPF);

    printf("Data de Nascimento: ");
    printData(p.dataNascimento);
    printf("\n");

    printf("Telefone: %s\n", p.telefone);
}
void printPassagem(Passagem pass) {
    printf("\n=== PASSAGEM ===\n");

    printf("Numero da Passagem: %d\n", pass.numPassagem);
    printf("Nome do Passageiro: %s\n", pass.passageiro.nome);
    printf("Numero da Viagem: %d\n", pass.numViagem);
    printf("Numero do Assento: %d\n", pass.numAss);
    printf("Metodo de pagamento realizado: ");
    switch (pass.metodoPag) {
        case Dinheiro: {
            printf("Dinheiro");
            break;}
        case Boleto: {
            printf("Boleto");
            break;}
        case Pix: {
            printf("Pix");
            break;}
        case Debito: {
            printf("Debito");
            break;}
        case Credito: {
            printf("Credito");
            break;}
        case Vauncher: {
            printf("Vauncher");
            break;}
        case Cheque: {
            printf("Cheque");
            break;}
    } printf("\n");
}

//Funções add passagem, passageiro e viagem
Passageiro addPassageiro(const char* nome, const char* cpf, int dia, int mes, int ano, const char* tel) {
    Passageiro passageiro;

    strcpy(passageiro.nome, nome);
    strcpy(passageiro.CPF, cpf);
    passageiro.dataNascimento.dia = dia;
    passageiro.dataNascimento.mes = mes;
    passageiro.dataNascimento.ano = ano;
    strcpy(passageiro.telefone, tel);

    return passageiro;
}
Passagem addPassagem(int nPass, const char *nome, int nVia, int numAss, metodo_Pag metPag) {
    Passagem passagem;

    passagem.numPassagem = nPass;
    strcpy(passagem.passageiro.nome, nome);
    passagem.numViagem = nVia;
    passagem.numAss = numAss;
    passagem.metodoPag = metPag;

    return passagem;
}
Viagem addViagem(
    int numViagem,
    int dSD, int dSM, int dSA, int hSH, int hSM, int hSS,
    int cepS , const char *ruaS, const char *bairroS, const char *cidadeS, const char *estadoS, const char *paisS,
    int dCD, int dCM, int dCA, int hCH, int hCM, int hCS,
    int cepC , const char *ruaC, const char *bairroC, const char *cidadeC, const char *estadoC, const char *paisC,
    Onibus nOnibus, int orgAss[], float preco) {

    Viagem v;
    v.numViagem = numViagem;
    v.dataSaida.dia = dSD;
    v.dataSaida.mes = dSM;
    v.dataSaida.ano = dSA;
    v.horarioSaida.horas = hSH;
    v.horarioSaida.minutos = hSM;
    v.horarioSaida.segundos = hSS;
    v.origem.numCEP = cepS;
    strcpy(v.origem.rua, ruaS);
    strcpy(v.origem.bairro, bairroS);
    strcpy(v.origem.cidade, cidadeS);
    strcpy(v.origem.estado, estadoS);
    strcpy(v.origem.pais, paisS);

    v.dataPrevistaChegada.dia = dCD;
    v.dataPrevistaChegada.mes = dCM;
    v.dataPrevistaChegada.ano = dCA;
    v.horarioPrevistoChegada.horas = hCH;
    v.horarioPrevistoChegada.minutos = hCM;
    v.horarioPrevistoChegada.segundos = hCS;
    v.destino.numCEP = cepC;
    strcpy(v.destino.rua, ruaC);
    strcpy(v.destino.bairro, bairroC);
    strcpy(v.destino.cidade, cidadeC);
    strcpy(v.destino.estado, estadoC);
    strcpy(v.destino.pais, paisC);

    v.onibus = nOnibus;

    v.assLivres = 0;
    for(int i = 0; i < nOnibus.capacidade; i++) {
        v.numAss[i] = orgAss[i]; // copia estado

        if(v.numAss[i] == 0) {
            v.assLivres++;
        } // conta livres
    }
    v.preco = preco;
    return v;
}


//-----------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------

int main() {
    int nPassagem = 1, nPassageiro = 1, nViagem = 1, asspass = 0, ocupados[MAX_Capacidade];
    srand(time(NULL) ^ clock()); // importante para números aleatórios

    //Definindo Horários:
    Horario h1 = {.horas = 14, .minutos = 30, .segundos = 0};
    Horario h2 = {.horas = 15, .minutos = 0, .segundos = 0};
    Horario h3 = {.horas = 16, .minutos = 45, .segundos = 0};
    Horario h4 = {.horas = 17, .minutos = 20, .segundos = 0};
    Horario h5 = {.horas = 18, .minutos = 50, .segundos = 0};
    Horario h6 = {.horas = 20, .minutos = 25, .segundos = 0};

    //Definindo Datas:
    Data d1 = {.dia = 27, .mes = 3, .ano = 2026};
    Data d2 = {.dia = 28, .mes = 3, .ano = 2026};
    Data d3 = {.dia = 29, .mes = 3, .ano = 2026};
    Data d4 = {.dia = 30, .mes = 3, .ano = 2026};
    Data d5 = {.dia = 31, .mes = 3, .ano = 2026};
    Data d6 = {.dia = 1, .mes = 4, .ano = 2026};

    Data df1 = {.dia = 1, .mes = 10, .ano = 2000};
    Data df2 = {.dia = 10, .mes = 7, .ano = 2000};

    //Definindo Passageiros:
    Passageiro passageiro[100];
    passageiro[nPassageiro++] = addPassageiro("Jose", "123.456.789-00", 01, 01, 2000, "(14)98765-4321");
    passageiro[nPassageiro++] = addPassageiro("Maria", "123.456.789-01", 11, 11, 2001, "(14)98765-4322");
    passageiro[nPassageiro++] = addPassageiro("Rafael", "123.456.789-02", 17, 10, 2001, "(14)98765-4323");
    passageiro[nPassageiro++] = addPassageiro("Melisa", "123.456.789-03", 19, 8, 2002, "(14)98765-4324");
    passageiro[nPassageiro++] = addPassageiro("Marcos", "123.456.789-04", 30, 5, 2001, "(14)98765-4325");
    passageiro[nPassageiro++] = addPassageiro("Ana", "123.456.789-05", 31, 3, 2003, "(14)98765-4326");
    passageiro[nPassageiro++] = addPassageiro("Joaquim", "123.456.789-06", 2, 4, 2002, "(14)98765-4327");
    passageiro[nPassageiro++] = addPassageiro("Beatriz", "123.456.789-07", 9, 2, 2001, "(14)98765-4328");
    passageiro[nPassageiro++] = addPassageiro("Luiz", "123.456.789-08", 5, 6, 2000, "(14)98765-4329");
    passageiro[nPassageiro++] = addPassageiro("Adriana", "123.456.789-09", 20, 1, 2000, "(14)98765-4320");

    //Definindo CEPs:
    CEP c1 = {.numCEP = 12345, .rua = "Rua A", .bairro = "Bairro B", .cidade = "Jacarezinho", .estado = "Parana", .pais = "Brasil"};
    CEP c2 = {.numCEP = 12346, .rua = "Rua B", .bairro = "Bairro C", .cidade = "Curitiba", .estado = "Parana", .pais = "Brasil"};
    CEP c3 = {.numCEP = 12347, .rua = "Rua C", .bairro = "Bairro D", .cidade = "Londrina", .estado = "Parana", .pais = "Brasil"};
    CEP c4 = {.numCEP = 12348, .rua = "Rua D", .bairro = "Bairro E", .cidade = "Ourinhos", .estado = "Sao Paulo", .pais = "Brasil"};
    CEP c5 = {.numCEP = 12349, .rua = "Rua E", .bairro = "Bairro F", .cidade = "Bauru", .estado = "Sao Paulo", .pais = "Brasil"};
    CEP c6 = {.numCEP = 12350, .rua = "Rua F", .bairro = "Bairro G", .cidade = "Sao Paulo", .estado = "Sao Paulo", .pais = "Brasil"};

    //Definindo Onibus:
    Onibus o1 = {.numOnibus = 1, .capacidade = 48, .placa = "ABC-1234", .modelo = "Volare", .anoFabricacao = df2};
    Onibus o2 = {.numOnibus = 2, .capacidade = 40, .placa = "DEF-5678", .modelo = "Marcopolo", .anoFabricacao = df1};
    Onibus o3 = {.numOnibus = 3, .capacidade = 44, .placa = "GHI-9012", .modelo = "Comil", .anoFabricacao = df2};
    Onibus o4 = {.numOnibus = 4, .capacidade =  56, .placa = "JKL-3456", .modelo = "Neobus", .anoFabricacao = df1};
    Onibus o5 = {.numOnibus = 5, .capacidade = 60, .placa = "MNO-7890", .modelo = "Mascarello", .anoFabricacao = df1};
    Onibus o6 = {.numOnibus = 6, .capacidade = 52, .placa = "PQR-2345", .modelo = "Irizar", .anoFabricacao = df2};

    //Definindo Viagens e passagens:
    Passagem passagem[100]; Viagem viagem[20];
    // Ida
    asspass = 0;for(int i = 0; i < o1.capacidade; i++) { //ocupados aleatórios com x% do total
        ocupados[i] = (rand() % 100) < 70;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d1.dia, d1.mes, d1.ano, h1.horas, h1.minutos, h1.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  d1.dia, d1.mes, d1.ano, h2.horas, h2.minutos, h2.segundos,
                                  c1.numCEP, c1.rua, c1.bairro, c1.cidade, c1.estado, c1.pais,
                                  o1, ocupados,  50);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem,asspass, Pix);
    asspass = 0;for(int i = 0; i < o2.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 30;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d2.dia, d2.mes, d2.ano, h2.horas, h2.minutos, h2.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  d2.dia, d2.mes, d2.ano, h3.horas, h3.minutos, h3.segundos,
                                  c2.numCEP, c2.rua, c2.bairro, c2.cidade, c2.estado, c2.pais,
                                  o2, ocupados,  350);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Credito);
    asspass = 0;for(int i = 0; i < o3.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 80;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d3.dia, d3.mes, d3.ano, h3.horas, h3.minutos, h3.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  d3.dia, d3.mes, d3.ano, h4.horas, h4.minutos, h4.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  o3, ocupados, 200);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Pix);
    asspass = 0;for(int i = 0; i < o4.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 20;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d4.dia, d4.mes, d4.ano, h4.horas, h4.minutos, h4.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  d4.dia, d4.mes, d4.ano, h5.horas, h5.minutos, h5.segundos,
                                  c5.numCEP, c5.rua, c5.bairro, c5.cidade, c5.estado, c5.pais,
                                  o4, ocupados,  200);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Vauncher);
    asspass = 0;for(int i = 0; i < o5.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 40;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d5.dia, d5.mes, d5.ano, h5.horas, h5.minutos, h5.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  d5.dia, d5.mes, d5.ano, h6.horas, h6.minutos, h6.segundos,
                                  c6.numCEP, c6.rua, c6.bairro, c6.cidade, c6.estado, c6.pais,
                                  o5, ocupados,  300);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Pix);

    // Volta
    asspass = 0;for(int i = 0; i < o2.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 65;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d2.dia, d2.mes, d2.ano, h1.horas, h1.minutos, h1.segundos,
                                  c1.numCEP, c1.rua, c1.bairro, c1.cidade, c1.estado, c1.pais,
                                  d2.dia, d2.mes, d2.ano, h2.horas, h2.minutos, h2.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  o2, ocupados,  50);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Debito);
    asspass = 0;for(int i = 0; i < o3.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 50;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d3.dia, d3.mes, d3.ano, h2.horas, h2.minutos, h2.segundos,
                                  c2.numCEP, c2.rua, c2.bairro, c2.cidade, c2.estado, c2.pais,
                                  d3.dia, d3.mes, d3.ano, h3.horas, h3.minutos, h3.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  o3, ocupados,  350);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Dinheiro);
    asspass = 0;for(int i = 0; i < o4.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 10;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d4.dia, d4.mes, d4.ano, h3.horas, h3.minutos, h3.segundos,
                                  c3.numCEP, c3.rua, c3.bairro, c3.cidade, c3.estado, c3.pais,
                                  d4.dia, d4.mes, d4.ano, h4.horas, h4.minutos, h4.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  o4, ocupados,  200);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Pix);
    asspass = 0;for(int i = 0; i < o5.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 90;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d5.dia, d5.mes, d5.ano, h4.horas, h4.minutos, h4.segundos,
                                  c5.numCEP, c5.rua, c5.bairro, c5.cidade, c5.estado, c5.pais,
                                  d5.dia, d5.mes, d5.ano, h5.horas, h5.minutos, h5.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c4.estado, c4.pais,
                                  o5, ocupados,  200);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Cheque);
    asspass = 0;for(int i = 0; i < o5.capacidade; i++) {
        ocupados[i] = (rand() % 100) < 90;
        if (asspass == NULL && ocupados[i] == 1) {
            asspass = i+1;}}
    viagem[nViagem++] = addViagem(nViagem, d6.dia, d6.mes, d6.ano, h5.horas, h5.minutos, h5.segundos,
                                  c6.numCEP, c6.rua, c6.bairro, c6.cidade, c6.estado, c6.pais,
                                  d6.dia, d6.mes, d6.ano, h6.horas, h6.minutos, h6.segundos,
                                  c4.numCEP, c4.rua, c4.bairro, c4.cidade, c5.estado, c4.pais,
                                  o4, ocupados, 200);
    passagem[nPassagem++] = addPassagem(nPassagem, passageiro[nPassagem].nome, viagem[nPassagem].numViagem, asspass, Pix);

    //-----------------------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------------------

    bool sair = false;
    do {
        int opcao;
        int loop = 0;
        //Menu de opcoes com switch
        printf("\n-----------------------------------------------------------------------------------\n");
        printf("\n\n------> Menu de opcoes:\n");
        printf("1. Visualizar viagens disponiveis\n");
        printf("2. Comprar passagem\n");
        printf("3. Consultar passagens\n");
        printf("4. Consultar passageiros\n");
        printf("5. Consultar onibus\n");
        printf("6. Sair\n\n");
        printf(">>>>> Digite a opcao desejada: ");
        scanf("%d", &opcao);
        switch (opcao) {
            // Lógica para comprar passagem
            case 1: {
                //Imprimindo todas as viagens
                for (int i = 1; i < nViagem; i++) {
                    printViagem(viagem[i]);
                }
                printf("%d", nViagem);
                break;
            }
            //Principal lógica da rodoviaria: compra de passagens
            case 2: {
                int nViag;
                //Selecionando Viagem
                while (loop == 0) {
                    printf("\n=============================================================================================================\n\n");
                    printf("\n>>>>> Digite o numero da viagem desejada: \n");
                    printf("(Digite 0, zero, para cancelar a compra da viagem!) \n");
                    scanf("%d", &nViag);
                    if (nViag == 0) {
                        printf("\n\n<<<| VOCE CANCELOU SUA VIAGEM! |>>>\n ");
                        loop = 1;
                    } else if(nViag < 0 || nViag > nViagem) {
                        printf("| No. de viagem indisponivel. Tente Novamente. |\n\n");
                        nViag = 0;
                    }else {
                        for(int i = 1; i <= nViagem; i++) {
                            if (viagem[i].numViagem == nViag) {
                                printf("\n<<<| VIAGEM No. %d DISPONIVEL! |>>>", nViag);
                                loop = 2;
                            }
                        }
                    }
                }
                loop == 2 ? loop = 0 : printf("\n");
                int npass, noAss;
                //Verificando assLivres disponíveis
                while (loop == 0) {
                    //int npass = 1, noAss = 0;
                    printf("\n=============================================================================================================\n\n");
                    printf("\n\n<<<| INFORME O NUMERO DE PASSAGENS. |>>>\n");
                    printf("(Ou digite 0, zero, para cancelar a compra da viagem) \n ");
                    printf(">>>>> No. de pasagens: ");
                    scanf("%d", &npass);

                    for(int i = 0; i < nViagem; i++) {
                        if (viagem[i].numViagem == nViag) {
                            noAss = viagem[i].assLivres;
                        }
                    }
                    if (npass == 0) {
                        printf("\n\n<<<| VOCE CANCELOU SUA VIAGEM! |>>>\n ");
                        loop = 1;
                    }else if ((noAss < npass) || (npass < 0)) {
                        printf("<<<| Possui numero de assLivres insuficiente(%d) para sua viagem(%d). |>>>", noAss, npass);
                        printf("\n| Verifique sua viagem e tente novamente. |\n");
                        for (int i = 0; i < nViagem; i++) {
                            if (viagem[i].numViagem == nViag) {
                                printViagem(viagem[i]);
                            }
                        }
                    } else if (noAss >= npass) {
                        loop = 2;
                    }
                }
                loop == 2 ? loop = 0 : printf("\n");
                char nome[npass][100], cpf[npass][20], tel[npass][20];
                char dia[npass][4], mes[npass][4], ano[npass][6];
                metodo_Pag metPag;
                while (loop == 0) {
                    //Caso assLivres
                    //estejam disponíveis, ele subtraira o numero de assLivres
                    //e cadastra os passageiros e suas passagens

                    //Subtração de assLivres
                    //na viagem
                    for(int i = 0; i < nViagem; i++) {
                        if (viagem[i].numViagem == nViag) {
                            viagem[i].assLivres -= npass;
                        }
                    }
                    //Cadastro de passageiros
                    printf("\n=============================================================================================================\n\n");
                    printf("\n\n<<<| CADASTRO DE PASSAGEIROS |>>>\n\n");
                    printf("Digite as informacoes a seguir para cada passageiro (%d)\n", npass);
                    for (int i = 0; i < npass; i++) {
                        printf("\n\n<<<| PASSAGEIRO NO. %d |>>>\n(Pressione ENTER para comecar caso não apareca nada)\n", i+1);
                        getchar();

                        printf("\nNome: ");
                        fgets(nome[i], sizeof(nome[i]), stdin);
                        nome[i][strcspn(nome[i], "\n")] = '\0';
                        printf("CPF: ");
                        fgets(cpf[i], sizeof(cpf[i]), stdin);
                        cpf[i][strcspn(cpf[i], "\n")] = '\0';
                        printf("Telefone: ");
                        fgets(tel[i], sizeof(tel[i]), stdin);
                        tel[i][strcspn(tel[i], "\n")] = '\0';

                        printf("Dia: ");
                        fgets(dia[i], sizeof(dia[i]), stdin);
                        dia[i][strcspn(dia[i], "\n")] = '\0';
                        printf("Mes: ");
                        fgets(mes[i], sizeof(mes[i]), stdin);
                        mes[i][strcspn(mes[i], "\n")] = '\0';
                        printf("Ano: ");
                        fgets(ano[i], sizeof(ano[i]), stdin);
                        ano[i][strcspn(ano[i], "\n")] = '\0';

                        printf("\n=============================================================================================================\n\n");
                        printf("\n<<<| PASSAGEIRO NO. %d CADASTRADO! |>>>\n", i+1);

                        //Guardando e imprimindo os passageiros
                        passageiro[nPassageiro++] = addPassageiro(nome[i], cpf[i], atoi(dia[i]), atoi(mes[i]), atoi(ano[i]), tel[i]);
                        printPassageiro(passageiro[nPassageiro-1]);
                    }
                    loop = 2;
                }
                loop == 2 ? loop = 0 : printf("\n");
                int escAss;
                int v[MAX_Capacidade];
                //Escolhendo o assento
                while(loop == 0) {
                    for (int i = 0; i < npass; i++) {
                        printf("\nHa %d passageiros. Passageiro numero %d", npass, i+1);
                        printf("\nDigite o numero do assento (1-%d) ou 0 para sair: ", viagem[nViag].onibus.capacidade);
                        printf("\nNúmero da viagem escolhida: %d.\n", viagem[nViag].numViagem);
                        //Imprimindo assentos disponiveis
                        printAssentos(viagem[nViag]);
                        printf("\nDigite o numero do assento ou 0 para sair: ");
                        scanf("%d", &escAss);
                        getchar();

                        if(escAss == 0) {
                            printf("Encerrando sistema...\n");
                            loop = 1;
                            break;
                        }
                        if(escAss < 1 || escAss > 60) {
                            printf("Assento invalido!\n");
                            continue;
                        }
                        if(viagem[nViag].numAss[escAss-1] == 1) {
                            printf("Assento ja ocupado!\n");
                        } else {
                            viagem[nViag].numAss[escAss-1] = 1;
                            printf("Assento %d reservado com sucesso!\n", escAss);
                            loop = 2;
                            v[i] = escAss;
                            printAssentos(viagem[nViag]);
                        }
                    }
                }
                loop == 2 ? loop = 0 : viagem[nViag].assLivres += npass;
                loop == 2 ? loop = 0 : nPassageiro -= npass;
                int vetor[npass]; int x;int y=0;
                foreach(x, v, npass) {
                    printf("%d\n", x);
                    printf("%d\n", y);
                    vetor[y] = x;
                    y++;
                    printf("%d\n", y);
                }
                while (loop == 0) {
                    //Calculando total das passagens
                    float valorTotal;
                    printf("\n=============================================================================================================\n\n");
                    printf("\n\n<<<| PAGAMENTO |>>>");
                    for (int i = 0; i < nViagem; i++) {
                        if (viagem[i].numViagem == nViag) {
                            printf("\n\nValor unitario: %.02f\n", viagem[i].preco);
                            valorTotal = viagem[i].preco * npass;
                            printf("Valor total (x%d): %.02f\n", npass, valorTotal);
                            do {
                                printf("\n----> Selecione o metodo de pagamento: ");
                                printf("\n0. Para sair");
                                printf("\n1. Dinheiro");
                                printf("\n2. Boleto");
                                printf("\n3. Pix");
                                printf("\n4. Debito");
                                printf("\n5. Credito");
                                printf("\n6. Vauncher");
                                printf("\n7. Cheque");

                                char mp[3];
                                printf("\n\n>>>>> Metodo de pagamento: ");
                                fgets(mp, sizeof(mp), stdin);
                                mp[strcspn(mp, "\n")] = '\0';

                                switch (atoi(mp)) {
                                    case 0:
                                        printf("Encerrando sistema...\n");
                                        loop = 1;
                                        break;
                                    case Dinheiro:
                                        metPag = Dinheiro;
                                        loop = 2;
                                        break;
                                    case Boleto:
                                        metPag = Boleto;
                                        loop = 2;
                                        break;
                                    case Pix:
                                        metPag =  Pix;
                                        loop = 2;
                                        break;
                                    case Debito:
                                        metPag = Debito;
                                        loop = 2;
                                        break;
                                    case Credito:
                                        metPag = Credito;
                                        loop = 2;
                                        break;
                                    case Vauncher:
                                        metPag = Vauncher;
                                        loop = 2;
                                        break;
                                    case Cheque:
                                        metPag = Cheque;
                                        loop = 2;
                                        break;
                                    default:
                                        printf("\n\n<<<| METODO DE PAGAMENTO INVALIDO! |>>>");
                                        printf("\n<<<| Tente novamente. |");
                                }
                            } while (loop == 0);
                        }
                    }
                }
                loop == 2 ? loop = 0 : viagem[nViag].numAss[escAss-1] = 0;
                while (loop == 0) {
                    //Guardando passagens
                    for (int i = 0; i < npass; i++) {
                        passagem[nPassagem++] = addPassagem(nPassagem, nome[i], nViag, vetor[i], metPag);
                        //Imprimindo
                        printf("\n=============================================================================================================\n\n");
                        printf("\n<<<| PASSAGEM NO. %d CADASTRADO! |>>>\n", nPassagem);
                        printPassagem(passagem[nPassagem-1]);
                    }
                    //Imprimindo viagens para verificar assLivres
                    //disponíveis
                    for (int i = 0; i < nViagem; i++) {
                        if (viagem[i].numViagem == nViag) {
                            printViagem(viagem[i]);
                        }
                    }
                    printf("\n=============================================\n<<<| BOA VIAGEM! |>>>\n=============================================\n");
                    loop = 2;
                }
                loop == 2 ? loop = 0 : printf("\n=============================================================================================================\n\n"
                "Direcionaod ao menu...\n\n");
                break;
            }
            // Lógica para consultar passagens
            case 3: {
                for (int i = 1; i < nPassagem; i++) {
                    printPassagem(passagem[i]);
                }
                printf("%d", nPassagem);
                break;
            }
            // Consultando passageiros
            case 4: {
                for (int i = 1; i < nPassageiro; i++) {
                    printPassageiro(passageiro[i]);
                }
                printf("%d", nPassageiro);
                break;
            }
            // Imprimindo onibus
            case 5: {
                printOnibus(o1);
                printOnibus(o2);
                printOnibus(o3);
                printOnibus(o4);
                printOnibus(o5);
                printOnibus(o6);
                break;
            }
            // Sair do programa
            case 6: {
                sair = true;
                break;
            }
            //Caso a opção seja inválida
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while(sair != true);
    printf("Voce saiu do programa.\nObrigado por usar nosso sistema de compra de passagens!\n");
    printf("\n-----------------------------------------------------------------------------------\n");
    return 0;
}