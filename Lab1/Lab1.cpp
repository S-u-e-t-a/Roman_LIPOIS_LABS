#include <iostream>
#include "interface.h"

#include <windows.h>

/// <summary>
/// ����� ����� � ���������
/// </summary>
/// <returns></returns>
int main()
{
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (MainMenu() != Exit);
	return 1;
}
