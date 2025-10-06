#include "mundo3_e3.h"
#include "../../core/Map.h"
#include "mundo3_tile_control.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"
#include "../../Entidad/Jefe.h"
#include "../../ataque/Laser.h"
#include "../../ataque/RayoCentinela.h"

using namespace System;
using namespace System::Threading;

Mundo3Escenario3::Mundo3Escenario3(
    bool* mostrar_dialogo,
    bool* guardarIA,
    Jugador* jugador,
    IA* IA
) {
    this->mostrar_dialogo = mostrar_dialogo;
    this->guardarIA = guardarIA;
    this->indice_mensaje = 0;

    this->fondo = new EstructuraEstatica(0, 0);
    this->fondo->loadMap("mundo3_e3.txt", tile_control::E3CharTotTile);

    this->jugadorEntity = jugador;
    this->IAEntity = IA;

    this->jugadorEntity->getCuerpo()->setFondo(this->fondo);
    this->IAEntity->getCuerpo()->setFondo(this->fondo);

    this->jugadorEntity->getCuerpo()->setPosX(5);
    this->jugadorEntity->getCuerpo()->setPosY(42);

    this->IAEntity->getCuerpo()->setPosX(25);
    this->IAEntity->getCuerpo()->setPosY(40);

    // El jefe recibe al jugador como objetivo
    this->jefeFinal = new Jefe(jugadorEntity, this->fondo);

    this->activo = false;
}

Mundo3Escenario3::~Mundo3Escenario3() {
    detenerThreads();
    delete this->fondo;
    delete this->jefeFinal;
    for (auto m : mensajes) delete m;
}
void Mundo3Escenario3::mostrar() {
    Console::Clear();

    if (this->fondo) this->fondo->render();
    if (this->jugadorEntity)
        this->jugadorEntity->getBarraVida().renderizarBarra();

    if (!this->mensajes.empty())
        this->mostrarDialogo();
}

void Mundo3Escenario3::mostrarDialogo() {
    this->mensajes[this->indice_mensaje]->render();
}

void Mundo3Escenario3::iniciarThreads() {
    this->activo = true;

    // Hilo del jefe final (IA enemiga principal)
    threadJefe = std::thread([this]() {
        while (activo) {
            if (!jefeFinal->estaVivo()) break;

            // Ataque automático del jefe
            jefeFinal->ejecutarAtaqueRandom();

            Thread::Sleep(400);
        }
        });
}

void Mundo3Escenario3::detenerThreads() {
    activo = false;
    if (threadJefe.joinable()) threadJefe.join();
}

void Mundo3Escenario3::update() {
    if (this->fondo) this->fondo->render();

    if (this->jugadorEntity) {
        this->jugadorEntity->render();
        this->jugadorEntity->getBarraVida().renderizarBarra();
    }
    if (this->IAEntity) this->IAEntity->render();
    if (this->jefeFinal) {
        this->jefeFinal->renderCuerpo();
        this->jefeFinal->getBarraVida().renderizarBarra();
    }
}
void Mundo3Escenario3::handleDialog(char tecla) {
    switch (tecla)
    {
    case 13:
        this->indice_mensaje++;
        if (this->indice_mensaje >= this->mensajes.size()) {
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
void Mundo3Escenario3::renderAnimation() {
    return;
}

void Mundo3Escenario3::handleInput(Game* game, char tecla) {
    return;
}
bool Mundo3Escenario3::setColisionCondition(char c, EstructuraDinamica*& entity) {
    short posX = entity->getPosX();
    short posY = entity->getPosY();

    short nextX = posX;
    short nextY = posY;

    switch (c) {
    case 'd': nextX = posX + 1; break;
    case 'a': nextX = posX - 1; break;
    case 'w': nextY = posY - 1; break;
    case 's': nextY = posY + 1; break;
    }

    if (nextY < 13 || nextY + entity->getAlto() > 73)
        return false;
    if (nextX + entity->getAncho() > 95)
        return false;

    return true;
}