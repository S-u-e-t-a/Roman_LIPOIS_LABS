#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Matrix.h"
template<typename MatrixType>
Matrix<MatrixType> MakeGilbertMatrix(int order);
template<typename MatrixType>
void PrintMatrix(Matrix<MatrixType>* m);
//double Det(Matrix* A);
int countOfSymsBeforeSeparator(double num);
template<typename MatrixType>
std::string getBeautifulViewOfMatrix(Matrix<MatrixType>* matrix, int precision);
template<typename MatrixType>
Matrix<MatrixType> makeLeftResidualMatrix(Matrix<MatrixType>* initial, Matrix<MatrixType>* inverted);
template<typename MatrixType>
Matrix<MatrixType> makeRightResidualMatrix(Matrix<MatrixType>* initial, Matrix<MatrixType>* inverted);
template<typename MatrixType>
double getRowNorm(Matrix<MatrixType>* residualMatrix);
#include "Math.h"


template<typename MatrixType>
Matrix<MatrixType> MakeGilbertMatrix(int order)
{
	Matrix<MatrixType> m(order, order);
	for (int i = 0; i < order; ++i)
	{
		for (int j = 0; j < order; ++j)
		{
			m(i, j)= 1 / (static_cast<MatrixType>(i+1) + j+1 - 1);
		}
	}
	//PrintMatrix(&m);
	return m;
}

//template<> Matrix<float> MakeGilbertMatrix(int order)
//{
//	Matrix<float> m(order, order);
//	for (int i = 0; i < order; ++i)
//	{
//		for (int j = 0; j < order; ++j)
//		{
//			m(i, j) = 1 / (static_cast<float>(i + 1) + j + 1 - 1);
//		}
//	}
//	//PrintMatrix(&m);
//	return m;
//}

template <typename MatrixType>
void PrintMatrix(Matrix<MatrixType>* m)
{
	/*for (int i = 0; i < m->getRowCount(); ++i)
	{
		for (int j = 0; j < m->getColCount(); ++j)
		{
			std::cout << m->operator()(i, j) << " ";
		}
		std::cout << std::endl;
	}*/
	std::cout <<getBeautifulViewOfMatrix(m,2) << std::endl;
}

int countOfSymsBeforeSeparator(double num)
{
	int count = 0;
	if (num<0)
	{
		count += 1;
		num *= -1;
	}
	do
	{
		num /= 10;
		count += 1;
	}
	while (num>1);

	return count;
}


template <typename MatrixType>
std::string getBeautifulViewOfMatrix(Matrix<MatrixType>* matrix, int precision)
{
	int cols = matrix->getColCount();
	int rows = matrix->getRowCount();
	auto maxLenOfNumInCol = std::vector<int>(cols);
	for (int i = 0; i < cols; ++i)
	{
		int max = 0;
		for (int j = 0; j < rows; ++j)
		{
			auto count = countOfSymsBeforeSeparator(static_cast<double>(matrix->operator()(j, i)));
			if(count>max)
			{
				max = count;
			}
		}
		maxLenOfNumInCol[i] = max;
	}
	auto strMatrix = std::vector<std::vector<std::string>>(rows);
	for (int i = 0; i < rows; ++i)
	{
		strMatrix[i] = std::vector<std::string>(cols);
		for (int j = 0; j < cols; ++j)
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(precision) <<static_cast<double>(matrix->operator()(i,j));
			std::string strNum = ss.str();
			while (strNum.size() < precision+maxLenOfNumInCol[j] + 1)
			{
				strNum = " " + strNum;
			}
			strMatrix[i][j] = strNum;
		}
	}
	std::stringstream ss;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			ss << strMatrix[i][j]<<" ";
		}
		ss << "\n";
	}
	return ss.str();
}

void printTable(std::vector<std::vector<std::string>> normalizedTable)
{
	int rows = normalizedTable.size();
	int cols = normalizedTable[0].size();
	std::stringstream ss;
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			ss << normalizedTable[i][j] << " ";
		}
		ss << "\n";
	}
	std::cout << ss.str() << std::endl;
}

std::vector<std::vector<std::string>> normalizeTable(std::vector<std::vector<std::string>> notNormalizedTable)
{
	//предполагается что таблица имеет заголовки столбцов и строк
	int rows = notNormalizedTable.size();
	int cols = notNormalizedTable[0].size();

	auto maxLenOfNumInCol = std::vector<int>(cols);
	for (int i = 0; i < cols; ++i)
	{
		int max = 0;
		for (int j = 0; j < rows; ++j)
		{
			auto len = notNormalizedTable[j][i].size();
			if (len > max)
			{
				max = len;
			}
		}
		maxLenOfNumInCol[i] = max;
	}
	auto strMatrix = std::vector<std::vector<std::string>>(rows);
	//for (int i = 0; i < rows; ++i)//копируем начальную таблицу
	//{
	//	for (int j = 0; j < cols; ++j)
	//	{
	//		strMatrix[i][j] = notNormalizedTable[i][j];
	//	}
	//}
	for (int i = 0; i < rows; ++i)
	{
		strMatrix[i] = std::vector<std::string>(cols);
	}
	strMatrix[0][0] = std::string(maxLenOfNumInCol[0], ' ');
	for (int i = 1; i < cols; ++i) //центрируем заголовки столбцов
	{
		bool isLeft = true;
		auto header = notNormalizedTable[0][i];
		while (header.size()<maxLenOfNumInCol[i])
		{
			if(isLeft)
			{
				header = " " + header;
			}
			else
			{
				header += " ";
			}
			isLeft = !isLeft;
			
		}
		strMatrix[0][i] = header;
	}
	for (int i = 1; i < rows; ++i) //добавляем слева пробелы для каждого элемента
	{
		strMatrix[i] = std::vector<std::string>(cols);
		for (int j = 0; j < cols; ++j)
		{
			//std::stringstream ss;
			//ss << std::fixed << std::setprecision(precision) << static_cast<double>(matrix->operator()(i, j));
			std::string strNum = notNormalizedTable[i][j];
			while (strNum.size() < maxLenOfNumInCol[j])
			{
				strNum = " " + strNum;
			}
			strMatrix[i][j] = strNum;
		}
	}

	return strMatrix;
}

std::vector<std::vector<std::string>> makeTable(std::vector<std::string> rowHeaders,
                                                std::vector<std::vector<std::string>> values)
{
	if (rowHeaders.size()!=values.size())
	{
		throw std::invalid_argument("Количество заголовков не равно количеству строк значений");
	}
	auto rowCount = rowHeaders.size() +1;
	auto colCount = values[0].size() + 1;
	auto ans = std::vector<std::vector<std::string>>(rowCount);
	for (int i = 0; i < rowCount; ++i)
	{
		ans[i] = std::vector<std::string>(colCount);
	}
	for (int i = 1; i < colCount; ++i)
	{
		ans[0][i] = std::to_string(i);
	}
	for (int i = 1; i < rowCount; ++i)
	{
		ans[i][0] = rowHeaders[i - 1];
	}
	for (int i = 1; i < rowCount; ++i)
	{
		for (int j = 1; j < colCount; ++j)
		{
			ans[i][j] = values[i - 1][j - 1];
		}
	}
	return ans;
}


template<typename MatrixType>
Matrix<MatrixType> makeLeftResidualMatrix(Matrix<MatrixType>* initial, Matrix<MatrixType>* inverted)
{
	Matrix<int> identity = Matrix<MatrixType>::GenerateIdentityMatrix(initial->getColCount());
	Matrix<MatrixType> res = ((*inverted) * initial) - &identity;
	return res;
}

template<typename MatrixType>
Matrix<MatrixType> makeRightResidualMatrix(Matrix<MatrixType>* initial, Matrix<MatrixType>* inverted)
{
	Matrix<int> identity = Matrix<MatrixType>::GenerateIdentityMatrix(initial->getColCount());
	Matrix<MatrixType> res = ((*initial) * inverted) - &identity;
	return res;
}

template<typename MatrixType>
double getRowNorm(Matrix<MatrixType>* residualMatrix)
{
	auto order = residualMatrix->getRowCount();
	std::vector<MatrixType> sumOfRow = std::vector<MatrixType>(order);
	for (int i = 0; i < order; ++i)
	{
		sumOfRow[i] = 0;
		for (int j = 0; j < order; ++j)
		{
			auto elem = residualMatrix->operator()(i, j);
			if (elem<0)
			{
				elem = elem * -1;
			}
			sumOfRow[i] = sumOfRow[i] + elem;
		}
	}
	auto max = sumOfRow[0];
	for (int i = 0; i < order; ++i)
	{
		if (sumOfRow[i]>max)
		{
			max = sumOfRow[i];
		}
	}
	return static_cast<double>(max);
}