// InputHandler.cpp
#include "InputHandler.h"
#include "Map.h"

InputHandler::InputHandler() {
    this->flecha = new Estructura(0, 0);
}

InputHandler::~InputHandler() {
    delete flecha;
}
