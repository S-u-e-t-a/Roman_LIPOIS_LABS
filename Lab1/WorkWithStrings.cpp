#include "WorkWithStrings.h"
#include <iostream>
#include "mainMenu.h"
#include "ChooseInputType.h"
using namespace std;

WorkWithStrings::WorkWithStrings()
{
	text = "Работа со строками\n1. Распечатать все первые слова предложений.\n2. Вернуться в главное меню";
}

void WorkWithStrings::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void WorkWithStrings::chooseVariant()
{
	cout << "Выберете нужный вариант:" << std::endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("Введите число от 1 до 2", PrintAllFirstWordsOfSentence,
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
		cout << "Что-то пошло не так....";
		chooseVariant();
		break;
	}
}
