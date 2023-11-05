#include "carro.hpp"
#include "menu.hpp"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdio>
using namespace std;

const int MAX = 32;
Carro Frota[MAX] {};
unsigned short qtd_cartas = 0;

void salvar() {
    cout << "Salvando o baralho no arquivo...\n";
    ofstream fout("..//baralho.dat", ios_base::out | ios_base::binary);
    if(!fout.is_open()) {
        cerr << "Erro ao fazer a gravação do arquivo do baralho\n";
        cout << "Saindo do programa...\n";
        Sleep();
        exit(EXIT_FAILURE);
    }

    char cabecalho[] = "BARALHO";
    fout.write((char*)cabecalho, strlen(cabecalho));
    fout.write((char*)&qtd_cartas, sizeof(unsigned short));
    fout.write((char*)&Frota, sizeof(Carro) * qtd_cartas);
    
    fout.close();
    cout << "Gravação do arquivo do baralho com sucesso!\n";
    cout << "Saindo do programa...\n";
}

static inline void LimparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void menu() {
    LimparTela();
    cout << "Gerador de Cartas\n";
    cout << "-----------------\n";
    cout << "(C)adastrar\n";
    cout << "(I)mportar\n";
    cout << "(A)lterar\n";
    cout << "(E)xcluir\n";
    cout << "(L)istar\n";
    cout << "(S)air\n\n";
    cout << "Escolha uma opção: ";
}

static void validar_atributo(float & atributo) {
    const int MIN = 1; 
    while(cin.fail() || atributo < MIN) {
        if(cin.fail()) {
            cout << "Entrada inválida! Por favor, insira um valor numérico válido: ";
        } else if(atributo < MIN) {
            cout << "Valor inválido! Por favor, insira um valor maior ou igual a 1: ";
        }
        LimparBuffer();
        cin >> atributo;
    }
}

static void ler_carro(Carro & carro) {
    cout << "Modelo: ";
    cin.ignore();
    cin.getline(carro.modelo, 50);

    cout << "Velocidade máxima: ";
    cin >> carro.velocidade_maxima;
    validar_atributo(carro.velocidade_maxima);

    cout << "Aceleração: ";
    cin >> carro.aceleracao;
    validar_atributo(carro.aceleracao);

    cout << "Potência: ";
    cin >> carro.potencia;
    validar_atributo(carro.potencia);

    cout << "Torque: ";
    cin >> carro.torque;
    validar_atributo(carro.torque);

    cout << "Preço: ";
    cin >> carro.preco;
    validar_atributo(carro.preco);
}

void cadastrar() {
    LimparTela();
    if(qtd_cartas == MAX) {
        cout << "O baralho está cheio\n";
        Sleep();
        return;
    }

    Carro carro;
    cout << "Cadastrar Carta\n";
    cout << "---------------\n";
    ler_carro(carro);    

    Frota[qtd_cartas] = carro;
    qtd_cartas++;
}

void listar() {
    LimparTela();
    if(qtd_cartas == 0) {
        cout << "O baralho está vazio\n";
        Sleep();
        return;
    }

    cout << "Cartas do baralho\n";
    cout << "-----------------\n";
    for(int i = 0;i < qtd_cartas;++i) {
        printf("#%d %s %.0f %.1f %.0f %.1f %.0f\n", 
        i + 1, 
        Frota[i].modelo, 
        Frota[i].velocidade_maxima,
        Frota[i].aceleracao,
        Frota[i].potencia,
        Frota[i].torque,
        Frota[i].preco);
    }
    
    cout << "\nPressione Enter para continuar...\n";
    cin.ignore();
    cin.ignore();
}

static void validar_num_carta(int & num_carta) {
    while(cin.fail() || num_carta > qtd_cartas || num_carta < 1) {
        if(num_carta > qtd_cartas || num_carta < 1) {
            cout << "Número da carta inválido. Digite novamente o número da carta: ";
        } else if(cin.fail()) {
            cout << "Entrada inválida! Por favor, insira um valor numérico válido: ";
        }
        LimparBuffer();
        cin >> num_carta;
    }
}

void alterar() {
    LimparTela();
    if(qtd_cartas == 0) {
        cout << "O baralho está vazio\n";
        Sleep();
        return;
    }

    cout << "Atualizar Carta\n";
    cout << "---------------\n";

    for(int i = 0;i < qtd_cartas;++i) {
        printf("%d) %s\n", i + 1, Frota[i].modelo);
    }
    
    cout << "\nDigite o número da carta: ";
    int num_carta;
    cin >> num_carta;
    validar_num_carta(num_carta);

    int indice = num_carta - 1; 

    cout << "Alterando a carta " << Frota[indice].modelo << " do baralho\n";
    ler_carro(Frota[indice]);
}

void importar() {
    LimparTela();
    if(qtd_cartas == MAX) {
        cout << "O baralho está cheio\n";
        Sleep();
        return;
    }
    
    cout << "Importar Cartas\n";
    cout << "---------------\n";
    cout << "Arquivo: ";
    char arquivo[40];
    cin >> arquivo;
    ifstream fin(arquivo, ios_base::in);
    if(!fin.is_open()) {
        cerr << "Erro ao abrir o arquivo\n";
        Sleep();
        return;
    }

    cout << "Importando:\n";
    for(int i = qtd_cartas;i < MAX && fin.peek() != EOF;++i) {
        fin.getline(Frota[i].modelo, 50);
        fin >> Frota[i].velocidade_maxima 
            >> Frota[i].aceleracao
            >> Frota[i].potencia
            >> Frota[i].torque
            >> Frota[i].preco;
        
        fin.ignore();
        fin.ignore();

        printf("%d %s %.0f %.1f %.0f %.1f %.0f\n", 
        i + 1, 
        Frota[i].modelo, 
        Frota[i].velocidade_maxima,
        Frota[i].aceleracao,
        Frota[i].potencia,
        Frota[i].torque,
        Frota[i].preco);
        qtd_cartas++;
    }

    cout << "Pressione Enter para continuar...\n";
    cin.ignore();
    cin.ignore();
}

void excluir() {
    LimparTela();
    if(qtd_cartas == 0) {
        cout << "O baralho está vazio\n";
        Sleep();
        return;
    }

    cout << "Excluir Carta\n";
    cout << "-------------\n";
    for(int i = 0;i < qtd_cartas;++i) {
        printf("%d) %s\n", i + 1, Frota[i].modelo);
    }

    cout << "\nDigite o número da carta: ";
    int num_carta;
    cin >> num_carta;
    validar_num_carta(num_carta);

    for(int i = num_carta - 1;i < qtd_cartas;++i) {
        Frota[i] = Frota[i + 1];
    }

    qtd_cartas--;

    cout << "\nA carta foi excluida do baralho\n";
    Sleep();
}