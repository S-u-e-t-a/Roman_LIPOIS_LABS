#include "interface.h"

#include <iostream>

#include "FileSystemFunctions.h"
#include "InputTools.h"
#include "StringWorker.h"
/// <summary>
/// Выводит в консоль полученную строка
/// </summary>
/// <param name="text"> Строка для вывода</param>
void WriteLine(std::string text = "")
{
	std::cout << text << std::endl;
}
/// <summary>
/// Показывает главное меню программы
/// </summary>
/// <returns>Результат работы функции</returns>
int MainMenu()
{
	const std::string text = "\t>>ГЛАВНОЕ МЕНЮ<<\n"
		"1. Работа со строками\n"
		"2. О программе\n"
		"3. Выход";
	WriteLine(text);
	WriteLine("Выберете нужный вариант:");
	const int variant = InputTools::TryGetIntUntilSuccessInRange(GetFirstWordsOfSentences, Exit);
	switch (variant)
	{
	case GetFirstWordsOfSentences:
		GetFirstWordsOfSentencesMenu();
		return Ok;
	case Help:
		ShowHelp();
		return Ok;
	case Exit:
		return Exit;
	default:
		std::cout << "Что-то пошло не так....";
		break;
	}
	return Ok;
}
/// <summary>
/// Вариант меню с получением первых слов предложений
/// </summary>
/// <returns></returns>
int GetFirstWordsOfSentencesMenu()
{
	WriteLine("\t>>ПОЛУЧЕНИЕ ПЕРВЫХ СЛОВ ПРЕДЛОЖЕНИЙ<<");
	WriteLine("1. Ввести текст с клавиатуры");
	WriteLine("2. Ввести текст с файла");
	WriteLine();
	WriteLine("Выберете нужный вариант:");
	const int variant = InputTools::TryGetIntUntilSuccessInRange(FromKeyboard, FromFile);
	std::string text;
	switch (variant)
	{
	case FromKeyboard:
		text = InputFromKeyboard();
		break;
	case FromFile:
		text = InputFromFile();
		break;
	default:
		std::cout << "Что-то пошло не так....";
		return NotOk;
	}
	const auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
	const auto answer = StringWorker::Join(firstWords, "\n");
	const auto textPlusAnswer = "\tВХОДНЫЕ ДАННЫЕ\n" + text + "\n\n\t ПЕРВЫЕ СЛОВА ПРЕДЛОЖЕНИЙ\n" + answer;
	WriteLine(textPlusAnswer);
	AskToSaveDialog("\tСОХРАНИТЬ НАЧАЛЬНЫЕ ДАННЫЕ В ФАЙЛ?", text);
	AskToSaveDialog("\tСОХРАНИТЬ РЕЗУЛЬТАТ В ФАЙЛ?", answer);
	AskToSaveDialog("\tСОХРАНИТ РЕЗУЛЬТАТ И НАЧАЛЬНЫЕ ДАННЫЕ В ОДИН ФАЙЛ?", textPlusAnswer);
	return Ok;
}

/// <summary>
/// Показывает справку
/// </summary>
/// <returns>Результат работы функции</returns>
int ShowHelp()
{
	WriteLine("\t>>СПРАВКА<<");
	std::string text = "Эта программа выводит первые слова предложений в тексте.\n\n"
		"Автор: Хлебников Роман\n"
		"Группа: 494\n"
		"Лабораторная работа №1\n"
		"Вариант 18\n";

	text +=
		"	       ____   ___    _____  ____   ___    _____  ____  ______ ___        _____						\n"
		"              / __ \\ /   |  |__  / / __ \\ /   |  / ___/ / __ \\/_  __//   |     _/__  /						\n"
		"             / /_/ // /| |   /_ < / /_/ // /| | / __ \\ / / / / / /  / /| |   _/_/ / /                      \n"
		"            / ____// ___ | ___/ // ____// ___ |/ /_/ // /_/ / / /  / ___ | _/_/  / /                       \n"
		"           /_/    /_/  |_|/____//_/    /_/  |_|\\____/ \\____/ /_/  /_/  |_|/_/   /_/                        \n"
		"    ____   ____   __  ___ ___     __  __   _  __     _____ ______ _____  __  __ __  ____ __ __ ____   ____ \n"
		"   / __ \\ / __ \\ /  |/  //   |   / / / /  | |/ /   _/__  // ____// ___/ / / / // /_/   // //_// __ \\ / __ )\n"
		"  / /_/ // / / // /|_/ // /| |  / /_/ /   |   /  _/_/ / // __/  / __ \\ / /_/ // //_// // ,<  / / / // __  |\n"
		" / ____// /_/ // /  / // ___ | / __  /   /   | _/_/  / // /___ / /_/ // __  // /_/ / // /| |/ /_/ // /_/ / \n"
		"/_/     \\____//_/  /_//_/  |_|/_/ /_/   /_/|_|/_/   /_//_____/ \\____//_/ /_//__/  /_//_/ |_|\\____//_____/  \n";


	WriteLine(text);
	WriteLine();
	WriteLine();

	return Ok;
}

/// <summary>
/// Показывает меню с выводом начальных данных с клавиатуры
/// </summary>
/// <returns>Полученный текст</returns>
std::string InputFromKeyboard()
{
	WriteLine("\t>>ВВОД НАЧАЛЬНЫХ ДАННЫХ С КЛАВИАТУРЫ<<");
	std::string text = "";
	std::string buffer = "";
	std::cout << "Введите текст." << std::endl;
	std::cout << "По окончании ввода введите пустую строку." << std::endl;
	std::cout << std::endl;
	while (true)
	{
		getline(std::cin, buffer);
		if (buffer != "")
		{
			text += buffer;
		}
		else
		{
			if (text.size() == 0)
			{
				std::cout << "Вы не ввели текст." << std::endl;
				std::cout << "Введите текст: " << std::endl;
				std::cout << std::endl;
			}
			else
			{
				break;
			}
		}
	}
	return text;
}

/// <summary>
/// Показывает меню с выводом начальных данных из файла
/// </summary>
/// <returns>Полученный текст</returns>
std::string InputFromFile()
{
	WriteLine("\t>>ВВОД НАЧАЛЬНЫХ ДАННЫХ ИЗ ФАЙЛА<<");
	auto text = FileSystemFunctions::GetTextFromFileDialog();
	return text;
}

/// <summary>
/// Показывает меню с выбором сохранения файла
/// </summary>
/// <param name="message">Сообщение для вывода</param>
/// <param name="stringToSave">Текст, который нужно сохранить</param>
/// <returns>Результат выполнения функции</returns>
int AskToSaveDialog(std::string message, std::string stringToSave)
{
	WriteLine(message);
	WriteLine("1 - ДА || НЕТ");
	switch (InputTools::TryGetIntUntilSuccessInRange(Yes, No))
	{
	case Yes:
		FileSystemFunctions::SaveTextToFileDialog(stringToSave);
		return Ok;
	case No:
		return Ok;
	default:
		return NotOk;
	}
}
