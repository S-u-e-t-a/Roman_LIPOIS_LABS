#include "AboutProgram.h"

#include <iostream>

#include "mainMenu.h"

AboutProgram::AboutProgram()
{
	text = "��� ��������� ������� ������ ����� ����������� � ������\n\n"
	"�����: ��������� �����\n"
	"������: 494\n"
	"������������ ������ �1\n"
	"������� 18";
}

void AboutProgram::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void AboutProgram::chooseVariant()
{
	std::cout << "��� ����������� ������� ����� �������......";
	std::string someChar;
	std::getline(std::cin, someChar);
	ClearScreenAndPrintNew(std::make_shared<MainMenu>());
}
