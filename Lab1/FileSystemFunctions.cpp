#include "FileSystemFunctions.h"
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <string>
#include <vector>
#include <string>
#include <fstream>
#include "InputTools.h"
using namespace std;

bool FileSystemFunctions::isPathGood(const std::string path)
{
	const size_t found = path.find_last_of("\\");
	const size_t point = path.find_last_of(".");
	const size_t base = point - found - 1;
	const string basefilenameStr = path.substr(found + 1, base);
	const char* basefilenameChar = basefilenameStr.c_str();
	ofstream file(path, ios::app);
	if (!_strcmpi(basefilenameChar, "con"))
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

bool FileSystemFunctions::isReadOnly(const std::string path)
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

void FileSystemFunctions::saveTextToFileFile(const std::string text, const std::string path)
{
	ofstream fout(path);
	fout << text << endl;
	fout.close();
}

std::string FileSystemFunctions::getTextFromFile(const std::string path)
{
	ifstream input_file(path);
	return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

void FileSystemFunctions::saveTextToFileDialog(const std::string text) //todo переписать при желании
{
	string pathOutput;
	cout << "Введите путь к файлу: ";
	//cin >> pathOutput;
	getline(cin, pathOutput);
	ifstream fout(pathOutput);
	while (!isPathGood(pathOutput) || isReadOnly(pathOutput))
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
		int choice = additionalMenu(); // Вывод вспомогательного меню
		switch (choice)
		{
		case Rewrite:
			{
				// Вариант с перезаписью
				ofstream fout(pathOutput);
				saveTextToFileFile(text, pathOutput);
				fout.close();
				break;
			}
		case CreateNewFile:
			{
				// Вариант с созданием нового файла
				fout.close();
				saveTextToFileDialog(text);
				break;
			}
		}
		break;
	}
	if (!fout)
	{
		// Если файла ещё не существует по данному пути, то происходит создание файла и его сохранение
		saveTextToFileFile(text, pathOutput);
		fout.close();
	}
	cout << endl;
}

int FileSystemFunctions::additionalMenu()
{
	cout << endl;
	cout << "\tВыберите вариант:" << endl;
	cout << "1. Перезаписать файл." << endl;
	cout << "2. Создать новый файл." << endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("Введите число от 1 до 2", Rewrite, CreateNewFile);
	return variant;
}

std::string FileSystemFunctions::getTextFromFileDialog()
{
	// Функция для чтения данных из файла
	string pathInput;
	cout << "Введите путь к файлу: ";
	//cin >> pathInput;
	getline(cin, pathInput);
	ifstream fin(pathInput);
	int count = 0; // Счетчик количества данных в данном файле
	while (true)
	{
		while (!fin || !isPathGood(pathInput))
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
	return getTextFromFile(pathInput);
}
