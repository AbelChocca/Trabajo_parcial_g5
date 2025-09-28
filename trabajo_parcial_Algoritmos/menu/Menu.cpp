#include "../core/Game.h"
#include <conio.h>
#include "../selector/Selector.h"

Tile MenuCharToTile(char c);
Tile InputCharToTile(char c);

Menu::Menu() {

    layout = new EstructuraEstatica(0, 0);
    layout->loadMap("assets/menu.txt", MenuCharToTile);
    input = new EstructuraDinamica(POSX_INPUT, POSY_INPUT, layout);
    input->loadMap("assets/input_handler.txt", InputCharToTile);
    opcionSeleccionada = 0;
}

Menu::~Menu() {
    delete layout;
    delete input;
}

void Menu::mostrar() {
    Console::Clear();

    if (layout) {
        layout->render();
    }
    if (this->input) {
        this->input->render();
    }
}
void Menu::update() {
    if (layout) {
        layout->render();
    }
}

void Menu::handleInput(Game* game, char c) {
    if (c == '1') {
        this->input->borrar();
        this->input->setPosY(22);
        this->setOpcion(0);
    }
    else if (c == '2') {
        this->input->borrar();
        this->input->setPosY(32);
        this->setOpcion(1);
    }
    else if (c == '3') {
        this->input->borrar();
        this->input->setPosY(42);
        this->setOpcion(2);
    }
    else if (c == 13) {
        if (this->getOpcion() == 0) {
            game->setState(new Selector());
            return;
        }
    }
    this->getInput()->render();
}

Tile MenuCharToTile(char c) {
    Tile t;

    switch (c) {
    case '#':
    case '0':
        t.bloque = L'█';
        t.color = ConsoleColor::White;
        break;

    case '*':
        t.bloque = L'█';
        t.color = ConsoleColor::DarkBlue;
        break;
    case '=':
    case '1':
    case '3':
        t.bloque = L'█';
        t.color = ConsoleColor::DarkGray;
        break;
    case '2':
        t.bloque = L'█';
        t.color = ConsoleColor::DarkCyan;
        break;
    case '4':
        t.bloque = L'█';
        t.color = ConsoleColor::Gray;
        break;
    case ' ':
        t.bloque = L' ';
        t.color = ConsoleColor::Black;
        break;
    case '5':
        t.bloque = L'█';
        t.color = ConsoleColor::Magenta;
        break;
    case '6':
        t.bloque = L'█';
        t.color = ConsoleColor::DarkMagenta;
        break;
    case '7':
        t.bloque = L'█';
        t.color = ConsoleColor::DarkRed;
        break;
    default:
        t.bloque = c;
        t.color = ConsoleColor::Gray;
        break;
    }

    return t;
}
Tile InputCharToTile(char c) {
    Tile t;

    switch (c)
    {
    case '*':
        t.bloque = L'█';
        t.color = ConsoleColor::White;
        break;
    case ' ':
        t.bloque = L' ';
        t.color = ConsoleColor::Black;
        break;
    default:
        t.bloque = c;
        t.color = ConsoleColor::Black;
    }
    return t;
}