#include "mundo3_e1.h"
#include "../../core/Map.h"

Tile E1CharToTile(char c);
Tile DialogCharToTile(char c);

Mundo3Escenario1::Mundo3Escenario1()
{
	this->fondo = new EstructuraEstatica(0, 0);
	this->fondo->loadMap("assets/mundo3_e1.txt", E1CharToTile);
	this->mostrar_dialogo = true;

	// Dialogos
	EstructuraEstatica* dialogo1 = new EstructuraEstatica(15, 45);
	dialogo1->loadMap("assets/mundo3_dialogo1.txt", DialogCharToTile);

	this->mensajes.push_back(dialogo1);
}

Mundo3Escenario1::~Mundo3Escenario1()
{
}

void Mundo3Escenario1::mostrar() {
	Console::Clear();

	if (this->fondo) {
		this->fondo->render();
	}
}
void Mundo3Escenario1::mostrarDialogo() {
	this->mensajes[this->indice_mensaje]->render();
}
void Mundo3Escenario1::handleInput(Game* game, char c) {
	if (this->mostrar_dialogo) this->handleMensajes(c);
	else {
		switch (c)
		{
		case 'd':
			break;

		default:
			break;
		}
	}
}
void Mundo3Escenario1::update() {
	if (this->fondo) this->fondo->render();
}
void Mundo3Escenario1::handleMensajes(char tecla) {
	switch (tecla)
	{
	case 13:
		break;
	default:
		break;
	}
}

Tile E1CharToTile(char c) {
	Tile t;
	switch (c)
	{
	case '*':
		t.bloque = L'█';
		t.color = ConsoleColor::DarkGray;
		break;
	case '#':
		t.bloque = L'█';
		t.color = ConsoleColor::DarkCyan;
		break;
	case ' ':
		t.bloque = L' ';
		t.color = ConsoleColor::Black;
		break;
	default:
		t.bloque = c;
		t.color = ConsoleColor::Black;
		break;
	}

	return t;
}
Tile DialogCharToTile(char c) {
	Tile t;
	switch (c)
	{
	case '*':
		t.bloque = L'█';
		t.color = ConsoleColor::White;
		break;
	default:
		t.bloque = c;
		t.color = ConsoleColor::White;
		break;
	}
	return t;
}