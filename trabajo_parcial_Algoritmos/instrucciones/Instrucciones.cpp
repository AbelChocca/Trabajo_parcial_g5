#include "Instrucciones.h"
#include "../selector/Selector.h"
#include "../levels/level2/mundo1_tile_control.h"
#include "../core/Game.h"
#include "../menu/Menu.h"
#include "../core/Map.h"
#include <conio.h>

// =========================================================
// Constructor
// =========================================================
Instrucciones::Instrucciones(short ancho, short alto) {
    this->ancho = ancho;
    this->alto = alto;

    layout = new EstructuraEstatica(0, 0);
    layout->loadMap(
        "assets/instrucciones.txt",
        tile_control::InstruccionesCharToTile
    );
    input = nullptr;
}

// =========================================================
// Destructor
// =========================================================
Instrucciones::~Instrucciones() {
    delete layout;
    if (input) delete input;
}

// =========================================================
// Mostrar mapa + texto
// =========================================================
void Instrucciones::mostrar() {
    Console::Clear();
    if (layout) layout->render();

    Console::ForegroundColor = ConsoleColor::White;
    Console::BackgroundColor = ConsoleColor::Black;

    int textoX = 56;
    int textoY = 11;

    Console::SetCursorPosition(textoX, textoY);
    Console::WriteLine("INSTRUCCIONES DEL JUEGO:");

    Console::SetCursorPosition(textoX, textoY + 2);
    Console::WriteLine("1. Usa las teclas AWSD para mover el personaje.");
    Console::SetCursorPosition(textoX, textoY + 3);
    Console::WriteLine("   Enter para continuar y Q para retroceder.");

    Console::SetCursorPosition(textoX, textoY + 5);
    Console::WriteLine("2. Evita enemigos y recoge objetos.");

    Console::SetCursorPosition(textoX, textoY + 7);
    Console::WriteLine("3. Llega al final del nivel para ganar.");

    Console::SetCursorPosition(textoX, textoY + 9);
    Console::WriteLine("Presiona Q para regresar al menu principal...");
}

// =========================================================
// Update
// =========================================================
void Instrucciones::update() {
    if (layout) layout->render();
}

// =========================================================
// Manejo de Input
// =========================================================
void Instrucciones::handleInput(Game* game, char tecla) {
    if (tecla == 'q' || tecla == 'Q') {
        game->setState(new Menu());
        return;
    }
}
