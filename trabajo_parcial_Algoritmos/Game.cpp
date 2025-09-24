#include "Game.h"

Game::Game() {
    running = true;
    menu = new Menu();
}

Game::~Game() {
    delete menu;
}

void Game::iniciar() {
    config::SetupConsole();
    config::SetupFont();
    config::SetupEncoding();
    config::basicConfig();

    // Renderizar menú solo una vez
    menu->mostrar();

    while (running) {
        update();   // solo procesa input
        Sleep(100);
    }
}

void Game::render() {
    Console::Clear();

    // Renderizar el menú
    if (menu) {
        menu->mostrar();
    }
}

void Game::update() {
    if (_kbhit()) {
        char tecla = _getch();
    }
}

void Game::salir() {
    running = false;
}
