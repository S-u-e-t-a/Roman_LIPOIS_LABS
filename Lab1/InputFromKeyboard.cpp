#include "InputFromKeyboard.h"

#include <iostream>

#include "ShowAnswerElement.h"
#include "StringWorker.h"

using namespace std;
InputFromKeyboard::InputFromKeyboard()
{
	text = "Ввод начальных данных с клавиатуры";
}


void InputFromKeyboard::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void InputFromKeyboard::chooseVariant()
{
	string text = "";
	string buffer = "";
	cout << "Введите текст." << endl;
	cout << "По окончании ввода введите пустую строку." << endl;
	cout << endl;
	while (true)
	{
		getline(cin, buffer);
		if (buffer != "")
		{
			text+=buffer;
		}
		else
		{
			if (text.size() == 0)
			{
				cout << "Вы не ввели текст." << endl;
				cout << "Введите текст: " << endl;
				cout << endl;
			}
			else
			{
				break;
			}
		}
	}
	const auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
	auto answer = StringWorker::Join(firstWords, "\n");
	
	//delete &firstWords;
	ClearScreenAndPrintNew(std::make_shared<AnswerElement>(text, answer));
}
