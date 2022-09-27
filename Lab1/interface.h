#pragma once
#include <string>

enum FuncResult
{
	Ok,
	NotOk,
};

enum MainMenuVariant
{
	GetFirstWordsOfSentences=1,
	Help,
	Exit
};

enum InputTypeVariants
{
	FromKeyboard = 1,
	FromFile
};

enum YesNo
{
	Yes = 1,
	No
};


int MainMenu();

int GetFirstWordsOfSentencesMenu();

int ShowHelp();


std::string InputFromKeyboard();

std::string InputFromFile();

int AskToSaveDialog(std::string message, std::string stringToSave);
