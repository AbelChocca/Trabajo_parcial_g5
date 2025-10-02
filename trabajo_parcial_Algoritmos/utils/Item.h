#pragma once
#include <string>

class EstructuraEstatica;

class Item
{
private:
	short cantidad;
	EstructuraEstatica* ascii;
	std::string tipo;

public:
	virtual ~Item() = 0;

	virtual void usarItem() = 0;
	virtual void renderItem() = 0;
};