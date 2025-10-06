#pragma once
#include "../core/Config.h"
#include <string>
#include <vector>

class EstructuraEstatica;
class EstructuraDinamica;
class Jugador;
class Entidad;

class Item
{
protected:
	short cantidad;
	EstructuraDinamica* ascii;
	EstructuraDinamica* dialogo;
	EstructuraEstatica* inventoryItem;
	std::vector<std::vector<std::vector<Tile>>> sprites_jugador;
	std::string nombre;
	char tipo;
	bool estaColisionando = false;

public:
	virtual ~Item() { };

	std::vector<std::vector<std::vector<Tile>>>& getSprites() { return this->sprites_jugador; }
	EstructuraDinamica*& getDialogo() { return this->dialogo; }
	EstructuraEstatica*& getInventoryItem() {
		return this->inventoryItem;
	};
	std::string& getNombre() { return this->nombre; }
	char& getTipo() { return this->tipo; }

	virtual void borrarItem() = 0;
	virtual void agregarItem(Jugador*& jugador) = 0;
	virtual void renderItem() = 0;
	virtual void usarItem(Jugador*& jugador) = 0;
	virtual bool colision(short& entityX, short& entityY, Entidad* entity) = 0;
};