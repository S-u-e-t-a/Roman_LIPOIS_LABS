#include "AboutProgram.h"

#include <iostream>

#include "mainMenu.h"

AboutProgram::AboutProgram()
{
	text = "Эта программа выводит первые слова предложений в тексте\n\n"
	"Автор: Хлебников Роман\n"
	"Группа: 494\n"
	"Лабораторная работа №1\n"
	"Вариант 18";
}

void AboutProgram::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void AboutProgram::chooseVariant()
{
	std::cout << "Для продолжения нажмите любую клавишу......";
	std::string someChar;
	std::getline(std::cin, someChar);
	ClearScreenAndPrintNew(std::make_shared<MainMenu>());
}
