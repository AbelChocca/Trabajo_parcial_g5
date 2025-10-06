#pragma once
#include "../core/Map.h"
#include <string>

struct Nodo {
	int x, y;
};

class Entidad
{
protected:
	EstructuraDinamica* cuerpo;
	std::string tipo;

public:
	virtual ~Entidad() = default;

	std::string& getTipo() { return this->tipo; }
	EstructuraDinamica*& getCuerpo() { return this->cuerpo; }
	virtual void render() {
		this->cuerpo->render();
	}
	virtual void recibirDaño(short daño) = 0;
	virtual char getDireccion() { return 'a'; }
};