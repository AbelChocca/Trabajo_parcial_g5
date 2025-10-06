#include "IA.h"
#include "../levels/level3/mundo3_tile_control.h"
#include "../ataque/Laser.h"
#include <queue>
#include <thread>


IA::IA(short x, short y, EstructuraEstatica* fondo) {
    EstructuraDinamica* estructura = new EstructuraDinamica(x, y, fondo);
    estructura->loadMap("assets/ia_sprite1.txt", tile_control::IACharToTile);
    this->cuerpo = estructura;
    this->tipo = "IA";
}

IA::~IA() {

}
bool IA::pasilloValido(short tx, short ty) {
    int anchoMapa = this->cuerpo->getFondo()->getAncho();
    int altoMapa = this->cuerpo->getFondo()->getAlto();

    if (tx < 0 || ty < 0 || tx >= anchoMapa || ty >= altoMapa) {
        return false;
    }

    Tile t = this->cuerpo->getFondo()->getGrafico()[ty][tx];
    return !t.isSolid;
}
void IA::moverIAhaciaDestino(short destinoX, short destinoY) {
    short alto = this->cuerpo->getFondo()->getAlto();
    short ancho = this->cuerpo->getFondo()->getAncho();
    queue<Nodo> q;
    vector<vector<bool>> visitado(alto,
        vector<bool>(ancho, false));
    vector<vector<Nodo>> padre(alto,
        vector<Nodo>(ancho, { -1,-1 }));

    Nodo inicio = {
    this->cuerpo->getPosX() + this->cuerpo->getAncho() / 2,
    this->cuerpo->getPosY() + this->cuerpo ->getAlto() / 2
    };

    Nodo destino = {
        destinoX,
        destinoY
    };


    q.push(inicio);
    visitado[inicio.y][inicio.x] = true;

    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };

    bool encontrado = false;

    while (!q.empty() && !encontrado) {
        Nodo actual = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = actual.x + dx[i];
            int ny = actual.y + dy[i];

            if (this->pasilloValido(nx, ny) && !visitado[ny][nx]) {
                visitado[ny][nx] = true;
                padre[ny][nx] = actual;
                q.push({ nx, ny });

                if (nx == destino.x && ny == destino.y) {
                    encontrado = true;
                    break;
                }
            }
        }
    }

    if (!encontrado) return;

    vector<Nodo> camino;
    Nodo paso = destino;
    while (!(paso.x == inicio.x && paso.y == inicio.y)) {
        camino.push_back(paso);
        paso = padre[paso.y][paso.x];
    }
    reverse(camino.begin(), camino.end());

    for (auto& next : camino) {
        this->cuerpo->borrar();

        this->cuerpo->setPosX(next.x - this->cuerpo->getAncho() / 2);
        this->cuerpo->setPosY(next.y - this->cuerpo->getAlto() / 2);

        this->cuerpo->render();
    }
}
void IA::dispararLaser(Entidad* objetivo) {
    if (!objetivo) return;

    Laser* nuevoLaser = new Laser(objetivo->getCuerpo()->getFondo(), this,  objetivo);

    // Lanzar thread
    std::thread([nuevoLaser]() {
        while (nuevoLaser->estaActivo()) {
            nuevoLaser->ejecutarAtaque();
            Sleep(50);
        }
        delete nuevoLaser;
        }).detach();
}