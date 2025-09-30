#pragma once

class Game;
class EstructuraEstatica;

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void handleInput(Game* game, char tecla) {
        return;
    };
    virtual void update() = 0;
    virtual void mostrar() = 0;

    virtual void handleDialog(char tecla) {
        return;
    }
    virtual short getAncho() {
        return;
    }
    virtual short getAlto() {
        return;
    }
};