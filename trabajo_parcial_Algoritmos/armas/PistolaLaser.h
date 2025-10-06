#pragma once
#include "Arma.h"
#include "../ataque/Projectil.h"
#include <string>
#include <vector>

class Jugador;

class PistolaLaser : public Arma
{
protected:
	std::vector<Projectil*> projectiles;
public:
	PistolaLaser(
		short x,
		short y,
		short dialogX,
		short dialogY,
		EstructuraEstatica* fondo,
		std::string nombre
	);
	~PistolaLaser();

	void agregarItem(Jugador*& jugador) override;
	void borrarItem() override;
	void usarItem(Jugador*& jugador) override;
	void renderItem() override;
};
