#include "Mundo1Escenario1.h"
#include "Mundo1Escenario2.h"
#include "../../core/Map.h"
#include "../../core/Config.h"
#include "mundo1_tile_control.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"
#include "../../core/GameState.h"

Mundo1Escenario1::Mundo1Escenario1(
	bool* mostrar_dialogo,
	bool* guardarIA
)
{
	this->mostrar_dialogo = mostrar_dialogo;
	this->guardarIA = guardarIA;
	this->fondo = new EstructuraEstatica(0, 0);
	this->fondo->loadMap("mundo1_1.txt", tile_control::E1CharToTile);
	this->indice_mensaje = 0;
	this->puntoFinal = { this->fondo->getAncho() - 20, 35, 20, 15 };

	// Dialogos
	EstructuraEstatica* dialogo1 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo2 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo3 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo4 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo5 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo6 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo7 = new EstructuraEstatica(25, 40);

	dialogo1->loadMap("mundo1_dialogo1.txt", tile_control::Dialog1CharToTile);
	dialogo2->loadMap("mundo1_dialogo2.txt", tile_control::Dialog1CharToTile);
	dialogo3->loadMap("mundo1_dialogo3.txt", tile_control::Dialog1CharToTile);
	dialogo4->loadMap("mundo1_dialogo4.txt", tile_control::Dialog1CharToTile);
	dialogo5->loadMap("mundo1_dialogo5.txt", tile_control::Dialog1CharToTile);
	dialogo6->loadMap("mundo1_dialogo6.txt", tile_control::Dialog1CharToTile);
	dialogo7->loadMap("mundo1_dialogo7.txt", tile_control::Dialog1CharToTile);

	this->mensajes.push_back(dialogo1);
	this->mensajes.push_back(dialogo2);
	this->mensajes.push_back(dialogo3);
	this->mensajes.push_back(dialogo4);
	this->mensajes.push_back(dialogo5);
	this->mensajes.push_back(dialogo6);
	this->mensajes.push_back(dialogo7);
}

Mundo1Escenario1::~Mundo1Escenario1()
{
	for (auto& mensaje : this->mensajes) {
		delete mensaje;
	}
	delete this->fondo;
}
short Mundo1Escenario1::getAncho() {
	return this->fondo->getAncho();
}
short Mundo1Escenario1::getAlto() {
	return this->fondo->getAlto();
}
void Mundo1Escenario1::mostrar() {
	Console::Clear();

	if (this->fondo) {
		this->fondo->render();
	}
	if (!this->mensajes.empty()) this->mostrarDialogo();
}
void Mundo1Escenario1::setJugador(Jugador* jugador) {
	this->jugadorEntity = jugador;
}
void Mundo1Escenario1::setIA(IA* ia) {
	this->IAEntity = ia;
}
void Mundo1Escenario1::mostrarDialogo() {
	this->mensajes[this->indice_mensaje]->render();
}

void Mundo1Escenario1::update() {
	if (this->fondo) this->fondo->render();
	if (this->jugadorEntity) this->jugadorEntity->render();

}

EstructuraEstatica* Mundo1Escenario1::getFondo() {
	return this->fondo;
};
void Mundo1Escenario1::handleDialog(char tecla) {
	switch (tecla)
	{
	case 13:
		this->indice_mensaje++;
		if (this->indice_mensaje == 5) {
			this->update();
		}
		else if (this->indice_mensaje >= 7) {
			this->update();
			*this->mostrar_dialogo = false;
			return;
		}
		this->mostrarDialogo();
		break;
	default:
		break;
	}
}

bool Mundo1Escenario1::estaCompletado() {
	short jx = this->jugadorEntity->getCuerpo()->getPosX();
	short jy = this->jugadorEntity->getCuerpo()->getPosY();

	return (jx >= this->puntoFinal.x &&
		jx <= this->puntoFinal.x + this->puntoFinal.ancho &&
		jy >= this->puntoFinal.y &&
		jy <= this->puntoFinal.y + this->puntoFinal.alto);
}
GameState* Mundo1Escenario1::cambiarEstado() {
	return new Mundo1Escenario2(this->mostrar_dialogo, this->guardarIA, this->jugadorEntity, this->IAEntity);
}

bool Mundo1Escenario1::setColisionCondition(char c, EstructuraDinamica*& entity) {
	short posX = entity->getPosX();
	short posY = entity->getPosY();

	switch (c)
	{
	case 'd':
		return posX < this->fondo->getAncho() - entity->getAncho();
		break;
	case 'a':
		return posX >= 1;
		break;
	case 'w':
		return posY > 37;
		break;
	case 's':
		return posY < this->fondo->getAlto() - entity->getAlto();
		break;
	}

	return true;
};
