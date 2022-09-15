#include "InputTools.h"
#include <iostream>

using namespace std;

int InputTools::TryGetIntUntillSucced(std::string inputMessage)
{
	cout << inputMessage << std::endl;
	string inputtedString;
	getline(cin, inputtedString);
	//cin >> inputtedString;
	try
	{
		int i = stoi(inputtedString);
		return i;
	}
	catch (const std::exception&)
	{
		return TryGetIntUntillSucced(inputMessage);
	}
}

int InputTools::TryGetIntUntillSuccedInRange(std::string inputMessage, int min, int max)
{
	int inputtedValue = TryGetIntUntillSucced(inputMessage);
	if (inputtedValue < min || inputtedValue > max)
	{
		return TryGetIntUntillSuccedInRange(inputMessage, min, max);
	}
	return inputtedValue;
}
