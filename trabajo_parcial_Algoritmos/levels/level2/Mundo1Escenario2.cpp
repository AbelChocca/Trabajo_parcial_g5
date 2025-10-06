#include "Mundo1Escenario2.h"
#include "mundo1_tile_control.h"
#include "../../core/Game.h"
#include "../../core/Map.h"
#include "../../core/Config.h"
#include "../../enemigo/enemigo.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"
#include "../../menu/Menu.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <cctype>

Mundo1Escenario2::Mundo1Escenario2(
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
    this->primerPunto = { 35, 35, 115, 2 };

    this->fondo = new EstructuraEstatica(0, 0);
    this->fondo->loadMap("mundo1_e2.txt", tile_control::E21CharToTile);

    // Mensajes
    EstructuraEstatica* mensaje1 = new EstructuraEstatica(40, 60);
    EstructuraEstatica* mensaje2 = new EstructuraEstatica(40, 60);
    mensaje1->loadMap("assets/mundo3_e2_dialogo1.txt", tile_control::Xaro1CharToTile);
    mensaje2->loadMap("assets/mundo3_e2_dialogo2.txt", tile_control::Xaro1CharToTile);
    mensajes.push_back(mensaje1);
    mensajes.push_back(mensaje2);

    // Enemigos
    EstructuraDinamica* enemigo_e1 = new EstructuraDinamica(60, 36, fondo);
    EstructuraDinamica* enemigo_e2 = new EstructuraDinamica(70, 49, fondo);
    enemigo_e1->loadMap("assets/enemigo.txt", tile_control::E1CharToTile);
    enemigo_e2->loadMap("assets/enemigo.txt", tile_control::E1CharToTile);

    Enemigo* enemigo1 = new Enemigo(enemigo_e1, 0);
    Enemigo* enemigo2 = new Enemigo(enemigo_e2, 0);
    enemigos.push_back(enemigo1);
    enemigos.push_back(enemigo2);

    mandarAlInicio();

    jugadorEntity->getCuerpo()->setFondo(fondo);
    IAEntity->getCuerpo()->setFondo(fondo);

    *mostrar_dialogo = true;

    preguntaActiva = false;
    preguntaMostrada = false;
    enemigoEnPregunta = nullptr;
}

Mundo1Escenario2::~Mundo1Escenario2() {
    delete fondo;
}

void Mundo1Escenario2::mostrarDialogo() {
    if (dialogo_activo && indice_mensaje < mensajes.size()) {
        mensajes[indice_mensaje]->render();
    }
}

void Mundo1Escenario2::update() {
    if (fondo) fondo->render();
    if (jugadorEntity) jugadorEntity->render();
    if (IAEntity) IAEntity->render();

    updatePreguntas();
}

void Mundo1Escenario2::mostrar() {
    Console::Clear();
    if (fondo) fondo->render();
    if (jugadorEntity) jugadorEntity->render();
    if (IAEntity) IAEntity->render();
    if (mostrar_dialogo) mostrarDialogo();
}

void Mundo1Escenario2::handleDialog(char tecla) {
    if (tecla == 13 && dialogo_activo) {
        mensajes[indice_mensaje]->borrar();
        if (indice_mensaje == 0) dialogo1_mostrado = true;
        if (indice_mensaje == 1) dialogo2_mostrado = true;
        dialogo_activo = false;
        *mostrar_dialogo = false;
    }
}

void Mundo1Escenario2::renderAnimation() {
    if (!fondo || !jugadorEntity || !IAEntity) return;

    int anchoFondo = fondo->getAncho();
    int altoFondo = fondo->getAlto();

    // 🟢 Movimiento del jugador
    if (!preguntaActiva && _kbhit()) {
        char tecla = tolower(_getch());
        EstructuraDinamica* cuerpo = jugadorEntity->getCuerpo();
        if (setColisionCondition(tecla, cuerpo)) {
            cuerpo->borrar();
            switch (tecla) {
            case 'w': cuerpo->setPosY(cuerpo->getPosY() - 1); break;
            case 's': cuerpo->setPosY(cuerpo->getPosY() + 1); break;
            case 'a': cuerpo->setPosX(cuerpo->getPosX() - 1); break;
            case 'd': cuerpo->setPosX(cuerpo->getPosX() + 1); break;
            default: break;
            }
        }
    }

    for (Enemigo*& enemigo : enemigos) {
        if (!enemigo) continue;

        if (enemigo == enemigoEnPregunta && preguntaActiva) {
            enemigo->getEstructura()->render();
            continue;
        }

        EstructuraDinamica* estructura = enemigo->getEstructura();
        if (!estructura) continue;

        estructura->borrar();

        int dx = enemigo->getDx();
        int nuevaX = estructura->getPosX() + dx;

        if (nuevaX < 0) {
            nuevaX = 0;
            enemigo->setDx(-dx);
        }
        else if (nuevaX + estructura->getAncho() >= anchoFondo) {
            nuevaX = anchoFondo - estructura->getAncho() - 1;
            enemigo->setDx(-dx);
        }

        estructura->setPosX(nuevaX);

        // 🟢 Colisión con el jugador
        if (enemigo->detectarColision(jugadorEntity->getCuerpo())) {
            estructura->setPosX(estructura->getPosX() - enemigo->getDx());

            if (!preguntaActiva) {
                preguntaActiva = true;
                preguntaMostrada = false;
                enemigoEnPregunta = enemigo;
            }
        }

        if (estructura->getPosX() >= 0 && estructura->getPosY() >= 0 &&
            estructura->getPosX() < anchoFondo && estructura->getPosY() < altoFondo) {
            estructura->render();
        }
    }

    jugadorEntity->render();
}

bool Mundo1Escenario2::setColisionCondition(char c, EstructuraDinamica*& entity) {
    if (!entity || !fondo) return false;

    if (colisionPrimerPunto() && !dialogo2_mostrado) {
        indice_mensaje = 1;
        dialogo_activo = true;
        *mostrar_dialogo = true;
        mostrarDialogo();
    }

    int posX = entity->getPosX();
    int posY = entity->getPosY();
    Tile** grafico = fondo->getGrafico();

    switch (c) {
    case 'd': {
        int x = posX + entity->getAncho();
        if (x >= fondo->getAncho()) return false;
        for (int y = posY; y < posY + entity->getAlto(); y++)
            if (grafico[y][x].isSolid) return false;
        break;
    }
    case 'a': {
        int x = posX - 1;
        if (x < 0) return false;
        for (int y = posY; y < posY + entity->getAlto(); y++)
            if (grafico[y][x].isSolid) return false;
        break;
    }
    case 's': {
        int y = posY + entity->getAlto();
        if (y >= fondo->getAlto()) return false;
        for (int x = posX; x < posX + entity->getAncho(); x++)
            if (grafico[y][x].isSolid) return false;
        break;
    }
    case 'w': {
        int y = posY - 1;
        if (y < 0) return false;
        for (int x = posX; x < posX + entity->getAncho(); x++)
            if (grafico[y][x].isSolid) return false;
        break;
    }
    }

    return true;
}

bool Mundo1Escenario2::colisionPrimerPunto() {
    int left = jugadorEntity->getCuerpo()->getPosX();
    int right = left + jugadorEntity->getCuerpo()->getAncho();
    int bottom = jugadorEntity->getCuerpo()->getPosY() + jugadorEntity->getCuerpo()->getAlto();

    return (bottom >= primerPunto.y &&
        bottom <= primerPunto.y + primerPunto.alto &&
        right >= primerPunto.x &&
        left <= primerPunto.x + primerPunto.ancho);
}

void Mundo1Escenario2::mandarAlInicio() {
    jugadorEntity->getCuerpo()->setPosX(5);
    jugadorEntity->getCuerpo()->setPosY(21);
    IAEntity->getCuerpo()->setPosX(25);
    IAEntity->getCuerpo()->setPosY(22);
}

void Mundo1Escenario2::updatePreguntas() {
    if (!preguntaActiva) return;

    if (!preguntaMostrada && enemigoEnPregunta) {
        EstructuraDinamica* cuerpo = enemigoEnPregunta->getEstructura();
        Console::SetCursorPosition(cuerpo->getPosX(), cuerpo->getPosY() - 2);

        std::ifstream file("pregunta2.txt");
        if (!file.is_open()) {
            std::cout << "No se pudo abrir pregunta1.txt\n";
            preguntaActiva = false;
            enemigoEnPregunta = nullptr;
            return;
        }

        std::string linea;
        std::cout << "\n--- PREGUNTA ---\n";
        while (std::getline(file, linea)) {
            std::cout << linea << "\n";
        }
        file.close();
        preguntaMostrada = true;
        std::cout << "\nElige una opción (A/B/C/D): ";
    }

    if (_kbhit()) {
        char tecla = std::tolower(_getch());
        switch (tecla) {
        case 'a':
        case 'c':
            std::cout << "\nRespuesta incorrecta.\n";
            preguntaActiva = false;
            preguntaMostrada = false;
            enemigoEnPregunta = nullptr;
            break;
        case 'b': // ✅ Respuesta correcta
            std::cout << "\ ¡Respuesta correcta! NIVEL 1 COMPLETADO.\n";
            Sleep(1500);
            {
                GameState* menu = new Menu();
                Game* game = new Game();
                game->setState(menu);
            }
            preguntaActiva = false;
            preguntaMostrada = false;
            enemigoEnPregunta = nullptr;
            break;
        case 'd':
            std::cout << "\nElegiste responder con la IA. Regresas al inicio.\n";
            mandarAlInicio();
            preguntaActiva = false;
            preguntaMostrada = false;
            enemigoEnPregunta = nullptr;
            break;
        default:
            break;
        }
    }
}

void Mundo1Escenario2::mostrarPregunta() {}

EstructuraEstatica* Mundo1Escenario2::getFondo() { return fondo; }
short Mundo1Escenario2::getAncho() { return fondo->getAncho(); }
short Mundo1Escenario2::getAlto() { return fondo->getAlto(); }
