#pragma once
#include <vector>
#include <string>

class StringWorker
{
public:
	static std::vector<std::string> GetFirstWordsOfSentences(std::string sentences);
	static std::vector<std::string> SplitString(std::string stringToSplit, std::string separators);
	static std::string Join(std::vector<std::string> strings, std::string delimiter);
};
