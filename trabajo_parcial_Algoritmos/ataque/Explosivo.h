#pragma once
#include "Ataque.h"
#include "../Entidad/Entidad.h"
#include <vector>
#include <queue>

struct NodoExplosivo { short x, y; };

class Explosivo : public Ataque {
private:
    Entidad* objetivo;
    std::vector<EstructuraDinamica*> spritesExplosion;
    int indiceSprite;
    bool explotando;
    std::vector<NodoExplosivo> camino;
    size_t pasoActual;

public:
    Explosivo(short x, short y, EstructuraEstatica* fondo, Entidad* objetivo);
    ~Explosivo();

    void renderAtaque() override;
    void borrarAtaque() override;
    void ejecutarAtaque() override;
    void reset(short x, short y) override;

private:
    void explotar();   
    void calcularBFS();
};
