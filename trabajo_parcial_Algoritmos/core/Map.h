#pragma once
#include "Config.h"
#include <string>
#include <vector>

typedef Tile(*CharToTileFunc)(char);

class Estructura {
protected:
    short posX;
    short posY;
    short ancho;
    short alto;
    Tile** grafico;

public:
    Estructura(short x, short y);
    virtual ~Estructura();

    bool loadMap(const std::string& filename, CharToTileFunc charToTile);

    void render();
    virtual void borrar() = 0;

    short getPosX() const { return this->posX; };
    short getPosY() const { return this->posY; };
    short getAlto() const { return this->alto; };
    short getAncho() const { return this->ancho; };
    Tile** getGrafico() const { return this->grafico; };

    void setPosY(short y) { this->posY = y; };
    void setPosX(short x) { this->posX = x; };
};

class EstructuraEstatica : public Estructura {
public:
    EstructuraEstatica(short x, short y) : Estructura(x, y) {};

    void borrar() override {
        for (int row = 0; row < this->getAlto(); row++) {
            for (int col = 0; col < this->getAncho(); col++) {
                int x = this->getPosX() + col;
                int y = this->getPosY() + row;

                if (x >= 0 && x < MAX_WIDTH && y >= 0 && y < MAX_HEIGHT) {
                    Console::SetCursorPosition(x, y);
                    Console::ForegroundColor = ConsoleColor::Black;
                    Console::Write(" ");
                }
            }
        }
        Console::ForegroundColor = ConsoleColor::White;
    }
};

class EstructuraDinamica : public Estructura {
private:
    EstructuraEstatica* fondo;
public:
    EstructuraDinamica(short x, short y, EstructuraEstatica* f) : Estructura(x, y), fondo(f) {};

    EstructuraEstatica* getFondo() {
        return this->fondo;
    }
    void setFondo(EstructuraEstatica* fondo) {
        this->fondo = fondo;
    }
    void borrar() override {
        for (int row = 0; row < this->getAlto(); row++) {
            for (int col = 0; col < this->getAncho(); col++) {
                int x = this->getPosX() + col;
                int y = this->getPosY() + row;
                if (y >= 0 && y < fondo->getAlto() && x >= 0 && x < fondo->getAncho()) {
                    Tile& t = fondo->getGrafico()[y][x];
                    Console::SetCursorPosition(x, y);
                    Console::ForegroundColor = t.color;
                    Console::Write(t.bloque); // ' '
                }
            }
        }
        Console::ForegroundColor = ConsoleColor::White;
    }

    void setSprite(const std::vector<std::vector<Tile>>& frame) {

        if (this->grafico) {
            for (int i = 0; i < this->alto; i++) {
                delete[] this->grafico[i];
            }
            delete[] this->grafico;
        }


        this->grafico = new Tile * [alto];
        for (int i = 0; i < alto; i++) {
            this->grafico[i] = new Tile[ancho];
            for (int j = 0; j < ancho; j++) {
                this->grafico[i][j] = frame[i][j];
            }
        }
    }


};

