#pragma once
#include "../../core/GameState.h"
#include "../../enemigo/enemigo.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"
#include <vector>

using namespace std;

class EstructuraEstatica;
class EstructuraDinamica;
class Item;

class Mundo3Escenario2 : public GameState
{
private:
	EstructuraEstatica* fondo;
	vector<EstructuraEstatica*> mensajes;
	vector<Enemigo*> enemigos;
	Jugador* jugadorEntity;
	IA* IAEntity;
	Item* pistola;
	Item* itemCercano = nullptr;
	short indice_mensaje;
	bool* mostrar_dialogo;
	bool* guardarIA;
	bool dialogo_activo = true;
	bool dialogo1_mostrado = false;
	bool dialogo2_mostrado = false;
	Rect primerPunto;
	Rect puntoFinal;
public:
	Mundo3Escenario2(
		bool* mostrar_dialogo, 
		bool* guardarIA, 
		Jugador* jugador,
		IA* IA
	);
	~Mundo3Escenario2();

	void mostrarDialogo();
	bool colisionPrimerPunto();
	void mandarAlInicio();

	Item* getItemCercano() override;
	void setItemCercano(Item* item) override;
	void intentaRecojer(Jugador*& jugador) override;
	void renderAnimation() override;
	bool setColisionCondition(char c, EstructuraDinamica*& entity) override;
	EstructuraEstatica* getFondo() override;
	void update() override;
	void mostrar() override;
	void handleDialog(char tecla) override;
	bool estaCompletado();
	GameState* cambiarEstado() override;
	short getAncho() override;
	short getAlto() override;
};