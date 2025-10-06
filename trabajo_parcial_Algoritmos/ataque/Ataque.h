#pragma once
class Entidad;
class EstructuraEstatica;

class Ataque
{
protected:
	short daño;
	bool activo;
	short posX;
	short posY;
	short dx;
	short dy;
	EstructuraEstatica* fondo;
public:
	Ataque();
	virtual ~Ataque() {};


	virtual void renderAtaque() = 0;
	virtual void borrarAtaque() = 0;
	virtual void ejecutarAtaque() = 0;
	virtual void reset(short x, short y) = 0;
};