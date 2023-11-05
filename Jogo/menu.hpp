#pragma once

#include "structs.hpp"
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
    sleep_for(seconds(3));
}

enum OpcoesMenu {
    SIM = 'S',
    NAO = 'N',
};

void ler_jogador(Jogador&,Jogador&);
void jogar(Jogador&,Jogador&);
void validar_opcao(char&);
void abrir_arquivo();
void menu();