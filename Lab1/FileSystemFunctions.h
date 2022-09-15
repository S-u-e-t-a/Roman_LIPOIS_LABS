#pragma once
#include <iomanip>
#include <filesystem>
#include <string>
#include <vector>
#include <string>

enum Saving { Rewrite = 1, CreateNewFile };

class FileSystemFunctions
{
public:
	static bool isPathGood(std::string path);
	static bool isReadOnly(std::string path);
	static void saveTextToFileFile(std::string text, std::string path);
	static std::string getTextFromFile(std::string path);
	static void saveTextToFileDialog(std::string text);
	static std::string getTextFromFileDialog();
private:
	static int additionalMenu();
	
};
