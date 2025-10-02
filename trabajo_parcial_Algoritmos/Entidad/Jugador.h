#pragma once
#include "Entidad.h"
#include "../utils/BarraVida.h"
#include "../utils/Inventario.h"
#include "../core/Config.h"

using namespace std;

class Jugador : public Entidad
{
private:
	BarraVida barra_vida;
	Inventario inventario;
	vector<vector<vector<Tile>>> sprites_jugador;
	short frame_actual;
public:
	Jugador(short x, short y, EstructuraEstatica* fondo);
	~Jugador();

	vector<vector<vector<Tile>>>& getSpritesJugador() { return this->sprites_jugador; };
	EstructuraDinamica* getCuerpo() const { return this->cuerpo; }

	void seleccionarItem();
};