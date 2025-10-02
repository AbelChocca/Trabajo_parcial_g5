#include "enemigo.h"
#include "../core/Map.h"

Enemigo::Enemigo(EstructuraDinamica* cuerpo)
{
	this->dx = 2;
	this->dy = 1;
	this->estructura = cuerpo;
}

Enemigo::~Enemigo()
{
	delete this->estructura;
}
void Enemigo::atacar() {

}

bool Enemigo::detectarColision(EstructuraDinamica* entidad) {
    short posX = this->estructura->getPosX();
    short posY = this->estructura->getPosY();
    short ancho = this->estructura->getAncho();
    short alto = this->estructura->getAlto();

    short entePosX = entidad->getPosX();
    short entePosY = entidad->getPosY();
    short enteAncho = entidad->getAncho();
    short enteAlto = entidad->getAlto();
    Tile** grafico = this->estructura->getFondo()->getGrafico();
    
    if ((entePosX < posX + ancho) &&
        (entePosX + enteAncho > posX) &&
        (entePosY + enteAlto > posY) &&
        (entePosY < posY + alto)
        ) {
        return true;
    }

    if (posX + ancho >= MAX_WIDTH) {
        this->dx *= -1;
        return false;
    }

    if (posX <= 0) {
        this->dx *= -1;
        return false;
    }

    if (this->dx > 0) {
        int bordeDerecho = posX + ancho;
        for (int y = posY; y < posY + alto; y++) {
            if (bordeDerecho >= MAX_WIDTH) break;
            if (y < 0 || y >= MAX_HEIGHT) continue; 
            if (grafico[y][bordeDerecho].isSolid) {
                this->dx *= -1;
                return false;
            }
        }
    }
    else if (this->dx < 0) {
        int bordeIzquierdo = posX - 1;
        for (int y = posY; y < posY + alto; y++) {
            if (bordeIzquierdo < 0) break;
            if (y < 0 || y >= MAX_HEIGHT) continue;
            if (grafico[y][bordeIzquierdo].isSolid) {
                this->dx *= -1;
                return false;
            }
        }
    }

    return false;
}
