#pragma once

#include "Map.h"
#include "InputHandler.h"

class Menu {
private:
    Estructura* layout;     
    InputHandler* input;    
    int opcionSeleccionada;

public:
    Menu();
    ~Menu();

    void mostrar();
    int getOpcion(); 
};