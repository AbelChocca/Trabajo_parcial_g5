#pragma once
#include "../../core/GameState.h"
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

class IA;
class Jefe;
class Jugador;
class EstructuraEstatica;

class Mundo3Escenario3 : public GameState {
private:
    EstructuraEstatica* fondo;
    vector<EstructuraEstatica*> mensajes;
    short indice_mensaje;
    Jugador* jugadorEntity;
    IA* IAEntity;
    Jefe* jefeFinal;

    std::thread threadJefe;
    std::atomic<bool> activo;

    bool* mostrar_dialogo;
    bool* guardarIA;

public:
    Mundo3Escenario3(
        bool* mostrar_dialogo,
        bool* guardarIA,
        Jugador* jugador,
        IA* IA
    );
    ~Mundo3Escenario3();

    void iniciarThreads();
    void detenerThreads();
    void mostrarDialogo();

    void handleDialog(char tecla) override;
    void mostrar() override;
    void update() override;
    void renderAnimation() override;
    void handleInput(Game* game, char tecla) override;
    bool setColisionCondition(char c, EstructuraDinamica*& entity) override;
};
