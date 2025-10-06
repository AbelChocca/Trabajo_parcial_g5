#pragma once
#include "Ataque.h"

class EstructuraDinamica;

class Projectil : public Ataque
{
private:
public:
	Projectil(short x, short y, EstructuraEstatica* fondo, short dx);
	~Projectil();

	void reset(short x, short y) override {};
	bool estaActivo();
	void renderAtaque() override;
	void borrarAtaque() override;
	void ejecutarAtaque() override;
};
