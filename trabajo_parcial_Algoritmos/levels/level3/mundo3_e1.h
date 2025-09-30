#pragma once
#include "../../core/GameState.h"
#include <vector>

class EstructuraEstatica;
class EstructuraDinamica;

class Mundo3Escenario1 : public GameState
{
protected:
	EstructuraEstatica* fondo;
	std::vector<EstructuraEstatica*> mensajes;
	EstructuraDinamica* jugador;
	bool completado;
	short indice_mensaje;
	bool* mostrar_dialogo;
public:
	Mundo3Escenario1(bool* mostrar_dialogo);
	~Mundo3Escenario1();

	EstructuraEstatica* getFondo() { return this->fondo; };

	void mostrarDialogo();
	void setJugador(EstructuraDinamica* jugador);
	void setCompletado();

	void update() override;
	void mostrar() override;
	void handleDialog(char tecla) override;
	short getAncho() override;
	short getAlto() override;
};