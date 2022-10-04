#include "StringWorker.h"
#include <list>
#include <regex>

/// <summary>
/// Получает первые слова предложений из текста
/// </summary>
/// <param name="text">Текст с предложениями</param>
/// <returns>Первые слова предложений</returns>
std::vector<std::string> StringWorker::GetFirstWordsOfSentences(std::string text)
{
	const auto sentences = SplitString(text, ".?!");
	const auto firstWords = new std::vector<std::string>;
	for (auto s : sentences)
	{
		auto splittedSentence = SplitString(s, " ,:;-_+=)(@#$^&*");
		auto firstWord = splittedSentence[0];
		if (firstWord == "")
		{
			if (splittedSentence.size() <= 1)
			{
				continue;
			}
			firstWord = splittedSentence[1];
		}
		firstWords->push_back(firstWord);
	}
	return *firstWords;
}

/// <summary>
/// Разбивает строку по заданным разделителям
/// </summary>
/// <param name="stringToSplit">Строка для разбиения</param>
/// <param name="delemiters">Разделители</param>
/// <returns>Разделенная строка</returns>
std::vector<std::string> StringWorker::SplitString(std::string stringToSplit, std::string delemiters)
{
	//https://stackoverflow.com/a/58164098
	std::regex re('[' + delemiters + ']');
	std::sregex_token_iterator first{stringToSplit.begin(), stringToSplit.end(), re, -1}, last;
	std::vector<std::string> tokens{first, last};
	return tokens;
}

/// <summary>
/// Собирает строку с заданным разделителем
/// </summary>
/// <param name="strings">Строки для объединения</param>
/// <param name="delimiter">Разделитель</param>
/// <returns>Собранная строка</returns>
std::string StringWorker::Join(std::vector<std::string> strings, std::string delimiter)
{
	auto newString = std::string("");
	for (size_t i = 0; i < strings.size() - 1; i++)
	{
		newString += strings[i] + delimiter;
	}
	newString += strings[strings.size() - 1];
	return newString;
}
