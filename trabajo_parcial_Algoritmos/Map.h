#pragma once
#include "Config.h"
#include <string>

typedef Tile(*CharToTileFunc)(char);

class Estructura {
private:
    short posX;
    short posY;
    size_t ancho;
    short alto;
    Tile** grafico;

public:
    Estructura(short x, short y);
    ~Estructura();

    bool loadMap(const std::string& filename, CharToTileFunc charToTile);
    void render();
};
