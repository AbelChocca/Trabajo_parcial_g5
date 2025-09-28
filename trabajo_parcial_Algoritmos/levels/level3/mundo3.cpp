#include "mundo3.h"
#include "../../core/Map.h"
#include "mundo3_e1.h"
#include <vector>

Tile CharacterCharToTile(char c);

Mundo3::Mundo3()
{
	this->frame_actual = 0;
	this->escenarioActual = new Mundo3Escenario1();
    this->inicializarJugador();

    this->cargarFrame("assets/personaje_sprite1.txt");
    this->cargarFrame("assets/personaje_sprite2.txt");
    this->cargarFrame("assets/personaje_sprite3.txt");
}
void Mundo3::inicializarJugador() {
    Mundo3Escenario1* escenario1 = dynamic_cast<Mundo3Escenario1*>(this->escenarioActual);

    this->jugador = new EstructuraDinamica(10, 40, escenario1->getFondo());
    this->jugador->loadMap("assets/personaje_sprite1.txt", CharacterCharToTile);
}

Mundo3::~Mundo3()
{
    delete jugador;
    delete escenarioActual;
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
void Mundo3::handleInput(Game* game, char c) {
    this->escenarioActual->handleInput(game, c);
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

    sprites_jugador.push_back(nuevoFrame);
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