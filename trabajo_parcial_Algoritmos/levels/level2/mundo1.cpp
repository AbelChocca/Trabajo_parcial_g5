#include "mundo1.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"
#include "mundo1_tile_control.h"
#include "Mundo1Escenario1.h"
#include <queue>

Mundo1::Mundo1()
{
    this->escenarioActual = new Mundo1Escenario1(&this->mostrar_dialogo, &this->guardarIA);

    this->jugadorEntity = new Jugador(10, 40, this->escenarioActual->getFondo());
    this->IAEntity = new IA(100, 35, this->escenarioActual->getFondo());

    this->mostrar_dialogo = true;
    this->guardarIA = false;

    this->panel_control = new EstructuraEstatica(151, 0);
    this->panel_control->loadMap("assets/panel_control.txt", tile_control::Panel1CharToTile);

    this->cargarFrame(this->jugadorEntity->getSpritesJugador(), "assets/personaje_sprite1.txt", tile_control::Character1CharToTile);
    this->cargarFrame(this->jugadorEntity->getSpritesJugador(), "assets/personaje_sprite2.txt", tile_control::Character1CharToTile);
    this->cargarFrame(this->jugadorEntity->getSpritesJugador(), "assets/personaje_sprite3.txt", tile_control::Character1CharToTile);

    this->cargarFrame(this->IAEntity->getSpritesIA(), "assets/ia_sprite1.txt", tile_control::IA1CharToTile);
    this->cargarFrame(this->IAEntity->getSpritesIA(), "assets/ia_sprite2.txt", tile_control::IA1CharToTile);


    if (auto escenario1 = dynamic_cast<Mundo1Escenario1*>(this->escenarioActual)) {
        escenario1->setJugador(this->jugadorEntity);
        escenario1->setIA(this->IAEntity);
    }

    this->IAEntity->getCuerpo()->setSprite(this->IAEntity->getSpritesIA()[1]);
}

Mundo1::~Mundo1()
{
    delete jugadorEntity;
    delete escenarioActual;
}
bool Mundo1::esValidoTile(int tx, int ty) {
    int anchoMapa = this->escenarioActual->getAncho();
    int altoMapa = this->escenarioActual->getAlto();

    if (tx < 0 || ty < 0 || tx >= anchoMapa || ty >= altoMapa) {
        return false;
    }

    Tile t = this->escenarioActual->getFondo()->getGrafico()[ty][tx];
    return !t.isSolid;
}

void Mundo1::mostrar() {
    Console::Clear();

    if (this->escenarioActual) {
        this->escenarioActual->mostrar();
    }

    if (this->jugadorEntity) {
        this->jugadorEntity->render();
    }

    // 🧠 Solo mostrar IA si NO estamos en el Escenario 1
    if (this->IAEntity && dynamic_cast<Mundo1Escenario1*>(this->escenarioActual) == nullptr) {
        this->IAEntity->render();
    }

    if (this->panel_control) {
        this->panel_control->render();
    }
}

void Mundo1::renderAnimation() {
    this->escenarioActual->renderAnimation();
}
void Mundo1::mover(char c) {
    EstructuraDinamica* jugadorCuerpo = this->jugadorEntity->getCuerpo();

    // ✅ Detectar si estamos en el Escenario 1
    bool esEscenario1 = dynamic_cast<Mundo1Escenario1*>(this->escenarioActual) != nullptr;

    // ⚠️ Solo usar IA si NO estamos en Escenario 1
    EstructuraDinamica* iaCuerpo = nullptr;
    if (!esEscenario1) {
        iaCuerpo = this->IAEntity->getCuerpo();
        iaCuerpo->borrar();
    }

    jugadorCuerpo->borrar();

    short posX = jugadorCuerpo->getPosX();
    short posY = jugadorCuerpo->getPosY();

    short posIX = 0, posIY = 0, destinoX = 0, destinoY = 0;

    if (!esEscenario1) {
        posIX = iaCuerpo->getPosX();
        posIY = iaCuerpo->getPosY();

        destinoX = posX + (jugadorCuerpo->getAncho() * 2);
        destinoY = posY + (jugadorCuerpo->getAlto() / 2);

        // Distancia entre IA y Jugador
        int dist = abs(posIX - destinoX) + abs(posIY - destinoY);

        if (dist > 50) {
            jugadorCuerpo->render();
            this->IAEntity->moverIAhaciaDestino(destinoX, destinoY);
            return;
        }
    }

    switch (c)
    {
    case 'd':
        if (this->escenarioActual->setColisionCondition(c, jugadorCuerpo)) {
            jugadorCuerpo->setPosX(posX + 1);
        }
        jugadorCuerpo->setSprite(this->jugadorEntity->getSpritesJugador()[1]);

        if (!esEscenario1 && this->escenarioActual->setColisionCondition(c, iaCuerpo)) {
            iaCuerpo->setPosX(posIX + 1);
            iaCuerpo->setSprite(this->IAEntity->getSpritesIA()[0]);
        }
        break;

    case 'a':
        if (this->escenarioActual->setColisionCondition(c, jugadorCuerpo)) {
            jugadorCuerpo->setPosX(posX - 1);
        }
        jugadorCuerpo->setSprite(this->jugadorEntity->getSpritesJugador()[2]);

        if (!esEscenario1 && this->escenarioActual->setColisionCondition(c, iaCuerpo)) {
            iaCuerpo->setPosX(posIX - 1);
            iaCuerpo->setSprite(this->IAEntity->getSpritesIA()[1]);
        }
        break;

    case 'w':
        if (this->escenarioActual->setColisionCondition(c, jugadorCuerpo))
            jugadorCuerpo->setPosY(posY - 1);
        if (!esEscenario1 && this->escenarioActual->setColisionCondition(c, iaCuerpo))
            iaCuerpo->setPosY(posIY - 1);
        break;

    case 's':
        if (this->escenarioActual->setColisionCondition(c, jugadorCuerpo))
            jugadorCuerpo->setPosY(posY + 1);
        if (!esEscenario1 && this->escenarioActual->setColisionCondition(c, iaCuerpo))
            iaCuerpo->setPosY(posIY + 1);
        break;

    case 'g':
        if (!esEscenario1) {
            jugadorCuerpo->render();
            this->IAEntity->moverIAhaciaDestino(destinoX, destinoY);
            return;
        }
        break;

    default:
        if (!this->jugadorEntity->getSpritesJugador().empty()) {
            jugadorCuerpo->setSprite(this->jugadorEntity->getSpritesJugador()[0]);
        }
        break;
    }

    if (this->escenarioActual->estaCompletado()) {
        GameState* siguiente = this->escenarioActual->cambiarEstado();
        delete this->escenarioActual;
        this->escenarioActual = siguiente;
        jugadorCuerpo->setSprite(this->jugadorEntity->getSpritesJugador()[0]);

        Console::Clear();
        this->mostrar();
        return;
    }

    jugadorCuerpo->render();

    // ✅ Renderizar IA solo si no estamos en Escenario 1
    if (!esEscenario1) {
        iaCuerpo->render();
    }
}


void Mundo1::handleInput(Game* game, char c) {
    if (this->mostrar_dialogo) {
        this->escenarioActual->handleDialog(c);
    }
    else {
        this->mover(c);
    }
}
void Mundo1::update() {
    if (this->escenarioActual) {
        this->escenarioActual->update();         // 🔄 ejecuta lógica (colisiones, preguntas)
        this->escenarioActual->renderAnimation(); // 🎨 mueve y dibuja enemigos
    }

    if (this->jugadorEntity) {
        this->jugadorEntity->render();
    }
}

void Mundo1::cargarFrame(
    vector<vector<vector<Tile>>>& sprites,
    const std::string& archivo,
    CharToTileFunc charToTile) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + archivo);
    }

    std::vector<std::vector<Tile>> nuevoFrame;

    std::string linea;
    while (std::getline(file, linea)) {
        std::vector<Tile> fila;
        for (char c : linea) {
            fila.push_back(charToTile(c));
        }
        nuevoFrame.push_back(fila);
    }

    sprites.push_back(nuevoFrame);
}
