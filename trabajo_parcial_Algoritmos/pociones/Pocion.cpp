#include "Pocion.h"
#include "../Entidad/Entidad.h"
#include "../levels/level3/mundo3_tile_control.h"

Pocion::Pocion(std::string e, short x, short y, EstructuraEstatica* fondo) {
	this->efecto = e;
	this->cantidad = 1;
    this->tipo = 'P';
	this->dialogo = new EstructuraDinamica(x, y, fondo);
	this->dialogo->loadMap("assets/pocion_dialogo.txt", tile_control::ItemDialogoCharToTile);
}

bool Pocion::colision(short& entityX, short& entityY, Entidad* entity) {
	EstructuraDinamica* pocionEstructura = this->ascii;

	short pocionX = pocionEstructura->getPosX();
	short pocionY = pocionEstructura->getPosY();

    bool colisionDetectada =
        pocionX < entityX + entity->getCuerpo()->getAncho() &&
        pocionX + pocionEstructura->getAncho() > entityX &&
        pocionY < entityY + entity->getCuerpo()->getAlto() &&
        pocionY + pocionEstructura->getAlto() > entityY;

    if (colisionDetectada) {
        if (entity->getTipo() == "jugador" && this->dialogo != nullptr) this->dialogo->render();
        return true;
    }
    else {
        if (this->dialogo != nullptr) this->dialogo->borrar();
        return false;
    }

}