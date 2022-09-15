#include "WorkWithStrings.h"
#include <iostream>
#include "mainMenu.h"
#include "ChooseInputType.h"
using namespace std;

WorkWithStrings::WorkWithStrings()
{
	text = "������ �� ��������\n1. ����������� ��� ������ ����� �����������.\n2. ��������� � ������� ����";
}

void WorkWithStrings::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void WorkWithStrings::chooseVariant()
{
	cout << "�������� ������ �������:" << std::endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("������� ����� �� 1 �� 2", PrintAllFirstWordsOfSentence,
	                                                       BackToMenu);
	switch (variant)
	{
	case PrintAllFirstWordsOfSentence:
		ClearScreenAndPrintNew(std::make_shared<ChooseInputType>());
		break;
	case BackToMenu:
		ClearScreenAndPrintNew(std::make_shared<MainMenu>());
		break;
	default:
		cout << "���-�� ����� �� ���....";
		chooseVariant();
		break;
	}
}
