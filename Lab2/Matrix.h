#pragma once

#include <stdexcept>
#include <vector>

#include "numInMatriix.h"

//https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates
//https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op
//Класс описывающий матрицу!!!!
template<typename MatrixType>
class Matrix {
public:
    Matrix<MatrixType>(unsigned rows, unsigned cols);
    Matrix<MatrixType>(const Matrix& m);               // Copy constructor
    Matrix<MatrixType>& operator= (const Matrix<MatrixType>& m);   // Assignment operator

    MatrixType& operator() (unsigned row, unsigned col);        // Subscript operators often come in pairs
    MatrixType  operator() (unsigned row, unsigned col) const;  // Subscript operators often come in pairs

    template<typename rightMatrixType>
    Matrix<MatrixType> operator * (const Matrix<rightMatrixType>* m);
    template<typename rightMatrixType>
    Matrix<MatrixType> operator - (const Matrix<rightMatrixType>* m);
    template<typename rightMatrixType>
    Matrix<MatrixType> operator + (const Matrix<rightMatrixType>* m);
    unsigned getRowCount() const;
    unsigned getColCount() const;
    static Matrix<int> GenerateIdentityMatrix(int size);
    //Matrix* Minor
    //Matrix* get_minor(int i, int j);
    Matrix<MatrixType>* getInverted();
    //~Matrix<MatrixType>();        // Destructor
private:
    unsigned rows_, cols_;
    std::vector<MatrixType> data_;
};

template <typename MatrixType>
Matrix<MatrixType>::Matrix<MatrixType>(unsigned rows, unsigned cols) : rows_(rows), cols_(cols)
//, data_ ← initialized below after the if...throw statement
{
	if (rows == 0 || cols == 0)
		throw std::invalid_argument("Matrix constructor has 0 size");
	data_ = std::vector<MatrixType>(rows_ * cols_);
}

template <typename MatrixType>
Matrix<MatrixType>::Matrix<MatrixType>(const Matrix<MatrixType>& matrix)
{
	rows_ = matrix.rows_;
	cols_ = matrix.cols_;
	data_ = std::vector<MatrixType>(rows_ * cols_);
	for (int i = 0; i < rows_ * cols_; ++i)
	{
		data_[i] = matrix.data_[i];
	}
	data_ = matrix.data_;
}

template <typename MatrixType>
Matrix<MatrixType>& Matrix<MatrixType>::operator=(const Matrix<MatrixType>& m)
{
	rows_ = m.getRowCount();
	cols_ = m.getColCount();
	data_ = std::vector<MatrixType>(rows_ * cols_);
	for (int i = 0; i < rows_; ++i)
	{
		for (int j = 0; j < cols_; ++j)
		{
			this->operator()(i, j) = m(i, j);
		}
	}
	return *this;
}

//template <typename MatrixType>
//Matrix<MatrixType>::~Matrix<MatrixType>()
//{
//	data_.clear();
//}

template <typename MatrixType>
template<typename rightMatrixType>
Matrix<MatrixType> Matrix<MatrixType>::operator*(const Matrix<rightMatrixType>* m)
{
	if (this->getColCount() != m->getRowCount())
	{
		throw std::invalid_argument(
			"Количество столбцов левой матрицы должно равняться количеству строк правой матрицы");
	}
	auto A = this;
	auto B = m;
	auto C = Matrix<MatrixType>(A->getRowCount(), B->getColCount());
	auto p = this->getColCount();
	for (int i = 0; i < C.getRowCount(); ++i)
	{
		for (int j = 0; j < C.getColCount(); ++j)
		{
			MatrixType cij=0;
			for (int k = 0; k < p; ++k)
			{
				cij = cij + A->operator()(i, k) * B->operator()(k, j);
				//cij += A->operator()(i, k) * B->operator()(k, j);
			}
			C(i, j) = cij;
		}
	}
	return C;
}


template <typename MatrixType>
template <typename rightMatrixType>
Matrix<MatrixType> Matrix<MatrixType>::operator-(const Matrix<rightMatrixType>* m)
{
	if (this->getColCount() != m->getColCount() || this->getRowCount() != m->getRowCount())
	{
		throw std::invalid_argument("Матрицы должны быть одинаковые по размеру!");
	}
	auto C = Matrix(this->getRowCount(), this->getColCount());
	for (int i = 0; i < this->getRowCount(); ++i)
	{
		for (int j = 0; j < this->getColCount(); ++j)
		{
			C(i, j) = this->operator()(i, j) - m->operator()(i, j);
		}
	}
	return C;
}

template <typename MatrixType>
template<typename rightMatrixType>
Matrix<MatrixType> Matrix<MatrixType>::operator+(const Matrix<rightMatrixType>* m)
{
	if (this->getColCount() != m->getColCount() || this->getRowCount() != m->getRowCount())
	{
		throw std::invalid_argument("Матрицы должны быть одинаковые по размеру!");
	}
	auto C = Matrix(this->getRowCount(), this->getColCount());
	for (int i = 0; i < this->getRowCount(); ++i)
	{
		for (int j = 0; j < this->getColCount(); ++j)
		{
			C(i, j) = this->operator()(i, j) + m->operator()(i, j);
		}
	}
	return C;
}

template <typename MatrixType>
unsigned Matrix<MatrixType>::getRowCount() const
{
	return rows_;
}

template <typename MatrixType>
unsigned Matrix<MatrixType>::getColCount() const
{
	return cols_;
}

template <typename MatrixType>
Matrix<int> Matrix<MatrixType>::GenerateIdentityMatrix(int size)
{
	Matrix<int> matrix(size, size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			matrix(i, j) = 0;
		}
	}
	for (int i = 0; i < size; ++i)
	{
		matrix(i, i) = 1;
	}
	return matrix;
}

//template <typename MatrixType>
//Matrix<MatrixType>* Matrix<MatrixType>::get_minor(int ii, int jj)
//{
//	auto minor = new Matrix(this->getRowCount() - 1, this->getColCount() - 1);
//	auto c = 0;
//	auto i = 0;
//	while (i < this->getRowCount())
//	{
//		if (i == ii)
//		{
//			i += 1;
//			continue;
//		}
//		auto j = 0;
//		while (j < this->getColCount())
//		{
//			if (j == jj)
//			{
//				j += 1;
//				continue;
//			}
//			int row, col;
//			if (c == 0)
//			{
//				row = 0;
//				col = 0;
//			}
//			else
//			{
//				row = c / (minor->getRowCount());
//				col = c % (minor->getColCount());
//			}
//			minor->operator()(row, col) = this->operator()(i, j);
//			c++;
//			j++;
//		}
//		i++;
//	}
//	return minor;
//}

template <typename MatrixType>
Matrix<MatrixType>* Matrix<MatrixType>::getInverted()
{
	int order = getColCount();

	// копируем начальную матрицу
	auto augmentedMatrix = Matrix(order, order * 2);
	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			augmentedMatrix(i, j) = operator()(i, j);
		}
	}
	// заполняем правую часть расширенной матрицы единичной матрицей
	for (int i = 0; i < order; i++) {
		for (int j = order; j < 2 * order; j++) {
			if (j == (i + order))
			{
				augmentedMatrix(i, j) = 1;
			}
			else
			{
				augmentedMatrix(i, j) = 0;
			}
		}
	}
	for (int nrow = 0; nrow < order; ++nrow)
	{
		auto divider = augmentedMatrix(nrow, nrow);
		for (int i = 0; i < order * 2; ++i)
		{
			augmentedMatrix(nrow, i) = augmentedMatrix(nrow, i) / divider;
		}

		for (int lowerRow = nrow + 1; lowerRow < order; ++lowerRow)
		{
			auto factor = augmentedMatrix(lowerRow, nrow);
			for (int i = 0; i < order * 2; ++i)
			{
				augmentedMatrix(lowerRow, i) = augmentedMatrix(lowerRow, i) - factor * augmentedMatrix(nrow, i);
			}
		}
	}
	for (int col = order - 1; col >= 1; --col)
	{
		for (int row = col - 1; row >= 0; --row)
		{
			auto factor = augmentedMatrix(row, col);
			for (int i = 0; i < order * 2; ++i)
			{
				augmentedMatrix(row, i) = augmentedMatrix(row, i) - augmentedMatrix(col, i) * factor;
			}
		}
	}
	auto result = new Matrix(order, order);
	for (int i = 0; i < order; ++i)
	{
		for (int j = 0; j < order; ++j)
		{
			result->operator()(i, j) = augmentedMatrix(i, order + j);
		}
	}
	return result;
}

template <typename MatrixType>
MatrixType& Matrix<MatrixType>::operator()(unsigned row, unsigned col)
{
	if (row >= rows_ || col >= cols_)
		throw std::invalid_argument("Matrix subscript out of bounds");
	return data_[cols_ * row + col];
}

template <typename MatrixType>
MatrixType Matrix<MatrixType>::operator()(unsigned row, unsigned col) const
{
	if (row >= rows_ || col >= cols_)
		throw std::invalid_argument("const Matrix subscript out of bounds");
	return data_[cols_ * row + col];
}

