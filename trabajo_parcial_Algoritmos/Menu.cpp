#include "Menu.h"

Tile MenuCharToTile(char c);

Menu::Menu() {
    layout = new Estructura(0, 0);
    layout->loadMap("menu.txt", MenuCharToTile);
    input = new InputHandler();
    opcionSeleccionada = 0;
}

Menu::~Menu() {
    delete layout;
    delete input;
}

void Menu::mostrar() {
    Console::Clear();

    // Renderizar el menú desde el archivo
    if (layout) {
        layout->render();
    }

    // leer input
    if (_kbhit()) {
        char tecla = _getch();
        if (tecla == '1') opcionSeleccionada = 1;
        else if (tecla == '2') opcionSeleccionada = 2;
        else if (tecla == '3') opcionSeleccionada = 3;
    }
}


int Menu::getOpcion() {
    return opcionSeleccionada;
}

Tile MenuCharToTile(char c) {
    Tile t;

    switch (c) {
    case '#':
        t.bloque = L'█';
        t.color = ConsoleColor::White;
        break;

    case '*': 
        t.bloque = L'█';
        t.color = ConsoleColor::DarkBlue;
        break;
    case ' ':
        t.bloque = L' ';
        t.color = ConsoleColor::Black;
        break;
    default:
        t.bloque = c;
        t.color = ConsoleColor::Gray;
        break;
    }

    return t;
}
