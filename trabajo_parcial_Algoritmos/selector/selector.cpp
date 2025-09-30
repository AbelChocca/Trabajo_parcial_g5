#include "Selector.h"
#include "../core/Game.h"
#include "../levels/level3/mundo3.h"

Tile SelectorCharToTile(char c);
Tile InputSelectorCharToTile(char c);

Selector::Selector() {
	this->fondo = new EstructuraEstatica(0, 0);
	this->fondo->loadMap("assets/selector.txt", SelectorCharToTile);
	this->input = new EstructuraDinamica(4, 16, fondo);
	this->input->loadMap("assets/input_selector.txt", InputSelectorCharToTile);
	this->selectedOption = 0;
};
Selector::~Selector() {

}

void Selector::setOption(short newOption) {
	this->selectedOption = newOption;
}
void Selector::handleInput(Game* game, char tecla) {
	switch (tecla)
	{
	case '1':
		this->setOption(0);
		this->input->borrar();
		this->input->setPosX(4);
		break;
	case '2':
		this->setOption(1);
		this->input->borrar();
		this->input->setPosX(54);
		break;
	case '3':
		this->setOption(2);
		this->input->borrar();
		this->input->setPosX(104);
		break;
	case 'q':
	case 'Q':
		game->setState(new Menu());
		return;
		break;
	case 13:
		switch (this->selectedOption)
		{
		case 0:
			break;
		case 1:

			break;
		case 2:
			game->setState(new Mundo3());
			return;
			break;
		default:
			break;
		}
	default:
		break;
	}
	this->input->render();
};
void Selector::update() {

};
void Selector::mostrar() {
	Console::Clear();

	if (this->fondo) {
		this->fondo->render();
	}

	if (this->input) this->input->render();

};

Tile InputSelectorCharToTile(char c) {
	Tile t;

	switch (c)
	{
	case '*':
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
	}
	return t;
}

Tile SelectorCharToTile(char c) {
	Tile t;

	switch (c)
	{
	case '*':
	case '#':
		t.bloque = L'█';
		t.color = ConsoleColor::White;
		break;
	case ' ':
		t.bloque = L' ';
		t.color = ConsoleColor::Black;
		break;
	default:
		t.bloque = c;
		t.color = ConsoleColor::Black;
	}

	return t;
}