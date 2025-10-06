#pragma once
#include "../../core/GameState.h"
#include <vector>

class Item;
class Jugador;
class IA;
class EstructuraEstatica;
class EstructuraDinamica;

class Mundo3Escenario1 : public GameState
{
protected:
	EstructuraEstatica* fondo;
	std::vector<EstructuraEstatica*> mensajes;
	Jugador* jugadorEntity;
	IA* IAEntity;
	Item* pocion;
	Item* itemCercano = nullptr;
	Rect puntoFinal;
	short indice_mensaje;
	bool* mostrar_dialogo;
	bool* guardarIA;
public:
	Mundo3Escenario1(bool* mostrar_dialogo, bool* guardarIA);
	~Mundo3Escenario1();

	void mostrarDialogo();
	void setJugador(Jugador* jugador);
	void setIA(IA* ia);

	void intentaRecojer(Jugador*& jugador) override;
	Item* getItemCercano() override;
	void setItemCercano(Item* item) override;
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