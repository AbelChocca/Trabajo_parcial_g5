#include "mundo3_tile_control.h"
#include "../../core/Config.h"

using namespace System;

namespace tile_control {
	Tile CharacterCharToTile(char c) {
		Tile t;

		switch (c)
		{
		case '*':
			t.bloque = L'▒';
			t.color = ConsoleColor::DarkYellow;
			break;
		case '#':
			t.bloque = L'▓';
			t.color = ConsoleColor::Yellow;
			break;
		case '0':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '1':
			t.bloque = L'░';
			t.color = ConsoleColor::Black;
			break;
		case '2':
			t.bloque = L'░';
			t.color = ConsoleColor::DarkGray;
			break;
		case '3':
			t.bloque = L'▒';
			t.color = ConsoleColor::Gray;
			break;
		case '4':
			t.bloque = L'░';
			t.color = ConsoleColor::DarkBlue;
			break;
		case '5':
			t.bloque = L'░';
			t.color = ConsoleColor::Black;
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Black;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::Black;
			break;
		}
		return t;
	}

	Tile IACharToTile(char c) {
		Tile t;
		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '#':
			t.bloque = L'░';
			t.color = ConsoleColor::DarkGray;
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Black;
			break;
		default:
			t.color = ConsoleColor::Black;
			t.bloque = c;
			break;
		}
		return t;
	}
	Tile E1CharToTile(char c) {
		Tile t;
		t.isSolid = false;
		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGray;
			break;
		case '#':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkCyan;
			break;
		case '0':
			t.bloque = L'█';
			t.color = ConsoleColor::Gray;
			break;
		case '1':
			t.bloque = L'█';
			t.color = ConsoleColor::Yellow;
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Cyan;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::Black;
			break;
		}

		return t;
	}
	Tile DialogCharToTile(char c) {
		Tile t;
		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case ' ':
			t.bloque = L'█';
			t.color = ConsoleColor::Black;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::White;
			break;
		}
		return t;
	}

	Tile XaroCharToTile(char c) {
		Tile t;

		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkBlue;
			break;
		case ' ':
			t.bloque = L'█';
			t.color = ConsoleColor::Black;
			break;
		case '(':
		case ')':
			t.bloque = c;
			t.color = ConsoleColor::DarkBlue;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::White;
			break;
		}

		return t;
	}
	Tile E2CharToTile(char c) {
		Tile t;
		switch (c)
		{
		case '#':
			t.bloque = L'█';
			t.color = ConsoleColor::Gray;
			t.isSolid = true;
			break;
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkRed;
			t.isSolid = true;
			break;
		case '0':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '4':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGreen;
			t.isSolid = true;
			break;
		case '.':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkYellow;
			t.isSolid = true;
			break;
		case '6':
			t.bloque = L'█';
			t.color = ConsoleColor::Cyan;
			t.isSolid = true;
			break;
		case '7':
			t.bloque = L'█';
			t.color = ConsoleColor::Yellow;
			t.isSolid = false;
			break;
		case '1':
			t.bloque = L'█';
			t.color = ConsoleColor::Yellow;
			t.isSolid = false;
			break;
		case '8':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkMagenta;
			t.isSolid = true;
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Black;
			t.isSolid = false;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::Black;
			t.isSolid = false;
			break;
		}
		return t;
	}

	Tile ECharToTile(char c) {
		Tile t;

		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkMagenta;
			t.tipo = 'E';
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Black;
			t.tipo = 'E';
			break;
		case '#':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			t.tipo = 'E';
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::Black;
			t.tipo = 'E';
			break;
		}

		return t;
	}
	Tile PanelCharToTile(char c) {
		Tile t;
		switch (c)
		{
		case '*':
		case '0':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			t.isSolid = true;
			break;
		case '#':
			t.bloque = L'█';
			t.color = ConsoleColor::Gray;
			break;
		case '4':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkYellow;
			break;
		case '9':
			t.bloque = L'█';
			t.color = ConsoleColor::Yellow;
			break;
		case '1':
			t.bloque = L'░';
			t.color = ConsoleColor::Black;
			break;
		case '2':
			t.bloque = L'░';
			t.color = ConsoleColor::DarkGray;
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Black;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::White;
			break;
		}
		return t;
	}

	Tile PCurativaCharToTile(char c) {
		Tile t;
		t.isSolid = true;
		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '1':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkYellow;
			break;
		case '2':
			t.bloque = L'█';
			t.color = ConsoleColor::Green;
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Black;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::White;
			break;
		}

		return t;
	}
	Tile ItemDialogoCharToTile(char c) {
		Tile t;
		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '#':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkYellow;
			break;
		case '1':
			t.bloque = L'█';
			t.color = ConsoleColor::Black;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::White;
			break;
		}

		return t;
	}
	Tile PistolaLaserCharToTile(char c) {
		Tile t;
		t.isSolid = true;
		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '1':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGray;
			break;
		case '.':
			t.bloque = L'█';
			t.color = ConsoleColor::Gray;
			break;
		case '2':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkCyan;
			break;
		case '3':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkBlue;
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Black;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::White;
			break;
		}

		return t;
	}
	Tile JugadorConPistolaLaserCharToTile(char c) {
		Tile t;
		switch (c)
		{
		case '*':
			t.bloque = L'▒';
			t.color = ConsoleColor::DarkYellow;
			break;
		case '#':
			t.bloque = L'▓';
			t.color = ConsoleColor::Yellow;
			break;
		case '0':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '1':
			t.bloque = L'░';
			t.color = ConsoleColor::Black;
			break;
		case '2':
			t.bloque = L'░';
			t.color = ConsoleColor::DarkGray;
			break;
		case '3':
			t.bloque = L'▒';
			t.color = ConsoleColor::Gray;
			break;
		case '4':
			t.bloque = L'░';
			t.color = ConsoleColor::DarkBlue;
			break;
		case '.':
			t.bloque = L'░';
			t.color = ConsoleColor::Black;
			break;
		case '5':
			t.bloque = L'█';
			t.color = ConsoleColor::Gray;
			break;
		case '7':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkBlue;
			break;
		case '6':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkCyan;
			break;
		case ' ':
			t.bloque = L' ';
			t.color = ConsoleColor::Black;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::Black;
			break;
		}
		return t;
	}
	Tile E3CharTotTile(char c) {
		Tile t;
		switch (c)
		{
		case '*':
		case '#':
			t.bloque = L'█';
			t.color = ConsoleColor::Gray;
			t.isSolid = false;
			break;
		case '3':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkRed;
			t.isSolid = true;
			break;
		case '1':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkYellow;
			t.isSolid = false;
			break;
		case '2':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGreen;
			t.isSolid = false;
			break;
		case ' ':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkBlue;
			t.isSolid = true;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::White;
			break;
		}
		return t;
	}
	Tile JefeCharToTile(char c) {
		Tile t;
		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkRed;
			break;
		case '#':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '1':
		case '5':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGray;
			break;
		case '2':
			t.bloque = L'█';
			t.color = ConsoleColor::Black;
			break;
		case ' ':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkBlue;
			break;
		default:
			t.bloque = c;
			t.color = ConsoleColor::White;
			break;
		}
		return t;
	}
}