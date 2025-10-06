#include "Explosivo.h"
#include "../core/Config.h"
#include <thread>
#include <algorithm>

Explosivo::Explosivo(short x, short y, EstructuraEstatica* fondo, Entidad* objetivo) {
    this->posX = x;
    this->posY = y;
    this->fondo = fondo;
    this->daño = 30;
    this->activo = true;
    this->objetivo = objetivo;
    this->indiceSprite = 0;
    this->explotando = false;
    this->pasoActual = 0;

    calcularBFS();
}

Explosivo::~Explosivo() {
    for (auto s : spritesExplosion)
        delete s;
}

void Explosivo::calcularBFS() {
    short alto = fondo->getAlto();
    short ancho = fondo->getAncho();

    std::vector<std::vector<bool>> visitado(alto, std::vector<bool>(ancho, false));
    std::vector<std::vector<NodoExplosivo>> padre(alto, std::vector<NodoExplosivo>(ancho, { -1,-1 }));
    std::queue<NodoExplosivo> q;

    NodoExplosivo inicio = { posX, posY };
    NodoExplosivo destino = { objetivo->getCuerpo()->getPosX(), objetivo->getCuerpo()->getPosY() };

    q.push(inicio);
    visitado[inicio.y][inicio.x] = true;

    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };

    bool encontrado = false;

    while (!q.empty() && !encontrado) {
        NodoExplosivo actual = q.front(); q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = actual.x + dx[i];
            int ny = actual.y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < ancho && ny < alto && !visitado[ny][nx]) {
                if (!fondo->getGrafico()[ny][nx].isSolid) {
                    visitado[ny][nx] = true;
                    padre[ny][nx] = actual;
                    NodoExplosivo siguiente;
                    siguiente.x = nx;
                    siguiente.y = ny;
                    q.push(siguiente);

                    if (nx == destino.x && ny == destino.y) {
                        encontrado = true;
                        break;
                    }
                }
            }
        }
    }

    if (!encontrado) return;

    NodoExplosivo paso = destino;
    while (!(paso.x == inicio.x && paso.y == inicio.y)) {
        camino.push_back(paso);
        paso = padre[paso.y][paso.x];
    }
    std::reverse(camino.begin(), camino.end());
}

void Explosivo::renderAtaque() {
    if (!activo) return;

    if (!explotando) {
        Console::SetCursorPosition(posX, posY);
        Console::ForegroundColor = ConsoleColor::Black;
        Console::Write(L'█');
    }
    else {
        if (indiceSprite < spritesExplosion.size())
            spritesExplosion[indiceSprite]->render();
    }

    Console::ForegroundColor = ConsoleColor::White;
}

void Explosivo::borrarAtaque() {
    if (!activo) return;

    if (!explotando) {
        Console::SetCursorPosition(posX, posY);
        Console::ForegroundColor = ConsoleColor::Black;
        Console::Write(this->fondo->getGrafico()[posY][posX].bloque);
    }
    else {
        if (indiceSprite < spritesExplosion.size()) {
            spritesExplosion[indiceSprite]->borrar();
        }
    }
    Console::ForegroundColor = ConsoleColor::White;
}

void Explosivo::ejecutarAtaque() {
    if (!this->activo) return;

    borrarAtaque();

    if (!explotando) {
        if (pasoActual < camino.size()) {
            this->posX = camino[pasoActual].x;
            this->posY = camino[pasoActual].y;
            this->pasoActual++;
        }
        else {
            this->explotando = true;
            this->indiceSprite = 0;
        }
    }
    else {
        explotar();
    }

    renderAtaque();
}

void Explosivo::explotar() {
    if (indiceSprite >= spritesExplosion.size()) {
        activo = false;
        return;
    }

    short ancho = spritesExplosion[indiceSprite]->getAncho();
    short alto = spritesExplosion[indiceSprite]->getAlto();
    short x0 = posX;
    short y0 = posY;

    EstructuraDinamica* e = objetivo->getCuerpo();
    if (this->objetivo) {
        short ex = e->getPosX();
        short ey = e->getPosY();
        short ew = e->getAncho();
        short eh = e->getAlto();

        if (x0 + ancho > ex && x0 < ex + ew &&
            y0 + alto > ey && y0 < ey + eh) {
            this->objetivo->recibirDaño(daño);
        }
    }

    indiceSprite++;
}

void Explosivo::reset(short x, short y) {
     this->posX = x;
     this->posY = y;
     this->activo = true;
     this->pasoActual = 0;
     this->explotando = false;
     this->calcularBFS();
    
}