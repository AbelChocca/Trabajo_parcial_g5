#include "RayoCentinela.h"
#include <queue>
#include <algorithm>

using namespace std;

RayoCentinela::RayoCentinela(short x, short y, EstructuraEstatica* fondo, Entidad* objetivo)
{
    this->posX = x;
    this->posY = y;
    this->fondo = fondo;
    this->objetivo = objetivo;
    this->daño = 30;
    this->activo = true;
    this->pasoActual = 0;

    calcularBFS();
}

RayoCentinela::~RayoCentinela() {}

void RayoCentinela::calcularBFS()
{
    int alto = fondo->getAlto();
    int ancho = fondo->getAncho();

    queue<NodoCentinela> q;
    vector<vector<bool>> visitado(alto, vector<bool>(ancho, false));
    vector<vector<NodoCentinela>> padre(alto, vector<NodoCentinela>(ancho, { -1, -1 }));

    NodoCentinela inicio = { posX, posY };

    NodoCentinela dest = {
        (short)(objetivo->getCuerpo()->getPosX() + objetivo->getCuerpo()->getAncho() / 2),
        (short)(objetivo->getCuerpo()->getPosY() + objetivo->getCuerpo()->getAlto() / 2)
    };

    q.push(inicio);
    visitado[inicio.y][inicio.x] = true;
    bool encontrado = false;

    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };

    while (!q.empty() && !encontrado) {
        NodoCentinela actual = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = actual.x + dx[i];
            int ny = actual.y + dy[i];

            if (nx >= 0 && nx < ancho && ny >= 0 && ny < alto &&
                !visitado[ny][nx] && !fondo->getGrafico()[ny][nx].isSolid) {

                visitado[ny][nx] = true;
                padre[ny][nx] = actual;
                q.push({ (short)nx, (short)ny });

                if (nx == dest.x && ny == dest.y) {
                    encontrado = true;
                    break;
                }
            }
        }
    }

    if (!encontrado) {
        activo = false;
        return;
    }

    NodoCentinela paso = dest;
    while (!(paso.x == inicio.x && paso.y == inicio.y)) {
        recorrido.push_back(paso);
        paso = padre[paso.y][paso.x];
    }
    reverse(recorrido.begin(), recorrido.end());
}

void RayoCentinela::renderAtaque() {
    if (!activo || pasoActual >= recorrido.size()) return;

    NodoCentinela& n = recorrido[pasoActual];
    Console::SetCursorPosition(n.x, n.y);
    Console::ForegroundColor = ConsoleColor::Red;
    Console::Write(L'▓');
    Console::ForegroundColor = ConsoleColor::White;
}

void RayoCentinela::borrarAtaque() {
    if (pasoActual == 0) return;

    NodoCentinela& n = recorrido[pasoActual - 1];
    Console::SetCursorPosition(n.x, n.y);
    Console::Write(this->fondo->getGrafico()[n.y][n.x].bloque);
}

void RayoCentinela::ejecutarAtaque() {
    if (!activo) return;

    borrarAtaque();
    renderAtaque();

    NodoCentinela& n = recorrido[pasoActual];
    EstructuraDinamica* cuerpo = objetivo->getCuerpo();

    if (n.x >= cuerpo->getPosX() && n.x < cuerpo->getPosX() + cuerpo->getAncho() &&
        n.y >= cuerpo->getPosY() && n.y < cuerpo->getPosY() + cuerpo->getAlto()) {
        activo = false;
        objetivo->recibirDaño(daño);
        return;
    }

    pasoActual++;

    if (pasoActual >= recorrido.size())
        activo = false;

    Sleep(10);
}

void RayoCentinela::reset(short x, short y) {
    this->posX = x;
    this->posY = y;
    this->activo = true;
    this->pasoActual = 0;
    this->calcularBFS();
}