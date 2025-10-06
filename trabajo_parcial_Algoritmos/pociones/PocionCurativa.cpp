#include "PocionCurativa.h"
#include "../core/Map.h"
#include "../levels/level3/mundo3_tile_control.h"
#include "../Entidad/Jugador.h"

PocionCurativa::PocionCurativa(
	short x, 
	short y,
	short dialogX,
	short dialogY,
	EstructuraEstatica* fondo,
	std::string nombre
) : Pocion("curacion", dialogX, dialogY, fondo) {
	this->curacion = 30;
	this->nombre = nombre;
	this->ascii = new EstructuraDinamica(x, y, fondo);
	this->ascii->loadMap("assets/pocionCurativa_frame.txt", tile_control::PCurativaCharToTile);
	this->inventoryItem = new EstructuraEstatica(154, 42);
	this->inventoryItem->loadMap("assets/pocion_curativa.txt", tile_control::PCurativaCharToTile);
}

PocionCurativa::~PocionCurativa() {
	delete this->ascii;
}

void PocionCurativa::agregarItem(Jugador*& jugador) {
	return;
}

void PocionCurativa::usarItem(Jugador*& jugador) {
	jugador->getBarraVida().aumentarVida(this->curacion);
	return;
};
void PocionCurativa::renderItem() {
	this->ascii->render();
};
void PocionCurativa::borrarItem() {
	this->ascii->borrar();
}