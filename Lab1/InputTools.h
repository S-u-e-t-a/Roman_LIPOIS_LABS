#pragma once
#include <string>

class InputTools
{
public:
	static int TryGetIntUntillSucced(std::string inputMessage);
	static int TryGetIntUntillSuccedInRange(std::string inputMessage, int min, int max);
	//static void PrintError(std::string er);
};
