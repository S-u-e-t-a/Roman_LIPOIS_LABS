#include "ChooseInputType.h"
#include <iostream>

#include "InputFromFile.h"
#include "InputFromKeyboard.h"
using namespace std;

ChooseInputType::ChooseInputType()
{
	text = "����������� ��� ������ ����� �����������\n����� ���� �����\n1. � ����������\n2. �� �����";
}


void ChooseInputType::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void ChooseInputType::chooseVariant()
{
	cout << "�������� ������ �������:\n " << std::endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("������� ����� �� 1 �� 2", FromKeyboard, FromFile);
	switch (variant)
	{
	case FromKeyboard:
		ClearScreenAndPrintNew(std::make_shared<InputFromKeyboard>());
		break;
	case FromFile:
		ClearScreenAndPrintNew(std::make_shared<InputFromFile>());
		break;
	default:
		cout << "���-�� ����� �� ���....";
		chooseVariant();
		break;
	}
}
