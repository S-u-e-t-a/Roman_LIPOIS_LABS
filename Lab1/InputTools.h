#pragma once
#include <string>

class InputTools
{
public:
	static int TryGetIntUntilSuccess(std::string inputMessage);
	static int TryGetIntUntilSuccessInRange(int min, int max, std::string inputMessage = "");
	//static void PrintError(std::string er);
};
