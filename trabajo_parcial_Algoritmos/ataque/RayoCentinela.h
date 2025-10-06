#pragma once
#include "Ataque.h"
#include "../Entidad/Entidad.h"
#include <vector>

struct NodoCentinela {
    short x, y;
};

class RayoCentinela : public Ataque
{
private:
    Entidad* objetivo;
    std::vector<NodoCentinela> recorrido;
    size_t pasoActual;

    void calcularBFS();
public:
    RayoCentinela(short x, short y, EstructuraEstatica* fondo, Entidad* objetivo);
    ~RayoCentinela();

    void reset(short x, short y) override;
    void renderAtaque() override;
    void borrarAtaque() override;
    void ejecutarAtaque() override;
};
