#pragma once

struct Carro {
    char modelo[50];
    float velocidade_maxima;
    float aceleracao;
    float potencia;
    float torque;
    float preco;
};

struct Jogador {
    Carro * cartas[4];
    int pontos = 0;
    char nome[20];

    inline void alocar_vetor() {
        for (int i = 0; i < 4; i++) {
            cartas[i] = new Carro;
        }
    }

    inline void desalocar_vetor() {
        for (int i = 0; i < 4; i++) {
            if(cartas[i] != nullptr) {
                delete cartas[i];
                cartas[i] = nullptr;
            }
        }
    }
};