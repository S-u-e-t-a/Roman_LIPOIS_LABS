#include "FileSystemFunctions.h"
#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <string>
#include <fstream>
#include "InputTools.h"
using namespace std;

bool FileSystemFunctions::IsPathGood(const std::string path)
{
	const size_t found = path.find_last_of('\\');
	const size_t point = path.find_last_of('.');
	const size_t base = point - found - 1;
	const string baseFilenameStr = path.substr(found + 1, base);
	const char* baseFilenameChar = baseFilenameStr.c_str();
	ofstream file(path, ios::app);
	if (!_strcmpi(baseFilenameChar, "con"))
	{
		return false;
	}
	if (!filesystem::is_regular_file(path))
	{
		return false;
	}
	file.close();
	return true;
}

bool FileSystemFunctions::IsReadOnly(const std::string path)
{
	ifstream file(path);
	WIN32_FIND_DATAA findData;
	const LPCSTR name = path.c_str();
	FindFirstFileA(name, &findData);
	if (findData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
	{
		//cerr << "Невозможно сохранить данные в файл, предназначенный только для чтения." << endl;
		return true;
	}
	return false;
}

void FileSystemFunctions::SaveTextToFileFile(const std::string text, const std::string path)
{
	ofstream fout(path);
	fout << text << endl;
	fout.close();
}

std::string FileSystemFunctions::GetTextFromFile(const std::string path)
{
	ifstream inputFile(path);
	return std::string((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
}

void FileSystemFunctions::SaveTextToFileDialog(const std::string text) //todo переписать при желании
{
	string pathOutput;
	cout << "Введите путь к файлу: ";
	//cin >> pathOutput;
	getline(cin, pathOutput);
	ifstream fout(pathOutput);
	while (!IsPathGood(pathOutput) || IsReadOnly(pathOutput))
	{
		// Проверка на корректный путь и имя файла
		fout.close();
		cerr << "Некорректное указание пути или имени файла." << endl;
		cout << "Введите путь к файлу: ";
		//cin >> pathOutput;
		getline(cin, pathOutput);
		fout.open(pathOutput);
	}
	cout << endl;
	fout.close();
	while (fout)
	{
		// Если файл уже существует
		cout << endl;
		cout << "Данный файл уже существует." << endl;
		int choice = AdditionalMenu(); // Вывод вспомогательного меню
		switch (choice)
		{
		case Rewrite:
			{
				// Вариант с перезаписью
				ofstream fout(pathOutput);
				SaveTextToFileFile(text, pathOutput);
				fout.close();
				break;
			}
		case CreateNewFile:
			{
				// Вариант с созданием нового файла
				fout.close();
				SaveTextToFileDialog(text);
				break;
			}
		}
		break;
	}
	if (!fout)
	{
		// Если файла ещё не существует по данному пути, то происходит создание файла и его сохранение
		SaveTextToFileFile(text, pathOutput);
		fout.close();
	}
	cout << endl;
}

int FileSystemFunctions::AdditionalMenu()
{
	cout << endl;
	cout << "\tВыберите вариант:" << endl;
	cout << "1. Перезаписать файл." << endl;
	cout << "2. Создать новый файл." << endl;
	const int variant = InputTools::TryGetIntUntilSuccessInRange(Rewrite, CreateNewFile); //"Введите число от 1 до 2",
	return variant;
}

std::string FileSystemFunctions::GetTextFromFileDialog()
{
	// Функция для чтения данных из файла
	string pathInput;
	cout << "Введите путь к файлу: ";
	//cin >> pathInput;
	getline(cin, pathInput);
	ifstream fin(pathInput);
	while (true)
	{
		while (!fin || !IsPathGood(pathInput))
		{
			// Проверка на существование файла по указанному пути
			fin.close();
			cerr << "Некорректное указание пути или имени файла." << endl;
			cout << "Введите путь к файлу: ";
			getline(cin, pathInput);
			fin.open(pathInput); // Открытие файла
		}
		break;
	}
	fin.seekg(0, ios::beg);
	//string temp; // Переменная для временного хранения символов из файла
	//while (!fin.eof())
	//{
	//	while (getline(fin, temp))
	//		text.push_back(temp);
	//}
	//fin.close();
	return GetTextFromFile(pathInput);
}
