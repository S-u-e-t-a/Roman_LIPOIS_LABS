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
		//cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
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

void FileSystemFunctions::saveTextToFileDialog(const std::string text) //todo ���������� ��� �������
{
	string pathOutput;
	cout << "������� ���� � �����: ";
	//cin >> pathOutput;
	getline(cin, pathOutput);
	ifstream fout(pathOutput);
	while (!isPathGood(pathOutput) || isReadOnly(pathOutput))
	{
		// �������� �� ���������� ���� � ��� �����
		fout.close();
		cerr << "������������ �������� ���� ��� ����� �����." << endl;
		cout << "������� ���� � �����: ";
		//cin >> pathOutput;
		getline(cin, pathOutput);
		fout.open(pathOutput);
	}
	cout << endl;
	fout.close();
	while (fout)
	{
		// ���� ���� ��� ����������
		cout << endl;
		cout << "������ ���� ��� ����������." << endl;
		int choice = additionalMenu(); // ����� ���������������� ����
		switch (choice)
		{
		case Rewrite:
			{
				// ������� � �����������
				ofstream fout(pathOutput);
				saveTextToFileFile(text, pathOutput);
				fout.close();
				break;
			}
		case CreateNewFile:
			{
				// ������� � ��������� ������ �����
				fout.close();
				saveTextToFileDialog(text);
				break;
			}
		}
		break;
	}
	if (!fout)
	{
		// ���� ����� ��� �� ���������� �� ������� ����, �� ���������� �������� ����� � ��� ����������
		saveTextToFileFile(text, pathOutput);
		fout.close();
	}
	cout << endl;
}

int FileSystemFunctions::additionalMenu()
{
	cout << endl;
	cout << "\t�������� �������:" << endl;
	cout << "1. ������������ ����." << endl;
	cout << "2. ������� ����� ����." << endl;
	int variant = InputTools::TryGetIntUntillSuccedInRange("������� ����� �� 1 �� 2", Rewrite, CreateNewFile);
	return variant;
}

std::string FileSystemFunctions::getTextFromFileDialog()
{
	// ������� ��� ������ ������ �� �����
	string pathInput;
	cout << "������� ���� � �����: ";
	//cin >> pathInput;
	getline(cin, pathInput);
	ifstream fin(pathInput);
	int count = 0; // ������� ���������� ������ � ������ �����
	while (true)
	{
		while (!fin || !isPathGood(pathInput))
		{
			// �������� �� ������������� ����� �� ���������� ����
			fin.close();
			cerr << "������������ �������� ���� ��� ����� �����." << endl;
			cout << "������� ���� � �����: ";
			getline(cin, pathInput);
			fin.open(pathInput); // �������� �����
		}
		break;
	}
	fin.seekg(0, ios::beg);
	//string temp; // ���������� ��� ���������� �������� �������� �� �����
	//while (!fin.eof())
	//{
	//	while (getline(fin, temp))
	//		text.push_back(temp);
	//}
	//fin.close();
	return getTextFromFile(pathInput);
}
