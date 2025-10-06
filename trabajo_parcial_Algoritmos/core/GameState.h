#pragma once

class Game;
class EstructuraEstatica;
class EstructuraDinamica;
class Item;
class Jugador;

struct Rect {
    int x, y;
    short ancho, alto;
};

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void handleInput(Game* game, char tecla) {
        return;
    };
    virtual void update() = 0;
    virtual void mostrar() = 0;
    virtual void renderAnimation() {
        return;
    };
    virtual Item* getItemCercano() {
        return nullptr;
    }
    virtual void setItemCercano(Item* item) {
        return;
    }
    virtual void intentaRecojer(Jugador*& jugador) {};
    virtual bool estaCompletado() {
        return false;
    };
    virtual GameState* cambiarEstado() {
        return nullptr;
    }
    virtual bool setColisionCondition(char c, EstructuraDinamica*& entity) {
        return false;
    }

    virtual EstructuraEstatica* getFondo() {
        return nullptr;
    }
    virtual void handleDialog(char tecla) {
        return;
    }
    virtual short getAncho() {
        return 0;
    }
    virtual short getAlto() {
        return 0;
    }
};