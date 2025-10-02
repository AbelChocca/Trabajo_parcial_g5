#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <io.h>
#include <fcntl.h>

using namespace System;

const int MAX_WIDTH = 180;
const int MAX_HEIGHT = 80;

struct Tile
{
	wchar_t bloque;
	bool isSolid;
	char tipo;
	ConsoleColor color;
};

namespace config {
	void SetupConsole();
	void SetupFont();
	void SetupEncoding();
	void basicConfig();
}