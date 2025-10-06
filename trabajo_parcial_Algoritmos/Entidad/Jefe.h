#pragma once
#include "../utils/BarraVida.h"
#include "../core/Config.h"
#include <vector>
#include <cstdlib>
#include <ctime>

class EstructuraDinamica;
class Ataque;
class Entidad;

class Jefe
{
private:
    BarraVida vida;
    std::vector<Ataque*> ataques;
    EstructuraDinamica* cuerpo;
    Entidad* objetivo;
    std::vector<std::vector<std::vector<Tile>>> sprites;
    float faseActual;   
    bool fase30Activada;

public:
    Jefe(Entidad* objetivo, EstructuraEstatica* fondo);
    ~Jefe();

    BarraVida& getBarraVida() { return this->vida; }
    void renderCuerpo();          
    void actualizarVida(short daño);
    bool estaVivo();        

    void ejecutarAtaqueRandom(); 
    void actualizarFase();      
};
