#pragma

class EstructuraEstatica;

class BarraVida
{
private:
	short vida;
	short posX;
	short posY;

public:
	BarraVida();
	~BarraVida();

	void actualizarBarra(short& da�o);
	void renderizarBarra();
};