#include "mundo3.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"
#include "../../core/UtilsFunc.h"
#include "../../utils/Item.h"
#include "mundo3_tile_control.h"
#include "mundo3_e1.h"
#include <queue>

Mundo3::Mundo3()
{
    this->escenarioActual = new Mundo3Escenario1(&this->mostrar_dialogo, &this->guardarIA);

    this->jugadorEntity = new Jugador(10, 40, this->escenarioActual->getFondo());
    this->IAEntity = new IA(100, 35, this->escenarioActual->getFondo());

    this->mostrar_dialogo = true;
    this->guardarIA = false;

    this->panel_control = new EstructuraEstatica(151, 0);
    this->panel_control->loadMap("assets/panel_control.txt", tile_control::PanelCharToTile);
    
    FrameLoader::cargarFrame(this->jugadorEntity->getSpritesJugador(), "assets/personaje_sprite1.txt", tile_control::CharacterCharToTile);
    FrameLoader::cargarFrame(this->jugadorEntity->getSpritesJugador(), "assets/personaje_sprite2.txt", tile_control::CharacterCharToTile);
    FrameLoader::cargarFrame(this->jugadorEntity->getSpritesJugador(), "assets/personaje_sprite3.txt", tile_control::CharacterCharToTile);

    FrameLoader::cargarFrame(this->IAEntity->getSpritesIA(), "assets/ia_sprite1.txt", tile_control::IACharToTile);
    FrameLoader::cargarFrame(this->IAEntity->getSpritesIA(), "assets/ia_sprite2.txt", tile_control::IACharToTile);


    if (auto escenario1 = dynamic_cast<Mundo3Escenario1*>(this->escenarioActual)) {
        escenario1->setJugador(this->jugadorEntity);
        escenario1->setIA(this->IAEntity);
    }

    auto& spritesIA = this->IAEntity->getSpritesIA();
    std::wcout << "Sprites IA cargados: " << spritesIA.size() << std::endl;

    this->IAEntity->getCuerpo()->setSprite(this->IAEntity->getSpritesIA()[1]);
}

Mundo3::~Mundo3()
{
    delete jugadorEntity;
    delete IAEntity;
    delete escenarioActual;
}
bool Mundo3::esValidoTile(int tx, int ty) {
    int anchoMapa = this->escenarioActual->getAncho();
    int altoMapa = this->escenarioActual->getAlto();

    if (tx < 0 || ty < 0 || tx >= anchoMapa || ty >= altoMapa) {
        return false;
    }

    Tile t = this->escenarioActual->getFondo()->getGrafico()[ty][tx];
    return !t.isSolid;
}

void Mundo3::mostrar() {
    Console::Clear();

    if (this->escenarioActual) {
        this->escenarioActual->mostrar();
    }

    if (this->panel_control) {
        this->panel_control->render();
    }
    if (this->jugadorEntity) {
        this->jugadorEntity->render();
        this->jugadorEntity->getBarraVida().renderizarBarra();
    }
}
void Mundo3::renderAnimation() {
    this->escenarioActual->renderAnimation();
}
void Mundo3::mover(char c) {
    EstructuraDinamica* jugadorCuerpo = this->jugadorEntity->getCuerpo();
    EstructuraDinamica* iaCuerpo = this->IAEntity->getCuerpo();
    Inventario& inventarioJugador = this->jugadorEntity->getInventario();

    jugadorCuerpo->borrar();
    if (!this->guardarIA) iaCuerpo->borrar();

    short posX = jugadorCuerpo->getPosX();
    short posY = jugadorCuerpo->getPosY();

    short posIX = iaCuerpo->getPosX();
    short posIY = iaCuerpo->getPosY();

    short destinoX = posX + (jugadorCuerpo->getAncho() * 2);
    short destinoY = posY + (jugadorCuerpo->getAlto() / 2);
   

    // Distancia entre IA y Jugador
    int dist = abs(posIX - destinoX) + abs(posIY - destinoY);

    if (dist > 50) {
        jugadorCuerpo->render();
        this->IAEntity->moverIAhaciaDestino(destinoX, destinoY);
        return;
    }

    switch (c)
    {
    case 'd':
        // jugador
        if (this->escenarioActual->setColisionCondition(c, jugadorCuerpo)) {
            jugadorCuerpo->setPosX(posX + 1);
        }
        this->jugadorEntity->setSpriteDireccion(jugadorCuerpo, 1);
        this->jugadorEntity->setDireccion('d');

        // IA
        if (this->escenarioActual->setColisionCondition(c, iaCuerpo)) {
            iaCuerpo->setPosX(posIX + 1);
        }
        iaCuerpo->setSprite(this->IAEntity->getSpritesIA()[0]);

        break;
    case 'a':
        //jugador
        if (this->escenarioActual->setColisionCondition(c, jugadorCuerpo)) {
            jugadorCuerpo->setPosX(posX - 1);
        }
        this->jugadorEntity->setSpriteDireccion(jugadorCuerpo, 2);
        this->jugadorEntity->setDireccion('a');
        // IA
        if (this->escenarioActual->setColisionCondition(c, iaCuerpo)) {
            iaCuerpo->setPosX(posIX - 1);
        }
        iaCuerpo->setSprite(this->IAEntity->getSpritesIA()[1]);
        break;
    case 'w':
        if (this->escenarioActual->setColisionCondition(c, jugadorCuerpo))
            jugadorCuerpo->setPosY(posY - 1);
        if (this->escenarioActual->setColisionCondition(c, iaCuerpo))
            iaCuerpo->setPosY(posIY - 1);
        break;
    case 's':
        if (this->escenarioActual->setColisionCondition(c, jugadorCuerpo))
            jugadorCuerpo->setPosY(posY + 1);

        if (this->escenarioActual->setColisionCondition(c, iaCuerpo))
            iaCuerpo->setPosY(posIY + 1);
        break;
    case 'g':
        if (!this->guardarIA) {
            jugadorCuerpo->render();
            this->IAEntity->moverIAhaciaDestino(destinoX, destinoY);
        }
        break;
    case 't':
        this->guardarIA = !this->guardarIA;
        break;
    case 'r':
        if (this->jugadorEntity->getInventario().getItemEquipado() != nullptr) {
            this->jugadorEntity->getInventario().getItemEquipado()->agregarItem(this->jugadorEntity);
        }
        break;
    case 'e':
        if (this->escenarioActual->getItemCercano() != nullptr) {
            this->escenarioActual->intentaRecojer(this->jugadorEntity);
        }
        break;
    case 'b':
        jugadorCuerpo->render();
        if (!this->guardarIA) iaCuerpo->render();
        this->jugadorEntity->getInventario().seleccionarItem(this->jugadorEntity);
        break;
    default:
        if (!this->jugadorEntity->getSpritesJugador().empty()) {
            this->jugadorEntity->setSpriteDireccion(jugadorCuerpo, 0);
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
    if (!this->guardarIA) iaCuerpo->render();
}

void Mundo3::handleInput(Game* game, char c) {
    if (this->mostrar_dialogo) {
        this->escenarioActual->handleDialog(c);
    }
    else {
        this->mover(c);
    }
}
void Mundo3::update() {
    if (this->escenarioActual) {
        this->escenarioActual->mostrar();
    }

    if (this->jugadorEntity) {
        this->jugadorEntity->render();
        this->jugadorEntity->getBarraVida().renderizarBarra();
    }
}