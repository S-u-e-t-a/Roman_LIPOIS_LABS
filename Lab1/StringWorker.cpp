#include "StringWorker.h"
#include <list>
#include <regex>

std::vector<std::string> StringWorker::GetFirstWordsOfSentences(std::string text)
{
	auto sentences = SplitString(text, ".?!");
	auto firstWords = new std::vector<std::string>;
	for (auto s : sentences)
	{
		auto splittedSentence = SplitString(s, " ,:;-_+=)(@#$^&*");
		auto firstWord = splittedSentence[0];
		if (firstWord=="")
		{
			if(splittedSentence.size()<=1)
			{
				continue;
			}
			firstWord = splittedSentence[1];
		}
		firstWords->push_back(firstWord);
	}
	return *firstWords;
}

std::vector<std::string> StringWorker::SplitString(std::string stringToSplit, std::string delemiters)
{
	//https://stackoverflow.com/a/58164098
	std::regex re('[' + delemiters + ']');
	std::sregex_token_iterator first{stringToSplit.begin(), stringToSplit.end(), re, -1}, last;
	std::vector<std::string> tokens{first, last};
	return tokens;
}

std::string StringWorker::Join(std::vector<std::string> strings, std::string delimiter)
{
	auto newString = std::string("");
	for (int i = 0; i < strings.size() - 1; i++)
	{
		newString += strings[i] + delimiter;
	}
	newString += strings[strings.size() - 1];
	return newString;
}
