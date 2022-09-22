#include "Math.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include "Matrix.h"

Matrix MakeGilbertMatrix(int order)
{
	Matrix m (order, order);
	for (int i = 0; i < order; ++i)
	{
		for (int j = 0; j < order; ++j)
		{
			m(i, j) = { 1,i+1 + j+1 - 1 };
			//m(i, j)= 1 / (static_cast<double>(i+1) + j+1 - 1);
		}
	}
	//PrintMatrix(&m);
	return m;
}

void PrintMatrix(Matrix* m)
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

//double Det(Matrix* A)
//{
//	auto m = A->getRowCount();
//	auto n = A->getColCount();
//	if(m!=n)
//	{
//		throw std::invalid_argument("");
//	}
//	if(n==1)
//	{
//		return A->operator()(0, 0);
//	}
//	auto signum = 1.0;
//	auto determinant = 0.0;
//	for (int j = 0; j < n; ++j)
//	{
//		auto minor = A->get_minor(0, j);
//		determinant += A->operator()(0, j) * signum * Det(minor);
//		signum *= -1;
//		delete minor;
//	}
//	return determinant;
//}

//Matrix* inverse(Matrix* A)
//{
//	auto result = new Matrix(A->getRowCount(), A->getColCount());
//	auto detA = Det(A);
//	for (int i = 0; i < result->getRowCount(); ++i)
//	{
//		for (int j = 0; j < result->getColCount(); ++j)
//		{
//			auto tmp = A->get_minor(i, j);
//			if((i+j)%2 == 1)
//			{
//				result->operator()(i,j) = -1 * Det(tmp) / detA;
//			}
//			else
//			{
//				result->operator()(i, j) = 1 * Det(tmp) / detA;
//
//			}
//			delete tmp;
//		}
//	}
//	return result;
//}

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

std::string getBeautifulViewOfMatrix(Matrix* matrix, int precision)
{
	int cols = matrix->getColCount();
	int rows = matrix->getRowCount();
	auto maxLenOfNumInCol = std::vector<int>(cols);
	for (int i = 0; i < cols; ++i)
	{
		int max = 0;
		for (int j = 0; j < rows; ++j)
		{
			auto count = countOfSymsBeforeSeparator(matrix->operator()(j, i).toDouble());
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
			ss << std::fixed << std::setprecision(precision) << matrix->operator()(i,j).toDouble();
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