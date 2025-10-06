#include "Projectil.h"
#include "../Entidad/Entidad.h"

Projectil::Projectil(short x, short y, EstructuraEstatica* fondo, short dx) {
	this->daño = 20;
	this->dx = dx;
	this->posX = x;
	this->posY = y;
	this->fondo = fondo;
}
Projectil::~Projectil() {
}

bool Projectil::estaActivo() {
	return this->activo;
}
void Projectil::renderAtaque() {
	if (!this->activo) return;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			short posX = this->posX + j;
			short posY = this->posY + i;

			if (posX >= 0 && posX < this->fondo->getAncho() &&
				posY >= 0 && posY < this->fondo->getAlto()) {
				Console::SetCursorPosition(posX, posY);
				Console::ForegroundColor = ConsoleColor::Cyan;
				Console::Write(L'█');
			}
		}
	}
	Console::ForegroundColor = ConsoleColor::White;
}
void Projectil::borrarAtaque() {
	if (!this->activo) return;
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 3; j++) {
			short posX = this->posX + j;
			short posY = this->posY + i;
			wchar_t& bloque = this->fondo->getGrafico()[posY][posX].bloque;

			if (posX >= 0 && posX < this->fondo->getAncho() &&
				posY >= 0 && posY < this->fondo->getAlto()) {
				Console::SetCursorPosition(posX, posY);
				Console::ForegroundColor = ConsoleColor::Black;
				Console::Write(bloque);
			}
		}
	}
	Console::ForegroundColor = ConsoleColor::White;
}
void Projectil::ejecutarAtaque() {
	this->borrarAtaque();

	this->posX += dx;

	if (this->posX < 0 || this->posX >= this->fondo->getAncho() - 3 ||
		this->posY < 0 || this->posY >= this->fondo->getAlto()) {
		this->activo = false;
		return;
	}

	if (this->fondo->getGrafico()[this->posY][this->posX].isSolid) {
		this->activo = false;
		return;
	}

	// PARA EL JEFE
	//if (posX >= objetivo->getCuerpo()->getPosX() &&
	//	posX < objetivo->getCuerpo()->getPosX() + objetivo->getCuerpo()->getAncho() &&
	//	posY >= objetivo->getCuerpo()->getPosY() &&
	//	posY < objetivo->getCuerpo()->getPosY() + objetivo->getCuerpo()->getAlto()) {
	//	activo = false;
	//	objetivo->rec

	
	this->renderAtaque();
}