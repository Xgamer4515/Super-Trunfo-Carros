#include "menu.hpp"
#include <iostream>
using std::cin;

int main() {
#if defined(_WIN32) || defined(_WIN64)
    ConfigurarAcentuacaoConsole();
#endif

    menu();
    char opcao;
    cin >> opcao;

    while(opcao != SAIR) {
        switch(opcao) {
            case CADASTRAR: cadastrar(); break;
            case IMPORTAR: importar(); break;
            case EXCLUIR: excluir(); break;
            case ALTERAR: alterar(); break;
            case LISTAR: listar(); break;
        }

        menu();
        cin >> opcao;
    }

    salvar();    
    return 0;
}