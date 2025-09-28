#pragma once

class Game;

class GameState
{
public:
    virtual ~GameState() = default;

    virtual void handleInput(Game* game, char tecla) = 0;
    virtual void update() = 0;
    virtual void mostrar() = 0;

};