#include "InputTools.h"

#include <format>
#include <iostream>

using namespace std;

/// <summary>
/// Пытается получить от пользователя значение INT пока оно не будет верным
/// </summary>
/// <param name="inputMessage">Сообщение для вывода</param>
/// <returns>Полученное от пользователя число</returns>
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

/// <summary>
/// Пытается получить от пользователя значение INT пока оно не будет верным в заданном интервале
/// </summary>
/// <param name="min">Начало интервала</param>
/// <param name="max">Конец интервала</param>
/// <param name="inputMessage">Сообщение для вывода</param>
/// <returns>Полученное от пользователя число</returns>
int InputTools::TryGetIntUntilSuccessInRange(int min, int max, std::string inputMessage)
{
	if (inputMessage == "")
	{
		inputMessage = std::format("Введите число от {} до {}", min, max);
	}
	const int inputtedValue = TryGetIntUntilSuccess(inputMessage);
	if (inputtedValue < min || inputtedValue > max)
	{
		return TryGetIntUntilSuccessInRange(min, max, inputMessage);
	}
	return inputtedValue;
}
