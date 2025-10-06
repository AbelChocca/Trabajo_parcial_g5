#include "BarraVida.h"
#include "../core/Map.h"


BarraVida::BarraVida(short vida, short x, short y)
{
	this->vida = vida;
	this->posX = x;
	this->posY = y;
	this->vida_fija = vida;
}

BarraVida::~BarraVida()
{
}

void BarraVida::borrarBarra() {
	short bloques = this->vida_fija / 10;
	Console::ForegroundColor = ConsoleColor::Black;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < bloques; j++) {
			int x = this->posX + j;
			int y = this->posY + i;

			Console::SetCursorPosition(x, y);
			Console::Write(L' ');
		}
	}
	Console::ForegroundColor = ConsoleColor::White;
}
void BarraVida::aumentarVida(short& vida) {
	this->borrarBarra();
	this->vida += vida;
	this->renderizarBarra();
}
void BarraVida::actualizarBarra(short& daño) {
	this->borrarBarra();
	this->vida -= daño;
	this->renderizarBarra();
}
void BarraVida::renderizarBarra() {
	short bloques = this->vida / 10;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < bloques; j++) {
			int x = this->posX + j;
			int y = this->posY + i;

			Console::SetCursorPosition(x, y);
			Console::ForegroundColor = ConsoleColor::Green;
			Console::Write(L'█');
		}
	}
	Console::ForegroundColor = ConsoleColor::White;
}