#include "mainMenu.h"
#include "WorkWithStrings.h"
#include <iostream>

#include "AboutProgram.h"
using namespace std;


MainMenu::MainMenu()
{
	text = "\tГлавное меню:\n"
	"1. Работа со строками\n"
	"2. О программе\n"
	"3. Выход";
}

void MainMenu::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void MainMenu::chooseVariant()
{
	cout << "Выберете нужный вариант:" << std::endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("Введите число от 1 до 3", ShowWorkWithStringsMenu, Exit);
	switch (variant)
	{
	case ShowWorkWithStringsMenu:
		ClearScreenAndPrintNew(std::make_shared<WorkWithStrings>());
		break;
	case About:
		ClearScreenAndPrintNew(std::make_shared<AboutProgram>());
		break;
	case Exit:
		exit(0);
	default:
		cout << "Что-то пошло не так....";
		chooseVariant();
		break;
	}
}
