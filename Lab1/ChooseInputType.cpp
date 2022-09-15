#include "ChooseInputType.h"
#include <iostream>

#include "InputFromFile.h"
#include "InputFromKeyboard.h"
using namespace std;

ChooseInputType::ChooseInputType()
{
	text = "Распечатать все первые слова предложений\nВыбор типа ввода\n1. С клавиатуры\n2. Из файла";
}


void ChooseInputType::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void ChooseInputType::chooseVariant()
{
	cout << "Выберете нужный вариант:\n " << std::endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("Введите число от 1 до 2", FromKeyboard, FromFile);
	switch (variant)
	{
	case FromKeyboard:
		ClearScreenAndPrintNew(std::make_shared<InputFromKeyboard>());
		break;
	case FromFile:
		ClearScreenAndPrintNew(std::make_shared<InputFromFile>());
		break;
	default:
		cout << "Что-то пошло не так....";
		chooseVariant();
		break;
	}
}
