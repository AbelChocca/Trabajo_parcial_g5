#pragma once
#include "../../core/GameState.h"
#include <vector>
#include <string>

class EstructuraEstatica;
class EstructuraDinamica;
struct Tile;
typedef Tile(*CharToTileFunc)(char);

class Mundo3 : public GameState
{
private:
	EstructuraDinamica* jugador;
	GameState* escenarioActual;
	std::vector<std::vector<std::vector<Tile>>> sprites_jugador;
	short frame_actual;
public:
	Mundo3();
	~Mundo3();

	void Mundo3::cargarFrame(const std::string& archivo);
	void Mundo3::inicializarJugador();

	void handleInput(Game* game, char tecla) override;
	void update() override;
	void mostrar() override;
};