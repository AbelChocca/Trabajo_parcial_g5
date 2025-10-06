#pragma once
#include "../utils/Item.h"

class Entidad;
class Jugador;

class Arma : public Item
{
protected:
    int dano;        

public:
    Arma(int dano, short x, short y, EstructuraEstatica* fondo);
    ~Arma() = default;

    EstructuraDinamica*& getEstructura() { return this->ascii; }

    bool colision(short& entityX, short& entityY, Entidad* entity) override;
};
