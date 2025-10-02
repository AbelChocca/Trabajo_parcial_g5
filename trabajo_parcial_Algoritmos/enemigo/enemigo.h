#pragma once

class EstructuraDinamica;

class Enemigo
{
private:
	EstructuraDinamica* estructura;
	short dx;
	short dy;
public:
	Enemigo(EstructuraDinamica* estructura);
	~Enemigo();

	EstructuraDinamica* getEstructura() { return this->estructura; };
	short getDx() { return this->dx; }

	void atacar();
	bool detectarColision(EstructuraDinamica* entidad);
};