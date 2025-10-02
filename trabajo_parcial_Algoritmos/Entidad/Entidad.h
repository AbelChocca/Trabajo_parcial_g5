#pragma once
#include "../core/Map.h"

struct Nodo {
	int x, y;
};

class Entidad
{
protected:
	EstructuraDinamica* cuerpo;

public:
	virtual ~Entidad() = default;

	virtual void render() {
		this->cuerpo->render();
	}
};