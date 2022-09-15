#include <iostream>
#include "interfacePrinter.h"
#include "mainMenu.h"
#include "WorkWithStrings.h"
#include <windows.h>

int main()
{
	setlocale(LC_ALL, "RU");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::shared_ptr<MainMenu> menu(new MainMenu);
	menu->Show();
}
