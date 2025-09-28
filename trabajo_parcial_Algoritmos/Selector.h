#pragma once
#include "GameState.h"
class EstructuraEstatica;
class EstructuraDinamica;

class Selector : public GameState
{
private:
	EstructuraEstatica* fondo;
	EstructuraDinamica* input;
	short selectedOption;

public:
	Selector();
	~Selector();

	void setOption(short newOption);

	void handleInput(Game* game, char tecla) override;
	void update() override;
	void mostrar() override;
};