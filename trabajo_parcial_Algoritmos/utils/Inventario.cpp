#include "Inventario.h"
#include "../utils/Item.h"
#include "../core/Map.h"
#include "../Entidad/Jugador.h"
#include <conio.h>


Inventario::Inventario()
{
	this->item_equipado = false;
	this->itemEquipado = nullptr;
}

Inventario::~Inventario()
{
}

void Inventario::utilizarItem(char c, Jugador* jugador) {
	if (this->item_equipado) return;
	short indice = c - '0';
	if (indice < 0 || indice >= this->orden.size()) return;

	std::string nombre = this->orden[indice];

	ItemInventory& slot = this->items[nombre];
	slot.memoryItem->usarItem(jugador);
	slot.cantidad--;
	if (slot.cantidad <= 0) {
		this->items.erase(nombre);

		this->orden.erase(this->orden.begin() + indice);
	}
	
}
void Inventario::desequiparItem() {
	this->itemEquipado = nullptr;
	this->item_equipado = false;
}
void Inventario::equiparItem(short indice) {
	if (this->item_equipado) return;
	if (indice < 0 || indice >= this->orden.size()) return;
	std::string& nombre = this->orden[indice];
	ItemInventory& slot = this->items[nombre];

	this->itemEquipado = slot.memoryItem;
	this->item_equipado = true;
}
void Inventario::seleccionarItem(Jugador* jugador) {
	char teclita = _getch();
	if (!std::isdigit(teclita)) {
		return;
	}
	short indice = teclita - '0';
	if (indice < 0|| indice > this->orden.size()) {
		return;
	}
	this->equiparItem(indice);
}
void Inventario::renderItems() {
	if (this->orden.empty()) return;
	short k = 0;
	short posX = 154;
	short posY = 41;
	for (const auto& nombre : this->orden) {
		ItemInventory& slot = this->items[nombre];
		Tile** item = slot.inventoryItem->getGrafico();
		short cantidad = slot.cantidad;

		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 21; j++) {
				short x = posX + j;
				short y = posY + i + (k*8);
				Tile t = item[i][j];

				if (t.bloque != L' ') {
					int color = static_cast<int>(t.color);
					if (color < static_cast<int>(ConsoleColor::Black) ||
						color > static_cast<int>(ConsoleColor::White)) {
						color = static_cast<int>(ConsoleColor::Gray); // color seguro
					}

					Console::ForegroundColor = static_cast<ConsoleColor>(color);
					Console::SetCursorPosition(posX + j, posY + i + (k * 8));
					Console::Write(t.bloque);
				}
			}
		}

		Console::ForegroundColor = ConsoleColor::White;
		Console::SetCursorPosition(posX + 15, posY + 5 + (k * 8));
		Console::Write("x");
		Console::Write(cantidad.ToString());


		k++;
	}
}

void Inventario::agregarItem(Item* item) {
	std::string nombre = item->getNombre();
	if (this->items.find(nombre) != this->items.end()) {
		this->items[nombre].cantidad++;
	}
	else {
		ItemInventory nuevoSlot;
		nuevoSlot.memoryItem = item;
		nuevoSlot.inventoryItem = new EstructuraEstatica(*(item->getInventoryItem()));
		nuevoSlot.cantidad = 1;
		this->items[nombre] = nuevoSlot;
		this->orden.push_back(nombre);
	}

	this->renderItems();
}