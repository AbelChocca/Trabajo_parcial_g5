#include "mundo3_e1.h"
#include "mundo3_e2.h"
#include "../../core/Map.h"
#include "../../core/Config.h"
#include "mundo3_tile_control.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"

Mundo3Escenario1::Mundo3Escenario1(
	bool* mostrar_dialogo, 
	bool* guardarIA
)
{
	this->mostrar_dialogo = mostrar_dialogo;
	this->guardarIA = guardarIA;
	this->fondo = new EstructuraEstatica(0, 0);
	this->fondo->loadMap("assets/mundo3_e1.txt", tile_control::E1CharToTile);
	this->indice_mensaje = 0;
	this->puntoFinal = { this->fondo->getAncho() - 20, 35, 20, 15};

	// Dialogos
	EstructuraEstatica* dialogo1 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo2 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo3 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo4 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo5 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo6 = new EstructuraEstatica(25, 40);
	EstructuraEstatica* dialogo7 = new EstructuraEstatica(25, 40);

	dialogo1->loadMap("assets/mundo3_dialogo1.txt", tile_control::DialogCharToTile);
	dialogo2->loadMap("assets/mundo3_dialogo2.txt", tile_control::DialogCharToTile);
	dialogo3->loadMap("assets/mundo3_dialogo3.txt", tile_control::DialogCharToTile);
	dialogo4->loadMap("assets/mundo3_dialogo4.txt", tile_control::DialogCharToTile);
	dialogo5->loadMap("assets/mundo3_dialogo5.txt", tile_control::DialogCharToTile);
	dialogo6->loadMap("assets/mundo3_dialogo6.txt", tile_control::XaroCharToTile);
	dialogo7->loadMap("assets/mundo3_dialogo7.txt", tile_control::XaroCharToTile);

	this->mensajes.push_back(dialogo1);
	this->mensajes.push_back(dialogo2);
	this->mensajes.push_back(dialogo3);
	this->mensajes.push_back(dialogo4);
	this->mensajes.push_back(dialogo5);
	this->mensajes.push_back(dialogo6);
	this->mensajes.push_back(dialogo7);
}

Mundo3Escenario1::~Mundo3Escenario1()
{
	for (auto& mensaje : this->mensajes) {
		delete mensaje;
	}
	delete this->fondo;
}
short Mundo3Escenario1::getAncho() {
	return this->fondo->getAncho();
}
short Mundo3Escenario1::getAlto() {
	return this->fondo->getAlto();
}
void Mundo3Escenario1::mostrar() {
	Console::Clear();

	if (this->fondo) {
		this->fondo->render();
	}
	if (!this->mensajes.empty()) this->mostrarDialogo();
}
void Mundo3Escenario1::setJugador(Jugador* jugador) {
	this->jugadorEntity = jugador;
}
void Mundo3Escenario1::setIA(IA* ia) {
	this->IAEntity = ia;
}
void Mundo3Escenario1::mostrarDialogo() {
	this->mensajes[this->indice_mensaje]->render();
}

void Mundo3Escenario1::update() {
	if (this->fondo) this->fondo->render();
	if (this->jugadorEntity) this->jugadorEntity->render();
	if (this->IAEntity) this->IAEntity->render();
}
EstructuraEstatica* Mundo3Escenario1::getFondo() {
	return this->fondo;
};
void Mundo3Escenario1::handleDialog(char tecla) {
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

bool Mundo3Escenario1::estaCompletado() {
	short jx = this->jugadorEntity->getCuerpo()->getPosX();
	short jy = this->jugadorEntity->getCuerpo()->getPosY();

	return (jx >= this->puntoFinal.x &&
		jx <= this->puntoFinal.x + this->puntoFinal.ancho &&
		jy >= this->puntoFinal.y &&
		jy <= this->puntoFinal.y + this->puntoFinal.alto);
}
GameState* Mundo3Escenario1::cambiarEstado() {
	return new Mundo3Escenario2(this->mostrar_dialogo, this->guardarIA, this->jugadorEntity, this->IAEntity);
}

bool Mundo3Escenario1::setColisionCondition(char c, EstructuraDinamica*& entity) {
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
