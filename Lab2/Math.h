#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include "Matrix.h"
template<typename MatrixType>
Matrix<MatrixType> MakeGilbertMatrix(int order);
template<typename MatrixType>
void PrintMatrix(Matrix<MatrixType>* m);
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
	return m;
}

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