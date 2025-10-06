#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "../core/GameState.h"
using namespace std;
using namespace System;

class Instrucciones : public GameState {
private:
    EstructuraEstatica* layout;
    EstructuraDinamica* input;
    short ancho;
    short alto;
    vector<string> fondo;

public:
    Instrucciones(short ancho = 150, short alto = 60);
    ~Instrucciones();
    EstructuraDinamica* getInput() const { return this->input; };

    void handleInput(Game* game, char tecla) override;
    void update() override;
    void mostrar() override;
};
