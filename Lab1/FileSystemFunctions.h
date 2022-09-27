#pragma once
#include <filesystem>
#include <string>
#include <string>

enum Saving { Rewrite = 1, CreateNewFile };

class FileSystemFunctions
{
public:
	static bool IsPathGood(std::string path);
	static bool IsReadOnly(std::string path);
	static void SaveTextToFileFile(std::string text, std::string path);
	static std::string GetTextFromFile(std::string path);
	static void SaveTextToFileDialog(std::string text);
	static std::string GetTextFromFileDialog();
private:
	static int AdditionalMenu();
};
