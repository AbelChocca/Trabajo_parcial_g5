#include "Laser.h"
#include <queue>
#include <algorithm>

using namespace std;

Laser::Laser(EstructuraEstatica* fondo, Entidad* origen, Entidad* objetivo) {
    this->fondo = fondo;
    this->objetivo = objetivo;
    this->activo = true;
    this->pasoActual = 0;

    int alto = fondo->getAlto();
    int ancho = fondo->getAncho();
    queue<NodoLaser> q;
    vector<vector<bool>> visitado(alto, vector<bool>(ancho, false));
    vector<vector<NodoLaser>> padre(alto, vector<NodoLaser>(ancho, { -1,-1 }));

    NodoLaser inicio = {
        origen->getCuerpo()->getPosX() + origen->getCuerpo()->getAncho() / 2,
        origen->getCuerpo()->getPosY() + origen->getCuerpo()->getAlto() / 2
    };

    NodoLaser dest = {
        objetivo->getCuerpo()->getPosX() + objetivo->getCuerpo()->getAncho() / 2,
        objetivo->getCuerpo()->getPosY() + objetivo->getCuerpo()->getAlto() / 2
    };

    q.push(inicio);
    visitado[inicio.y][inicio.x] = true;
    bool encontrado = false;

    int dx[4] = { 1,-1,0,0 };
    int dy[4] = { 0,0,1,-1 };

    while (!q.empty() && !encontrado) {
        NodoLaser actual = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = actual.x + dx[i];
            int ny = actual.y + dy[i];

            if (nx >= 0 && nx < ancho && ny >= 0 && ny < alto && !visitado[ny][nx] &&
                !fondo->getGrafico()[ny][nx].isSolid) {

                visitado[ny][nx] = true;
                padre[ny][nx] = actual;
                NodoLaser siguiente;
                siguiente.x = nx;
                siguiente.y = ny;
                q.push(siguiente);

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

    NodoLaser paso = dest;
    while (!(paso.x == inicio.x && paso.y == inicio.y)) {
        recorrido.push_back(paso);
        paso = padre[paso.y][paso.x];
    }
    std::reverse(recorrido.begin(), recorrido.end());
}

Laser::~Laser() {}

void Laser::renderAtaque() {
    if (!activo || pasoActual >= recorrido.size()) return;

    NodoLaser& n = recorrido[pasoActual];
    Console::SetCursorPosition(n.x, n.y);
    Console::ForegroundColor = ConsoleColor::Cyan;
    std::wcout << L'█';
    Console::ForegroundColor = ConsoleColor::White;
}

void Laser::borrarAtaque() {
    if (pasoActual == 0) return;

    NodoLaser& n = recorrido[pasoActual - 1];
    Console::SetCursorPosition(n.x, n.y);
    Console::ForegroundColor = ConsoleColor::Black;
    std::wcout << L' ';
    Console::ForegroundColor = ConsoleColor::White;
}

void Laser::ejecutarAtaque() {
    if (!activo) return;

    borrarAtaque();

    renderAtaque();

    NodoLaser& n = recorrido[pasoActual];
    EstructuraDinamica* cuerpo = objetivo->getCuerpo();
    if (n.x >= cuerpo->getPosX() && n.x < cuerpo->getPosX() + cuerpo->getAncho() &&
        n.y >= cuerpo->getPosY() && n.y < cuerpo->getPosY() + cuerpo->getAlto()) {
        activo = false;
        objetivo->recibirDaño(daño);
        return;
    }

    pasoActual++;

    if (pasoActual >= recorrido.size()) activo = false;
}
