#include "mundo1_tile_control.h"
#include "../../core/Config.h"

using namespace System;

namespace tile_control {
	Tile Character1CharToTile(char c) {
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
		default:
			t.bloque = c;
			t.color = ConsoleColor::Black;
			break;
		}
		return t;
	}

	Tile IA1CharToTile(char c) {
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
	Tile E11CharToTile(char c) {
		Tile t;
		t.isSolid = false;
		switch (c)
		{
		case '*':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGray;
			break;
		case 'G':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGray;
			break;
		case 'K':
			t.bloque = L'█';
			t.color = ConsoleColor::Gray;
			break;
		case 'N':
			t.bloque = L'█';
			t.color = ConsoleColor::Black;
			break;
		case 'B':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkRed;
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
	Tile Dialog1CharToTile(char c) {
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

	Tile Xaro1CharToTile(char c) {
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
	Tile E21CharToTile(char c) {
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
			t.color = ConsoleColor::DarkBlue;
			t.isSolid = true;
			break;
		case '0':
			t.bloque = L'█';
			t.color = ConsoleColor::White;
			break;
		case '4':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkCyan;
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
			t.color = ConsoleColor::DarkBlue;
			t.isSolid = false;
			break;
		case '1':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGray;
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

	Tile E1M1CharToTile(char c) {
		Tile t;

		switch (c)
		{
		case 'G':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkGray;
			break;
		case 'K':
			t.bloque = L'█';
			t.color = ConsoleColor::Gray;
			break;
		case 'N':
			t.bloque = L'█';
			t.color = ConsoleColor::Black;
			break;
		case 'B':
			t.bloque = L'█';
			t.color = ConsoleColor::DarkRed;
			break;
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
	Tile Panel1CharToTile(char c) {
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
	Tile InstruccionesCharToTile(char c) {
		Tile t;
		t.bloque = L'█'; // 🔹 AHORA siempre usa bloque █
		t.isSolid = false;
		t.tipo = ' ';
		t.color = ConsoleColor::White;        // color de letra

		switch (c) {
		case '.':
			t.color = ConsoleColor::DarkBlue; break;
		case '-':
			t.color = ConsoleColor::DarkGreen; break;
		case 'G':
			t.color = ConsoleColor::White; break;
		case '=':
			t.color = ConsoleColor::Gray; break;
		case 'M':
			t.color = ConsoleColor::White; break;
		case 'B':
			t.color = ConsoleColor::White; break;
		case 'N':
			t.color = ConsoleColor::Black; break;
		case 'P':
			t.color = ConsoleColor::Red; break;
		case 'C':
			t.color = ConsoleColor::Cyan; break;
		case 'Y':
			t.color = ConsoleColor::DarkYellow; break;
		case 'R':
			t.color = ConsoleColor::DarkRed; break;
		default:
			t.color = ConsoleColor::DarkBlue; break;
		}
		return t;
	}
}