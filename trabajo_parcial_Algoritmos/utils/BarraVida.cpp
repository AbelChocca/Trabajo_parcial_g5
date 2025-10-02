#include "BarraVida.h"
#include "../core/Map.h"


BarraVida::BarraVida()
{
	this->vida = 100;
	this->posX = 165;
	this->posY = 18;
}

BarraVida::~BarraVida()
{
}

void BarraVida::actualizarBarra(short& daño) {
	this->vida -= daño;
	this->renderizarBarra();
}
void BarraVida::renderizarBarra() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < this->vida; j+= 10) {
			int x = this->posX + (j % 10);
			int y = this->posY + i;

			Console::SetCursorPosition(x, y);
			Console::ForegroundColor = ConsoleColor::Green;
			Console::Write(L'█');
		}
	}
	Console::ForegroundColor = ConsoleColor::White;
}