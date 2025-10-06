#include "Arma.h"
#include "../levels/level3/mundo3_tile_control.h"
#include "../Entidad/Entidad.h"

Arma::Arma(int dano, short x, short y, EstructuraEstatica* fondo) {
    this->tipo = 'A';
    this->dano = dano;
    this->cantidad = 1;

    this->dialogo = new EstructuraDinamica(x, y, fondo);
    this->dialogo->loadMap("assets/arma_dialogo.txt", tile_control::ItemDialogoCharToTile);
}

bool Arma::colision(short& entityX, short& entityY, Entidad* entity) {
    if (this->ascii == nullptr) return false;

    EstructuraDinamica* armaEstructura = this->ascii;

    short armaX = armaEstructura->getPosX();
    short armaY = armaEstructura->getPosY();

    bool colisionDetectada =
        armaX < entityX + entity->getCuerpo()->getAncho() &&
        armaX + armaEstructura->getAncho() > entityX &&
        armaY < entityY + entity->getCuerpo()->getAlto() &&
        armaY + armaEstructura->getAlto() > entityY;

    if (colisionDetectada) {
        if (entity->getTipo() == "jugador" && this->dialogo != nullptr) this->dialogo->render();
        return true;
    }
    else {
        if (this->dialogo != nullptr) this->dialogo->borrar();
        return false;
    }
}
