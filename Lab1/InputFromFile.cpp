#include "InputFromFile.h"
#include <iostream>
#include "FileSystemFunctions.h"
#include "ShowAnswerElement.h"
#include "StringWorker.h"
using namespace std;

InputFromFile::InputFromFile()
{
	text = "¬вод начальных данных из файла.";
}

void InputFromFile::Show()
{
	InterfaceElement::Show();
	chooseVariant();
}

void InputFromFile::chooseVariant()
{
	auto text = FileSystemFunctions::getTextFromFileDialog();
	const auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
	auto answer = StringWorker::Join(firstWords, "\n");
	//delete &firstWords;
	ClearScreenAndPrintNew(std::make_shared<AnswerElement>(text, answer));
}
