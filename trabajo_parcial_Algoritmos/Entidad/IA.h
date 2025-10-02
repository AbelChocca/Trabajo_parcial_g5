#pragma once
#include "Entidad.h"

using namespace std;

class IA : public Entidad
{
private:
	vector<vector<vector<Tile>>> sprites_IA;
public:
	IA(short x, short y, EstructuraEstatica* fondo);
	~IA();

	EstructuraDinamica* getCuerpo() const { return this->cuerpo; }
	vector<vector<vector<Tile>>>& getSpritesIA() { return this->sprites_IA; }
	void moverIAhaciaDestino(short destinoX, short destinoY);
	bool pasilloValido(short tx, short ty);
};