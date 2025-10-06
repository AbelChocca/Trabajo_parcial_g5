#pragma once
#include "../Entidad/Entidad.h"

class EstructuraDinamica;

class Enemigo : public Entidad
{
private:
	short da�o;
	short dx;
	short dy;
public:
	Enemigo(EstructuraDinamica* estructura, short da�o);
	~Enemigo();

	EstructuraDinamica* getEstructura() { return this->cuerpo; };
	short& getDx() { return this->dx; }
	short& getDa�o() { return this->da�o; }
	void setDx(short dx) { this->dx = dx; }


	void recibirDa�o(short da�o) {};
	void atacar();
	bool detectarColision(EstructuraDinamica* entidad);
};