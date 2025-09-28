#pragma once
#include "../core/Map.h"
#include "../core/GameState.h"

const int POSY_INPUT = 22;
const int POSX_INPUT = 39;

class Game;

class Menu : public GameState {
private:
    EstructuraEstatica* layout;
    EstructuraDinamica* input;
    int opcionSeleccionada;

public:
    Menu();
    ~Menu();

    int getOpcion() const { return this->opcionSeleccionada; };
    EstructuraDinamica* getInput() const { return this->input; };

    void setOpcion(int opcion) { this->opcionSeleccionada = opcion; };

    void handleInput(Game* game, char tecla) override;
    void mostrar() override;
    void update() override;
};


Tile MenuCharToTile(char c);
