#include "Config.h"


namespace config {
	void SetupConsole() {
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD bufferSize;
		bufferSize.X = 150;
		bufferSize.Y = 80;
		SetConsoleScreenBufferSize(hOut, bufferSize);

		SMALL_RECT windowSize;
		windowSize.Left = 0;
		windowSize.Top = 0;
		windowSize.Right = bufferSize.X - 1;
		windowSize.Bottom = bufferSize.Y - 1;
		SetConsoleWindowInfo(hOut, TRUE, &windowSize);
	}
	void SetupFont() {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 8;
		cfi.dwFontSize.Y = 10;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	}
	void SetupEncoding() {
		SetConsoleOutputCP(CP_UTF8);
		_setmode(_fileno(stdout), _O_U8TEXT);
	}
	void basicConfig() {
		Console::CursorVisible = false;
	}
}