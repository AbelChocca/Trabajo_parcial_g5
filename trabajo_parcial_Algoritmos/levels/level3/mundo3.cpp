#include "mundo3.h"
#include "../../core/Map.h"
#include "mundo3_e1.h"
#include <vector>

Tile CharacterCharToTile(char c);

Mundo3::Mundo3()
{
    this->mostrar_dialogo = true;
	this->frame_actual = 0;
	this->escenarioActual = new Mundo3Escenario1(&this->mostrar_dialogo);

    this->cargarFrame("assets/personaje_sprite1.txt");
    this->cargarFrame("assets/personaje_sprite2.txt");
    this->cargarFrame("assets/personaje_sprite3.txt");

    this->inicializarPersonajes();

    if (auto escenario1 = dynamic_cast<Mundo3Escenario1*>(this->escenarioActual)) {
        escenario1->setJugador(this->jugador);
    }

}
void Mundo3::inicializarPersonajes() {
    Mundo3Escenario1* escenario1 = dynamic_cast<Mundo3Escenario1*>(this->escenarioActual);

    this->jugador = new EstructuraDinamica(10, 40, escenario1->getFondo());
    this->jugador->loadMap("assets/personaje_sprite1.txt", CharacterCharToTile);

    this->IA = new EstructuraDinamica(30, 30, escenario1->getFondo());
    this->IA->loadMap("assets/ia_sprite1.txt", nullptr);
}

Mundo3::~Mundo3()
{
    delete jugador;
    delete escenarioActual;
}
bool Mundo3::esValido(int x, int y) {
    return (x >= 0 && x < this->escenarioActual->getAncho() && y >= 0 && y < this->escenarioActual->getAlto());
}

void Mundo3::mostrar() {
    Console::Clear();

    if (this->escenarioActual) {
        this->escenarioActual->mostrar();
    }

    if (this->jugador) {
        this->jugador->render();
    }
}
void Mundo3::mover(char c) {
    this->jugador->borrar();

    short posX = this->jugador->getPosX();
    short posY = this->jugador->getPosY();

    switch (c)
    {
    case 'd':
        if (posX < MAX_WIDTH - this->jugador->getAncho()) {
            this->jugador->setPosX(posX + 1);
        }
        if (sprites_jugador.size() > 1) {
            this->jugador->setSprite(this->sprites_jugador[1]);
        }
        break;
    case 'a':
        if (posX >= 1) {
            this->jugador->setPosX(posX - 1);
        }
        if (sprites_jugador.size() > 2) {
            this->jugador->setSprite(this->sprites_jugador[2]);
        }
        break;
    case 'w':
        if (posY > 37)
            this->jugador->setPosY(posY - 1);
        break;
    case 's':
        if (posY < MAX_HEIGHT - this->jugador->getAlto())
            this->jugador->setPosY(posY + 1);
        break;
    default:
        if (!sprites_jugador.empty()) {
            this->jugador->setSprite(this->sprites_jugador[0]);
        }
        break;
    }

    this->jugador->render();
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

    if (this->jugador) {
        this->jugador->render();
    }
}

void Mundo3::cargarFrame(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + archivo);
    }

    std::vector<std::vector<Tile>> nuevoFrame; 

    std::string linea;
    while (std::getline(file, linea)) {
        std::vector<Tile> fila;
        for (char c : linea) {
            fila.push_back(CharacterCharToTile(c));
        }
        nuevoFrame.push_back(fila);
    }

    this->sprites_jugador.push_back(nuevoFrame);
}

Tile CharacterCharToTile(char c) {
    Tile t;

    switch (c)
    {
    case '*':
        t.bloque = L'▒';
        t.color = ConsoleColor::DarkYellow;
        break;
    case '#':
        t.bloque = L'▓';
        t.color = ConsoleColor::Yellow;
        break;
    case '0':
        t.bloque = L'█';
        t.color = ConsoleColor::White;
        break;
    case '1':
        t.bloque = L'░';
        t.color = ConsoleColor::Black;
        break;
    case '2':
        t.bloque = L'░';
        t.color = ConsoleColor::DarkGray;
        break;
    case '3':
        t.bloque = L'▒';
        t.color = ConsoleColor::Gray;
        break;
    case '4':
        t.bloque = L'░';
        t.color = ConsoleColor::DarkBlue;
        break;
    case '5':
        t.bloque = L'░';
        t.color = ConsoleColor::Black;
        break;
    default:
        t.bloque = c;
        t.color = ConsoleColor::Black;
        break;
    }
    return t;
}