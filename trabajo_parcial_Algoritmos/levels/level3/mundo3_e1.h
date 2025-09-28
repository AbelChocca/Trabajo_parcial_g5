#pragma once
#include "../../core/GameState.h"
#include <vector>

class EstructuraEstatica;

class Mundo3Escenario1 : public GameState
{
protected:
	EstructuraEstatica* fondo;
	std::vector<EstructuraEstatica*> mensajes;
	short indice_mensaje;
	bool mostrar_dialogo;
public:
	Mundo3Escenario1();
	~Mundo3Escenario1();

	EstructuraEstatica* getFondo() { return this->fondo; };

	void handleMensajes(char tecla);
	void mostrarDialogo();

	void handleInput(Game* game, char tecla) override;
	void update() override;
	void mostrar() override;
};