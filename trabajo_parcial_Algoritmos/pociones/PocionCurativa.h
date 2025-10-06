#pragma once
#include "Pocion.h"
#include <string>

class PocionCurativa : public Pocion
{
private:
	short curacion;
public:
	PocionCurativa(
		short x,
		short y,
		short dialogX,
		short dialogY,
		EstructuraEstatica* fondo,
		std::string nombre
	);
	~PocionCurativa();
		
	void agregarItem(Jugador*& jugador) override;
	void borrarItem() override;
	void usarItem(Jugador*& jugador) override;
	void renderItem() override;
};