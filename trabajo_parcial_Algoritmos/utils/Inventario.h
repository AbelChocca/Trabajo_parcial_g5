#pragma once
#include <unordered_map>
#include <string>
#include <vector>

class Item;
class EstructuraEstatica;
class Jugador;


struct ItemInventory {
	Item* memoryItem;
	EstructuraEstatica* inventoryItem;
	short cantidad;
};

class Inventario
{
private:
	std::unordered_map<std::string, ItemInventory> items;
	std::vector<std::string> orden;
	bool item_equipado;
	Item* itemEquipado;
public:
	Inventario();
	~Inventario();

	Item*& getItemEquipado() { return this->itemEquipado; }
	bool& hayItemEquipado() { return this->item_equipado; }
	void desequiparItem();
	void equiparItem(short indice);
	void utilizarItem(char c, Jugador* jugador);
	void seleccionarItem(Jugador* jugador);
	void renderItems();
	void agregarItem(Item* item);
};