#include "menu.hpp"
#include <iostream>
using std::cin; 

extern Carro * Baralho;

int main() {
#if defined(_WIN32) || defined(_WIN64)
    ConfigurarAcentuacaoConsole();
#endif

    abrir_arquivo();
    menu();
    char opcao;
    cin >> opcao;
    validar_opcao(opcao);

    Jogador jogador1, jogador2;
    
    while(opcao != NAO) {
        ler_jogador(jogador1,jogador2);
        jogar(jogador1,jogador2);

        menu();
        cin >> opcao;
        validar_opcao(opcao);
    }
    
    delete[] Baralho;
    jogador1.desalocar_vetor();
    jogador2.desalocar_vetor(); 
}