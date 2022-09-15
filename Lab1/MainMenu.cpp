#include "mainMenu.h"
#include "WorkWithStrings.h"
#include <iostream>

#include "AboutProgram.h"
using namespace std;


MainMenu::MainMenu()
{
	text = "\t������� ����:\n"
	"1. ������ �� ��������\n"
	"2. � ���������\n"
	"3. �����";
}

void MainMenu::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void MainMenu::chooseVariant()
{
	cout << "�������� ������ �������:" << std::endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("������� ����� �� 1 �� 3", ShowWorkWithStringsMenu, Exit);
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
		cout << "���-�� ����� �� ���....";
		chooseVariant();
		break;
	}
}
