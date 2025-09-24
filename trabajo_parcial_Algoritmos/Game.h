#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include "Menu.h"

using namespace std;
using namespace System;

namespace config {
	void SetupConsole();
	void SetupFont();
	void SetupEncoding();
	void basicConfig();
}

class Game {
private:
    bool running;

    Menu* menu;

public:
    Game();
    ~Game();

    void iniciar();
    void render();
    void update();
    void salir();
};


