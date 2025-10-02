
class EstructuraDinamica;

class Ataque 
{
private:
	short daño;

	void renderizarDestino(EstructuraDinamica* destino);
public:
	Ataque();
	~Ataque();

	void colisionAtaque(EstructuraDinamica* entidad);
	void lanzarAtaque();
};