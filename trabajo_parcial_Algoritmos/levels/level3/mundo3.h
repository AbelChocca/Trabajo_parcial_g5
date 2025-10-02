#pragma once
#include "../../core/GameState.h"
#include <vector>
#include <string>

using namespace std;

class EstructuraEstatica;
class EstructuraDinamica;
class Jugador;
class IA;
struct Tile;
typedef Tile(*CharToTileFunc)(char);

class Mundo3 : public GameState
{
private:
	Jugador* jugadorEntity;
	IA* IAEntity;
	EstructuraEstatica* panel_control;
	GameState* escenarioActual;
	short frame_actual;
	bool mostrar_dialogo;
	bool guardarIA; 
public:
	Mundo3();
	~Mundo3();

	void cargarFrame(vector<vector<vector<Tile>>>& sprites, const string& archivo, CharToTileFunc charToTile);
	void mover(char c);
	bool esValidoTile(int tx, int ty);

	void renderAnimation() override;
	void handleInput(Game* game, char tecla) override;
	void update() override;
	void mostrar() override;
};