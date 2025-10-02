#include "Inventario.h"


Inventario::Inventario()
{
}

Inventario::~Inventario()
{
}

void Inventario::renderItems() {

}

void Inventario::agregarItem(Item* item) {
	this->items.push_back(item);
}