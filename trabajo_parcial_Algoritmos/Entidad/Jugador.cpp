#include "Jugador.h"
#include "../levels/level3/mundo3_tile_control.h"
#include "../utils/Item.h"

Jugador::Jugador(short x, short y, EstructuraEstatica* fondo) : barra_vida(190, 155, 18) {
	this->frame_actual = 0;
	EstructuraDinamica* estructura = new EstructuraDinamica(x, y, fondo);
	estructura->loadMap("assets/personaje_sprite1.txt", tile_control::CharacterCharToTile);
	this->cuerpo = estructura;
    this->tipo = "jugador";
}

Jugador::~Jugador() {

}

void Jugador::seleccionarItem() {
	return;
}
void Jugador::setSpriteDireccion(EstructuraDinamica* cuerpo, short dirIndex) {
    Inventario& inv = this->inventario;
    Item*& item = inv.getItemEquipado();
    if (inv.hayItemEquipado() && item != nullptr) {
        cuerpo->setSprite(item->getSprites()[dirIndex]);
    }
    else {
        cuerpo->setSprite(this->getSpritesJugador()[dirIndex]);
    }
}