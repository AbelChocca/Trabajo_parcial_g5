#include "mundo3_e2.h"
#include "../../core/Map.h"
#include "mundo3_tile_control.h"
#include "../../enemigo/enemigo.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"

Mundo3Escenario2::Mundo3Escenario2(
	bool* mostrar_dialogo, 
	bool* guardarIA,
	Jugador* jugador,
	IA* ia
) {
	this->jugadorEntity = jugador;
	this->IAEntity = ia;
	this->indice_mensaje = 0;
	this->mostrar_dialogo = mostrar_dialogo;
	this->guardarIA = guardarIA;
	this->primerPunto = {35, 35, 115, 2};

	this->fondo = new EstructuraEstatica(0,0);
	this->fondo->loadMap("assets/mundo3_e2.txt", tile_control::E2CharToTile);

	EstructuraEstatica* mensaje1 = new EstructuraEstatica(40, 60);
	EstructuraEstatica* mensaje2 = new EstructuraEstatica(40, 60);

	mensaje1->loadMap("assets/mundo3_e2_dialogo1.txt", tile_control::XaroCharToTile);
	mensaje2->loadMap("assets/mundo3_e2_dialogo2.txt", tile_control::XaroCharToTile);

	this->mensajes.push_back(mensaje1);
	this->mensajes.push_back(mensaje2);

	EstructuraDinamica* enemigo_e1 = new EstructuraDinamica(60, 36, this->fondo);
	EstructuraDinamica* enemigo_e2 = new EstructuraDinamica(70, 49, this->fondo);

	enemigo_e1->loadMap("assets/enemigo.txt", tile_control::ECharToTile);
	enemigo_e2->loadMap("assets/enemigo.txt", tile_control::ECharToTile);

	Enemigo* enemigo1 = new Enemigo(enemigo_e1);
	Enemigo* enemigo2 = new Enemigo(enemigo_e2);

	this->enemigos.push_back(enemigo1);
	this->enemigos.push_back(enemigo2);

	this->mandarAlInicio();

	this->jugadorEntity->getCuerpo()->setFondo(this->fondo);
	this->IAEntity->getCuerpo()->setFondo(this->fondo);

	*this->mostrar_dialogo = true;
}
Mundo3Escenario2::~Mundo3Escenario2() {
	delete fondo;
}

void Mundo3Escenario2::mostrarDialogo() {
	if (this->dialogo_activo) this->mensajes[this->indice_mensaje]->render();
};

EstructuraEstatica* Mundo3Escenario2::getFondo() {
	return this->fondo;
};
void Mundo3Escenario2::update() {
	if (this->fondo) this->fondo->render();
	if (this->jugadorEntity) this->jugadorEntity->render();
	if (this->IAEntity) this->IAEntity->render();
};
void Mundo3Escenario2::mostrar() {
	Console::Clear();
	if (this->fondo) this->fondo->render();
	if (this->jugadorEntity) this->jugadorEntity->render();
	if (this->IAEntity) this->IAEntity->render();
	if (this->mostrar_dialogo) this->mostrarDialogo();
};
void Mundo3Escenario2::handleDialog(char tecla) {
	if (tecla == 13 && this->dialogo_activo) {
		this->mensajes[this->indice_mensaje]->borrar();

		if (indice_mensaje == 0) dialogo1_mostrado = true;
		if (indice_mensaje == 1) dialogo2_mostrado = true;

		this->dialogo_activo = false;
		*this->mostrar_dialogo = false;
	}
};
void Mundo3Escenario2::renderAnimation() {
	for (Enemigo*& enemigo : this->enemigos) {
		EstructuraDinamica* estructura = enemigo->getEstructura();
		estructura->borrar();

		estructura->setPosX(estructura->getPosX() + enemigo->getDx());

		if (enemigo->detectarColision(this->jugadorEntity->getCuerpo())) {
			this->jugadorEntity->getCuerpo()->borrar();
			this->IAEntity->getCuerpo()->borrar();
			this->mandarAlInicio();
			// Quitar vida al jugador
		}

		estructura->render();
	}
}
void Mundo3Escenario2::mandarAlInicio() {
	this->jugadorEntity->getCuerpo()->setPosX(5);
	this->jugadorEntity->getCuerpo()->setPosY(21);

	this->IAEntity->getCuerpo()->setPosX(25);
	this->IAEntity->getCuerpo()->setPosY(22);
}
bool Mundo3Escenario2::colisionPrimerPunto() {
	short left = this->jugadorEntity->getCuerpo()->getPosX();
	short right = left + this->jugadorEntity->getCuerpo()->getAncho();
	short bottom = this->jugadorEntity->getCuerpo()->getPosY() + this->jugadorEntity->getCuerpo()->getAlto();

	return (bottom >= this->primerPunto.y &&
		bottom <= this->primerPunto.y + this->primerPunto.alto &&
		right >= this->primerPunto.x &&
		left <= this->primerPunto.x + this->primerPunto.ancho);
}

bool Mundo3Escenario2::setColisionCondition(char c, EstructuraDinamica*& entity) {
	if (this->colisionPrimerPunto() && !dialogo2_mostrado) {
		this->indice_mensaje = 1;
		this->dialogo_activo = true;
		*this->mostrar_dialogo = true;
		this->mostrarDialogo();
	}
	short posX = entity->getPosX();
	short posY = entity->getPosY();
	Tile** grafico = this->fondo->getGrafico();
	switch (c)
	{
	case 'd':
	{
		int x = posX + entity->getAncho();
		for (int y = posY; y < posY + entity->getAlto(); y++) {
			if (x >= MAX_WIDTH || grafico[y][x].isSolid) return false;
		}
		break;
	}
	case 'a':
	{
		int x = posX - 1;
		for (int y = posY; y < posY + entity->getAlto(); y++) {
			if (x < 0 || grafico[y][x].isSolid) return false;
		}
		break;
	}
	case 's':
	{
		int y = posY + entity->getAlto();
		for (int x = posX; x < posX + entity->getAncho(); x++) {
			if (y >= MAX_HEIGHT || grafico[y][x].isSolid) return false;
		}
		break;
	}
	case 'w':
	{
		int y = posY - 1;
		for (int x = posX; x < posX + entity->getAncho(); x++) {
			if (y < 0 || grafico[y][x].isSolid) return false;
		}
		break;
	}
	default:
		break;
	}

	return true;
}

short Mundo3Escenario2::getAncho() {
	return this->fondo->getAncho();
};
short Mundo3Escenario2::getAlto() {
	return this->fondo->getAlto();
};
