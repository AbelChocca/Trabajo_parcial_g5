#pragma once

class EstructuraEstatica;

class BarraVida
{
private:
	short vida;
	short posX;
	short posY;
	short vida_fija;

public:
	BarraVida(short vida, short x, short y);
	~BarraVida();

	short& getVida() { return this->vida; }
	short& getVidaMaxima() { return this->vida_fija; }

	void aumentarVida(short& vida);
	void borrarBarra();
	void actualizarBarra(short& daño);
	void renderizarBarra();
};