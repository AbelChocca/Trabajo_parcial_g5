#pragma once
#include "../utils/Item.h"

class Entidad;

class Pocion : public Item
{
protected:
	std::string efecto;
public:
	Pocion(std::string e, short x, short y, EstructuraEstatica* fondo);
	~Pocion() = default;

	EstructuraDinamica*& getEstructura() { return this->ascii; };

	bool colision(short& entityX, short& entityY, Entidad* entity) override;
};
