#include <iostream>
#include "interface.h"

#include <windows.h>

/// <summary>
/// Точка входа в программу
/// </summary>
/// <returns></returns>
int main()
{
	system("color F0");
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (MainMenu() != Exit);
	return 1;
}
