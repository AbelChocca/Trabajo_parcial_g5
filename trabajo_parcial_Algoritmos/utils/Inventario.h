#pragma once
#include <vector>

class Item;
class EstructuraEstatica;

class Inventario
{
private:
	std::vector<Item*> items;

public:
	Inventario();
	~Inventario();

	void renderItems();
	void agregarItem(Item* item);
};