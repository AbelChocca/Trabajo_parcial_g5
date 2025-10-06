#pragma once
#include "../../core/GameState.h"
#include "../../Entidad/Jugador.h"
#include "../../Entidad/IA.h"
#include "../../enemigo/enemigo.h"
#include "../../core/Config.h"
#include "../../core/Map.h"
#include <vector>

class Mundo1Escenario2 : public GameState {
private:
    Jugador* jugadorEntity;
    IA* IAEntity;
    bool* mostrar_dialogo;
    bool* guardarIA;
    EstructuraEstatica* fondo;

    std::vector<EstructuraEstatica*> mensajes;
    std::vector<Enemigo*> enemigos;

    bool dialogo_activo = false;
    bool dialogo1_mostrado = false;
    bool dialogo2_mostrado = false;
    int indice_mensaje;

    bool preguntaActiva;
    bool preguntaMostrada;

    // 🟢 NUEVO: para saber cuál enemigo activó la pregunta
    Enemigo* enemigoEnPregunta;

    struct Punto {
        int x, y, ancho, alto;
    } primerPunto;

public:
    Mundo1Escenario2(bool* mostrar_dialogo, bool* guardarIA, Jugador* jugador, IA* ia);
    ~Mundo1Escenario2();

    void mostrar() override;
    void update() override;
    void renderAnimation() override;
    void handleDialog(char tecla);

    void mostrarDialogo();
    void mandarAlInicio();
    bool colisionPrimerPunto();
    bool setColisionCondition(char c, EstructuraDinamica*& entity);

    void updatePreguntas();
    void mostrarPregunta();

    EstructuraEstatica* getFondo();
    short getAncho();
    short getAlto();
};
