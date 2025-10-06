#include "Game.h"

Game::Game() {
    running = true;
    currentState = new Menu();
}

Game::~Game() {
    delete currentState;
}
GameState* Game::getState() {
    return this->currentState;
}

void Game::iniciar() {
    config::SetupConsole();
    config::SetupFont();
    config::SetupEncoding();
    config::basicConfig();

    this->render();

    while (running) {
        if (_kbhit()) {
            char tecla = _getch();
            currentState->handleInput(this, tecla);
        }
        currentState->renderAnimation();
        Sleep(20);
    }
}

void Game::render() {
    Console::Clear();

    if (currentState) {
        currentState->mostrar();
    }
}

void Game::update() {
    if (currentState) {
        currentState->update();
    }
}

void Game::salir() {
    running = false;
}

void Game::setState(GameState* newState) {
    if (currentState) delete currentState;
    this->currentState = newState;

    if (currentState) currentState->mostrar();
}