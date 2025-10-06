#pragma once
#include "../Entidad/Entidad.h"

class EstructuraDinamica;

class Enemigo : public Entidad
{
private:
	short daño;
	short dx;
	short dy;
public:
	Enemigo(EstructuraDinamica* estructura, short daño);
	~Enemigo();

	EstructuraDinamica* getEstructura() { return this->cuerpo; };
	short& getDx() { return this->dx; }
	short& getDaño() { return this->daño; }
	void setDx(short dx) { this->dx = dx; }


	void recibirDaño(short daño) {};
	void atacar();
	bool detectarColision(EstructuraDinamica* entidad);
};