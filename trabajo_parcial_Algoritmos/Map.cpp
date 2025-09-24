#include "Map.h"

Estructura::Estructura(short x, short y) : posX(x), posY(y), ancho(0), alto(0) {
    grafico = new Tile * [MAX_HEIGHT];
    for (int i = 0; i < MAX_HEIGHT; i++) {
        grafico[i] = new Tile[MAX_WIDTH];
    }
}

Estructura::~Estructura() {
    for (int i = 0; i < MAX_HEIGHT; i++) {
        delete[] grafico[i];
    }
    delete[] grafico;
}

bool Estructura::loadMap(const std::string& filename, CharToTileFunc charToTile) {
    std::fstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    int row = 0;

    while (getline(file, line) && row < MAX_HEIGHT) {
        this->ancho = line.size();
        for (int col = 0; col < this->ancho && col < MAX_WIDTH; col++) {
            this->grafico[row][col] = charToTile(line[col]);
        }
        row++;
    }
    this->alto = row;

    return true;
}

void Estructura::render() {
    for (int row = 0; row < this->alto; row++) {
        for (int col = 0; col < this->ancho; col++) {
            Tile& t = grafico[row][col];

            Console::SetCursorPosition(this->posX + col, this->posY + row);
            Console::ForegroundColor = t.color;
            Console::Write(t.bloque);
        }
    }
    Console::ForegroundColor = ConsoleColor::White;
}
