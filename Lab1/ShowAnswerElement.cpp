#include "ShowAnswerElement.h"

#include "WorkWithStrings.h"
#include <iostream>

#include "FileSystemFunctions.h"
#include "MainMenu.h"
using namespace std;


AnswerElement::AnswerElement(string initialIn, string answerIn)
{
	text = "������� ������:\n" + initialIn + "\n\n���������:\n" + answerIn;
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
		"\t�������� ������ �������:\n"
	"1. ��������� ������ �������� ������\n"
	"2. ��������� ������ ���������\n"
	"3. ��������� �������� ������ � ��������� � ���� ����\n"
	"4. ��������� �������� ������ � ��������� � ������ �����\n"
	"5. ������ �� ���������."
		<< std::endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("������� ����� �� 1 �� 5",
	                                                       SaveOnlyInitial, SaveNothing);
	switch (variant)
	{
	case SaveOnlyInitial:
		cout << "\t���������� ��������� ������";
		FileSystemFunctions::saveTextToFileDialog(initial);
		break;
	case SaveOnlyResult:
		cout << "\t���������� ����������";
		FileSystemFunctions::saveTextToFileDialog(answer);
		break;
	case SaveInitialAndResultToOneFile:
		cout << "\t���������� ��������� ������ � ���������� � ���� ����";
		FileSystemFunctions::saveTextToFileDialog(text);
		break;
	case SaveInitialAndResultSeparately:
		cout << "\t���������� ��������� ������";
		FileSystemFunctions::saveTextToFileDialog(initial);
		cout << "\t���������� ����������";
		FileSystemFunctions::saveTextToFileDialog(answer);
		break;
	case SaveNothing:
		break;
	default:
		cout << "���-�� ����� �� ���....";
		chooseVariant();
		break;
	}
	ClearScreenAndPrintNew(std::make_shared<MainMenu>());
}
