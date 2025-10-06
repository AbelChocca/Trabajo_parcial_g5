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
	char direccion_actual;
public:
	Jugador(short x, short y, EstructuraEstatica* fondo);
	~Jugador();

	char getDireccion() override { return this->direccion_actual; }
	Inventario& getInventario() { return this->inventario; }
	vector<vector<vector<Tile>>>& getSpritesJugador() { return this->sprites_jugador; };
	EstructuraDinamica* getCuerpo() const { return this->cuerpo; }
	BarraVida& getBarraVida() { return this->barra_vida; }

	void recibirDaño(short daño) override {
		this->barra_vida.actualizarBarra(daño);
	};
	void setDireccion(char dir) { this->direccion_actual = dir; }
	void seleccionarItem();
	void setSpriteDireccion(EstructuraDinamica* cuerpo, short dirIndex);
};