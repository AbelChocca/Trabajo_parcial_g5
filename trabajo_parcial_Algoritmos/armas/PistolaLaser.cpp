#include "PistolaLaser.h"
#include "../core/Map.h"
#include "../levels/level3/mundo3_tile_control.h"
#include "../core/UtilsFunc.h"
#include "../Entidad/Jugador.h"
#include "../ataque/Projectil.h"

PistolaLaser::PistolaLaser(
	short x,
	short y,
	short dialogX,
	short dialogY,
	EstructuraEstatica* fondo,
	std::string nombre
) : Arma(20, dialogX, dialogY, fondo) {
	this->nombre = nombre;
	this->ascii = new EstructuraDinamica(x, y, fondo);
	this->ascii->loadMap("assets/pistolaLaser_frame.txt", tile_control::PistolaLaserCharToTile);
	this->inventoryItem = new EstructuraEstatica(154, 42);
	this->inventoryItem->loadMap("assets/pistola_laser.txt", tile_control::PistolaLaserCharToTile);

	FrameLoader::cargarFrame(this->sprites_jugador, "assets/jugador_pistolarLaser.txt", tile_control::JugadorConPistolaLaserCharToTile);
	FrameLoader::cargarFrame(this->sprites_jugador, "assets/jugador_pistolarLaser2.txt", tile_control::JugadorConPistolaLaserCharToTile);
	FrameLoader::cargarFrame(this->sprites_jugador, "assets/jugador_pistolarLaser3.txt", tile_control::JugadorConPistolaLaserCharToTile);
}

PistolaLaser::~PistolaLaser() {
	delete this->ascii;
}
void PistolaLaser::usarItem(Jugador*& jugador) {
	if (this->projectiles.empty()) return;
	for (size_t i = 0; i < this->projectiles.size(); ) {
		Projectil*& projectil = this->projectiles[i];
		projectil->ejecutarAtaque();

		if (!projectil->estaActivo()) {
			delete projectil;
			this->projectiles.erase(this->projectiles.begin() + i);
		}
		else {
			++i;
		}
	}
}

void PistolaLaser::agregarItem(Jugador*& jugador) {
	// Aquí puedes agregar la lógica para disparar o aumentar daño
	EstructuraDinamica* cuerpo = jugador->getCuerpo();
	short ancho = cuerpo->getAncho();
	short alto = cuerpo->getAlto();
	short x = cuerpo->getPosX();
	short y = cuerpo->getPosY();
	char c = jugador->getDireccion();
	switch (c)
	{
	case 'd':
		this->projectiles.push_back(new Projectil(x + ancho, y + (alto / 2), cuerpo->getFondo(), 1));
		break;
	case 'a':
		this->projectiles.push_back(new Projectil(x, y + (alto / 2), cuerpo->getFondo(), -1));
		break;
	}
	return;
}

void PistolaLaser::renderItem() {
	this->ascii->render();
}

void PistolaLaser::borrarItem() {
	this->ascii->borrar();
}
