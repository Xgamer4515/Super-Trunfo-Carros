#include "structs.hpp"
#include "menu.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <random>
#include <cstdio>
#include <limits>
using namespace std;

Carro * Baralho = nullptr;
unsigned short qtd_cartas = 0;

static void Sair(const char * mensagem) {
    cerr << mensagem;
    cout << "Saindo do programa...\n";
    Sleep();
    exit(EXIT_FAILURE);
}

void abrir_arquivo() {
    ifstream fin("..//baralho.dat", ios_base::in | ios_base::binary);
    if(!fin.is_open()) {
        Sair("Erro ao abrir o arquivo do baralho\n");
    }

    char cabecalho[8] {};
    const int max = 7;
    fin.read((char*)&cabecalho, max);
    if(strcmp(cabecalho,"BARALHO") != 0) {
        Sair("Arquivo do baralho incorreto\n");
    }

    fin.read((char*)&qtd_cartas, sizeof(unsigned short));
    if(qtd_cartas < 8) {
        Sair("Quantidade de cartas insuficiente para jogar\n");
    }

    Baralho = new Carro[qtd_cartas];
    fin.read((char*)Baralho, sizeof(Carro) * qtd_cartas);
    fin.close();
}

void menu() {
    LimparTela();
    cout << "Super Trunfo Carros\n";
    cout << "-------------------\n"; 
    cout << "Iniciar nova partida? [S/N] ";
}

void validar_opcao(char & opcao) {
    while(opcao != SIM && opcao != NAO) {
        cout << "Opção inválida. Digite novamente sua opçao: ";
        cin >> opcao;
    }
}

void ler_jogador(Jogador & jogador1, Jogador & jogador2) {
    cout << "Jogador1: ";
    cin >> jogador1.nome;

    cout << "Jogador2: ";
    cin >> jogador2.nome;

    cout << "----------\n";
}

static void distribuir_cartas(Jogador & jogador1, Jogador & jogador2) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, qtd_cartas - 1);
    jogador1.alocar_vetor();
    jogador2.alocar_vetor();

    int num_cartas = 4;
    int indices[qtd_cartas];
    for (int i = 0; i < qtd_cartas; ++i) {
        indices[i] = i;
    }

    for (int i = qtd_cartas - 1; i > 0; --i) {
        int j = dist(mt) % (i + 1);
        swap(indices[i], indices[j]);
    }

    for (int i = 0; i < num_cartas; ++i) {
        jogador1.cartas[i] = &Baralho[indices[i]];
        jogador2.cartas[i] = &Baralho[indices[i + num_cartas]];
    }
}

static void menu_jogo() {
    cout << "1. Velocidade máxima\n";
    cout << "2. Aceleração\n";
    cout << "3. Potência\n";
    cout << "4. Torque\n";
    cout << "5. Preço\n\n";
    cout << "Escolha atributo: ";
}

static void alterar_pontos(Jogador & jogador1, Jogador & jogador2, float atributo_jogador1, float atributo_jogador2) {
    if(atributo_jogador1 > atributo_jogador2) {
        jogador1.pontos += 2;
    } else if(atributo_jogador1 == atributo_jogador2) {
        jogador1.pontos += 1;
        jogador2.pontos += 1;
    } else {
        jogador2.pontos += 2;
    }
}

static void verificar_vencedor(Jogador & jogador1, Jogador & jogador2, int atributo, int indice) {
    enum Atributos {
        VELOCIDADE_MAXIMA = 1,
        ACELERACAO,
        POTENCIA,
        TORQUE,
        PRECO,
    };

    float atributo_jogador1, atributo_jogador2;

    switch(atributo) {
        case VELOCIDADE_MAXIMA:
            atributo_jogador1 = jogador1.cartas[indice]->velocidade_maxima; 
            atributo_jogador2 = jogador2.cartas[indice]->velocidade_maxima;
            break;
        case ACELERACAO:
            atributo_jogador1 = jogador1.cartas[indice]->aceleracao; 
            atributo_jogador2 = jogador2.cartas[indice]->aceleracao;
            break;
        case POTENCIA:
            atributo_jogador1 = jogador1.cartas[indice]->potencia; 
            atributo_jogador2 = jogador2.cartas[indice]->potencia;
            break;
        case TORQUE:
            atributo_jogador1 = jogador1.cartas[indice]->torque; 
            atributo_jogador2 = jogador2.cartas[indice]->torque;
            break;
        case PRECO:
            atributo_jogador1 = jogador1.cartas[indice]->preco; 
            atributo_jogador2 = jogador2.cartas[indice]->preco;
            break;
    }

    if(atributo == ACELERACAO || atributo == TORQUE) {
        if(atributo == ACELERACAO) {
            alterar_pontos(jogador1, jogador2, atributo_jogador2, atributo_jogador1);
        } else {
            alterar_pontos(jogador1, jogador2, atributo_jogador1, atributo_jogador2);
        }

        printf("\n[%s] %s | %.1f\n", jogador1.nome, jogador1.cartas[indice]->modelo, atributo_jogador1);
        printf("[%s] %s | %.1f\n\n", jogador2.nome, jogador2.cartas[indice]->modelo, atributo_jogador2);
    } else {
        alterar_pontos(jogador1, jogador2, atributo_jogador1, atributo_jogador2);
        printf("\n[%s] %s | %.0f\n", jogador1.nome, jogador1.cartas[indice]->modelo, atributo_jogador1);
        printf("[%s] %s | %.0f\n\n", jogador2.nome, jogador2.cartas[indice]->modelo, atributo_jogador2);
    }
}

static void LimparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static void validar_atributo(int & atributo) {
    while(atributo < 1 || cin.fail() || atributo > 5) {
        if(atributo < 1 || atributo > 5) {
            cout << "Atributo inválido. Digite novamente o atributo: ";
        } else if(cin.fail()) {
            cout << "Entrada inválida! Por favor, digite novamente o atributo: ";
        }
        LimparBuffer();
        cin >> atributo;
    }
}

void jogar(Jogador & jogador1, Jogador & jogador2) {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 3);
    bool vez_jogador1 = true;
    int indice;

    distribuir_cartas(jogador1, jogador2);
    LimparTela();
    for(int i = 0;i < 4;++i) {
        indice = dist(mt);
        if(vez_jogador1) {
            printf("[%s]\n\n", jogador1.nome);
            printf("Carta: %s\n", jogador1.cartas[indice]->modelo);
        } else {
            printf("[%s]\n\n", jogador2.nome);
            printf("Carta: %s\n", jogador2.cartas[indice]->modelo);
        }

        menu_jogo();
        int atributo;
        cin >> atributo;
        validar_atributo(atributo);
        verificar_vencedor(jogador1, jogador2, atributo, indice);

        printf("Placar: %s %d x %s %d\n", jogador1.nome, jogador1.pontos, jogador2.nome, jogador2.pontos);
        printf("--------------------------\n");
        vez_jogador1 = !vez_jogador1;

        Sleep();
        LimparTela();
    }

    printf("Final: %s %d x %s %d\n", jogador1.nome, jogador1.pontos, jogador2.nome, jogador2.pontos);
    Sleep();
}