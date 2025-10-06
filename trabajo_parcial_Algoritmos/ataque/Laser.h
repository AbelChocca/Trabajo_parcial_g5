#pragma once
#include "Ataque.h"
#include "../Entidad/Entidad.h"

struct NodoLaser { short x, y; };

class Laser : public Ataque
{
private:
	Entidad* objetivo;
	std::vector<NodoLaser> recorrido;
	size_t pasoActual = 0;
public:
	Laser(EstructuraEstatica* fondo, Entidad* origen, Entidad* objetivo);
	~Laser();

	void renderAtaque() override;
	void borrarAtaque() override;
	void ejecutarAtaque() override;
	void reset(short x, short y) override {};

	bool estaActivo() const { return activo; }
};
