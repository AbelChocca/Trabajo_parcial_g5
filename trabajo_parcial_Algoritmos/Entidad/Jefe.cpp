#include "Jefe.h"
#include "../Entidad/Entidad.h"
#include "../ataque/Ataque.h"
#include "../core/UtilsFunc.h"
#include "../ataque/Explosivo.h"
#include "../ataque/RayoCentinela.h"
#include "../levels/level3/mundo3_tile_control.h"


Jefe::Jefe(Entidad* objetivo, EstructuraEstatica* fondo) :
	vida(380, 80, 5)
{
    this->fase30Activada = false;
    this->faseActual = 1.0f;
    this->cuerpo = new EstructuraDinamica(100, 15, fondo);
    this->cuerpo->loadMap("assets/mundo3_jefe_sprite1.txt", tile_control::JefeCharToTile);
    this->objetivo = objetivo;
    ataques.push_back(new Explosivo(100, 33, fondo, objetivo));
    ataques.push_back(new RayoCentinela(100, 33, fondo, objetivo));

    FrameLoader::cargarFrame(this->sprites, "assets/mundo3_jefe_sprite1.txt", tile_control::JefeCharToTile);
    FrameLoader::cargarFrame(this->sprites, "assets/mundo3_jefe_sprite2.txt", tile_control::JefeCharToTile);
    FrameLoader::cargarFrame(this->sprites, "assets/mundo3_jefe_sprite3.txt", tile_control::JefeCharToTile);
    
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}
Jefe::~Jefe() {
    delete cuerpo;
    for (auto a : ataques)
        delete a;
}

void Jefe::renderCuerpo() {
    if (cuerpo)
        cuerpo->render();
}
bool Jefe::estaVivo() {
    return this->vida.getVida() > 0;
}
void Jefe::actualizarVida(short daño) {
    this->vida.actualizarBarra(daño);
    this->actualizarFase();
}
void Jefe::actualizarFase() {
    float porcentaje = (float)vida.getVida() / vida.getVidaMaxima();

    if (porcentaje <= 0.3f && !fase30Activada) {
        if (this->sprites.size() > 2)
            this->cuerpo->setSprite(this->sprites[2]);
        fase30Activada = true;
    }
    else if (porcentaje <= 0.5f && porcentaje > 0.3f) {
        if (this->sprites.size() > 1)
            this->cuerpo->setSprite(sprites[1]);
    }
    faseActual = porcentaje;
}

void Jefe::ejecutarAtaqueRandom() {
    if (ataques.empty()) return;

    int index = std::rand() % this->ataques.size();

    ataques[index]->reset(this->cuerpo->getPosX(), this->cuerpo->getPosY());
    ataques[index]->ejecutarAtaque();
}