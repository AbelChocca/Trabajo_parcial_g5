#pragma once
#include "../../core/GameState.h"
#include <vector>

class Jugador;
class IA;
class EstructuraEstatica;
class EstructuraDinamica;

class Mundo1Escenario1 : public GameState
{
protected:
	EstructuraEstatica* fondo;
	std::vector<EstructuraEstatica*> mensajes;
	Jugador* jugadorEntity;
	IA* IAEntity;
	Rect puntoFinal;
	short indice_mensaje;
	bool* mostrar_dialogo;
	bool* guardarIA;
public:
	Mundo1Escenario1(bool* mostrar_dialogo, bool* guardarIA);
	~Mundo1Escenario1();

	void mostrarDialogo();
	void setJugador(Jugador* jugador);
	void setIA(IA* ia);

	bool setColisionCondition(char c, EstructuraDinamica*& entity) override;
	GameState* cambiarEstado() override;
	bool estaCompletado() override;
	EstructuraEstatica* getFondo() override;
	void update() override;
	void mostrar() override;
	void handleDialog(char tecla) override;
	short getAncho() override;
	short getAlto() override;
};