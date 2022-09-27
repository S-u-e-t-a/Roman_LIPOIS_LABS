#include "InputTools.h"

#include <format>
#include <iostream>

using namespace std;

int InputTools::TryGetIntUntilSuccess(std::string inputMessage)
{
	cout << inputMessage << std::endl;
	string inputtedString;
	getline(cin, inputtedString);
	//cin >> inputtedString;
	try
	{
		const int i = stoi(inputtedString);
		return i;
	}
	catch (const std::exception&)
	{
		return TryGetIntUntilSuccess(inputMessage);
	}
}

int InputTools::TryGetIntUntilSuccessInRange(int min, int max, std::string inputMessage)
{
	if (inputMessage == "")
	{
		inputMessage = std::format("¬ведите число от {} до {}", min, max);
	}
	const int inputtedValue = TryGetIntUntilSuccess(inputMessage);
	if (inputtedValue < min || inputtedValue > max)
	{
		return TryGetIntUntilSuccessInRange(min, max, inputMessage);
	}
	return inputtedValue;
}
