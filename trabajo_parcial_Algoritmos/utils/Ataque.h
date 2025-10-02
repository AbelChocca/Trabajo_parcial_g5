
class EstructuraDinamica;

class Ataque 
{
private:
	short da�o;

	void renderizarDestino(EstructuraDinamica* destino);
public:
	Ataque();
	~Ataque();

	void colisionAtaque(EstructuraDinamica* entidad);
	void lanzarAtaque();
};