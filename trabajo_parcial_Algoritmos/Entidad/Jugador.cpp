#include "Jugador.h"
#include "../levels/level3/mundo3_tile_control.h"

Jugador::Jugador(short x, short y, EstructuraEstatica* fondo) {
	this->frame_actual = 0;
	EstructuraDinamica* estructura = new EstructuraDinamica(x, y, fondo);
	estructura->loadMap("assets/personaje_sprite1.txt", tile_control::CharacterCharToTile);
	this->cuerpo = estructura;
}

Jugador::~Jugador() {

}

void Jugador::seleccionarItem() {
	return;
}