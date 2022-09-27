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
		//cerr << "���������� ��������� ������ � ����, ��������������� ������ ��� ������." << endl;
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

void FileSystemFunctions::SaveTextToFileDialog(const std::string text) //todo ���������� ��� �������
{
	string pathOutput;
	cout << "������� ���� � �����: ";
	//cin >> pathOutput;
	getline(cin, pathOutput);
	ifstream fout(pathOutput);
	while (!IsPathGood(pathOutput) || IsReadOnly(pathOutput))
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
		int choice = AdditionalMenu(); // ����� ���������������� ����
		switch (choice)
		{
		case Rewrite:
			{
				// ������� � �����������
				ofstream fout(pathOutput);
				SaveTextToFileFile(text, pathOutput);
				fout.close();
				break;
			}
		case CreateNewFile:
			{
				// ������� � ��������� ������ �����
				fout.close();
				SaveTextToFileDialog(text);
				break;
			}
		}
		break;
	}
	if (!fout)
	{
		// ���� ����� ��� �� ���������� �� ������� ����, �� ���������� �������� ����� � ��� ����������
		SaveTextToFileFile(text, pathOutput);
		fout.close();
	}
	cout << endl;
}

int FileSystemFunctions::AdditionalMenu()
{
	cout << endl;
	cout << "\t�������� �������:" << endl;
	cout << "1. ������������ ����." << endl;
	cout << "2. ������� ����� ����." << endl;
	const int variant = InputTools::TryGetIntUntilSuccessInRange(Rewrite, CreateNewFile); //"������� ����� �� 1 �� 2",
	return variant;
}

std::string FileSystemFunctions::GetTextFromFileDialog()
{
	// ������� ��� ������ ������ �� �����
	string pathInput;
	cout << "������� ���� � �����: ";
	//cin >> pathInput;
	getline(cin, pathInput);
	ifstream fin(pathInput);
	while (true)
	{
		while (!fin || !IsPathGood(pathInput))
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
	return GetTextFromFile(pathInput);
}
