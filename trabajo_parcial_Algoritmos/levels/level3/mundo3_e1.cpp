#include "mundo3_e1.h"
#include "../../core/Map.h"
#include "../../core/Config.h"

Tile E1CharToTile(char c);
Tile DialogCharToTile(char c);

Mundo3Escenario1::Mundo3Escenario1(bool* mostrar_dialogo)
{
	this->mostrar_dialogo = mostrar_dialogo;
	this->fondo = new EstructuraEstatica(0, 0);
	this->fondo->loadMap("assets/mundo3_e1.txt", E1CharToTile);
	this->indice_mensaje = 0;
	this->completado = false;

	// Dialogos
	EstructuraEstatica* dialogo1 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo2 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo3 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo4 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo5 = new EstructuraEstatica(25, 40);

	dialogo1->loadMap("assets/mundo3_dialogo1.txt", DialogCharToTile);
	dialogo2->loadMap("assets/mundo3_dialogo2.txt", DialogCharToTile);
	dialogo3->loadMap("assets/mundo3_dialogo3.txt", DialogCharToTile);
	dialogo4->loadMap("assets/mundo3_dialogo4.txt", DialogCharToTile);
	dialogo5->loadMap("assets/mundo3_dialogo5.txt", DialogCharToTile);

	this->mensajes.push_back(dialogo1);
	this->mensajes.push_back(dialogo2);
	this->mensajes.push_back(dialogo3);
	this->mensajes.push_back(dialogo4);
	this->mensajes.push_back(dialogo5);
}

Mundo3Escenario1::~Mundo3Escenario1()
{
}
short Mundo3Escenario1::getAncho() {
	return this->fondo->getAncho();
}
short Mundo3Escenario1::getAlto() {
	return this->fondo->getAlto();
}
void Mundo3Escenario1::mostrar() {
	Console::Clear();

	if (this->fondo) {
		this->fondo->render();
	}
	if (!this->mensajes.empty()) this->mostrarDialogo();
}
void Mundo3Escenario1::setJugador(EstructuraDinamica* jugador) {
	this->jugador = jugador;
}
void Mundo3Escenario1::mostrarDialogo() {
	this->mensajes[this->indice_mensaje]->render();
}

void Mundo3Escenario1::update() {
	if (this->fondo) this->fondo->render();
	if (this->jugador) this->jugador->render();
}
void Mundo3Escenario1::handleDialog(char tecla) {
	switch (tecla)
	{
	case 13:
		this->indice_mensaje++;
		if (this->indice_mensaje >= 5) {
			*this->mostrar_dialogo = false;
			this->update();
			return;
		}
		this->mostrarDialogo();
		break;
	default:
		break;
	}
}

void Mundo3Escenario1::setCompletado() {
	this->completado = true;
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
	case ' ':
		t.bloque = L'█';
		t.color = ConsoleColor::Black;
		break;
	default:
		t.bloque = c;
		t.color = ConsoleColor::White;
		break;
	}
	return t;
}