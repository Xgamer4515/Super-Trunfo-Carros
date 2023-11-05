#pragma once

#include <chrono>
#include <thread>
using std::chrono::seconds;
using std::this_thread::sleep_for;

#if defined(_WIN32) || defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

inline void ConfigurarAcentuacaoConsole() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
} 
#endif

inline void LimparTela() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

inline void Sleep() {
    sleep_for(seconds(2));
}

enum Opcoes {
    CADASTRAR = 'C',
    IMPORTAR = 'I',
    EXCLUIR = 'E',
    ALTERAR = 'A',
    LISTAR = 'L',
    SAIR = 'S',
};

void cadastrar();
void importar();
void excluir();
void alterar();
void salvar();
void listar();
void menu();