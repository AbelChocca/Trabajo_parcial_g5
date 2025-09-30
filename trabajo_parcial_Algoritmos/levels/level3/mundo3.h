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
	EstructuraDinamica* IA;
	GameState* escenarioActual;
	std::vector<std::vector<std::vector<Tile>>> sprites_jugador;
	short frame_actual;
	bool mostrar_dialogo;
public:
	Mundo3();
	~Mundo3();

	void Mundo3::cargarFrame(const std::string& archivo);
	void Mundo3::inicializarPersonajes();
	void Mundo3::mover(char c);
	bool Mundo3::esValido(int x, int y);

	void handleInput(Game* game, char tecla) override;
	void update() override;
	void mostrar() override;
};