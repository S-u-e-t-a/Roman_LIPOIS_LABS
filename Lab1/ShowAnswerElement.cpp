#include "ShowAnswerElement.h"

#include "WorkWithStrings.h"
#include <iostream>

#include "FileSystemFunctions.h"
#include "MainMenu.h"
using namespace std;


AnswerElement::AnswerElement(string initialIn, string answerIn)
{
	text = "Входные данные:\n" + initialIn + "\n\nРезультат:\n" + answerIn;
	initial = initialIn;
	answer = answerIn;
}

void AnswerElement::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void AnswerElement::chooseVariant()
{
	cout <<
		"\tВыберете нужный вариант:\n"
	"1. Сохранить только исходные данные\n"
	"2. Сохранить только результат\n"
	"3. Сохранить исходные данные и результат в один файл\n"
	"4. Сохранить исходные данные и результат в разные файлы\n"
	"5. Ничего не сохранять."
		<< std::endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("Введите число от 1 до 5",
	                                                       SaveOnlyInitial, SaveNothing);
	switch (variant)
	{
	case SaveOnlyInitial:
		cout << "\tСохранение начальных данных";
		FileSystemFunctions::saveTextToFileDialog(initial);
		break;
	case SaveOnlyResult:
		cout << "\tСохранение результата";
		FileSystemFunctions::saveTextToFileDialog(answer);
		break;
	case SaveInitialAndResultToOneFile:
		cout << "\tСохранение начальных данных и результата в один файл";
		FileSystemFunctions::saveTextToFileDialog(text);
		break;
	case SaveInitialAndResultSeparately:
		cout << "\tСохранение начальных данных";
		FileSystemFunctions::saveTextToFileDialog(initial);
		cout << "\tСохранение результата";
		FileSystemFunctions::saveTextToFileDialog(answer);
		break;
	case SaveNothing:
		break;
	default:
		cout << "Что-то пошло не так....";
		chooseVariant();
		break;
	}
	ClearScreenAndPrintNew(std::make_shared<MainMenu>());
}
