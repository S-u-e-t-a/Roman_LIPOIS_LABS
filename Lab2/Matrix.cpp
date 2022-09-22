#include "Matrix.h"

Matrix::Matrix(unsigned rows, unsigned cols): rows_(rows), cols_(cols)
//, data_ ← initialized below after the if...throw statement
{
	if (rows == 0 || cols == 0)
		throw std::invalid_argument("Matrix constructor has 0 size");
	data_ = std::vector<numInMatrix>(rows_ * cols_);
}

Matrix::Matrix(const Matrix& matrix)
{
	rows_ = matrix.rows_;
	cols_ = matrix.cols_;
	data_ = std::vector<numInMatrix>(rows_ * cols_);
	for (int i = 0; i < rows_ * cols_; ++i)
	{
		data_[i] = matrix.data_[i];
	}
	data_ = matrix.data_;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	rows_ = m.getRowCount();
	cols_ = m.getColCount();
	data_ = std::vector<numInMatrix>(rows_ * cols_);
	for (int i = 0; i < rows_; ++i)
	{
		for (int j = 0; j < cols_; ++j)
		{
			this->operator()(i, j) = m(i, j);
		}
	}
	return *this;
}

Matrix::~Matrix()
{
	data_.clear();
}


//Matrix& Matrix::operator=(const Matrix& m)
//{
//
//}

Matrix Matrix::operator*(const Matrix* m)
{
	if (this->getColCount() != m->getRowCount())
	{
		throw std::invalid_argument(
			"Количество столбцов левой матрицы должно равняться количеству строк правой матрицы");
	}
	auto A = this;
	auto B = m;
	auto C = Matrix(A->getRowCount(), B->getColCount());
	auto p = this->getColCount();
	for (int i = 0; i < C.getRowCount(); ++i)
	{
		for (int j = 0; j < C.getColCount(); ++j)
		{
			auto cij = numInMatrix(0, 1);
			for (int k = 0; k < p; ++k)
			{
				//todo delete
				//auto a = A[1,2];
				auto a = A->operator()(i, k);
				auto b = B->operator()(k, j);

				cij = cij + A->operator()(i, k) * B->operator()(k, j);
				//cij += A->operator()(i, k) * B->operator()(k, j);
			}
			C(i, j) = cij;
		}
	}

	return C;
}

Matrix Matrix::operator-(const Matrix* m)
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

Matrix Matrix::operator+(const Matrix* m)
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

unsigned Matrix::getRowCount() const
{
	return rows_;
}

unsigned Matrix::getColCount() const
{
	return cols_;
}

Matrix Matrix::GenerateIdentityMatrix(int size)
{
	Matrix matrix(size, size);
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

Matrix* Matrix::get_minor(int ii, int jj)
{
	auto minor = new Matrix(this->getRowCount() - 1, this->getColCount() - 1);
	auto c = 0;
	auto i = 0;
	while (i < this->getRowCount())
	{
		if (i == ii)
		{
			i += 1;
			continue;
		}
		auto j = 0;
		while (j < this->getColCount())
		{
			if (j == jj)
			{
				j += 1;
				continue;
			}
			int row, col;
			if (c == 0)
			{
				row = 0;
				col = 0;
			}
			else
			{
				row = c / (minor->getRowCount());
				col = c % (minor->getColCount());
			}
			minor->operator()(row, col) = this->operator()(i, j);
			c++;
			j++;
		}
		i++;
	}
	return minor;
}

numInMatrix::numInMatrix()
{
	numerator = 0;
	denominator = 1;
}

numInMatrix::numInMatrix(int value)
{
	numerator = value;
	denominator = 1;
}

//numInMatrix::numInMatrix(double value)
//{
//	throw std::invalid_argument("");
//}

//numInMatrix::numInMatrix(const numInMatrix& nim)
//{
//}

numInMatrix::numInMatrix(int numer, int denom)
{
	if (denom==0)
	{
		throw std::invalid_argument("Делитель не должен быть равен нулю!");
	}
	auto nod = NOD(numer, denom);
	numerator = numer/nod;
	denominator = denom/nod;
}

numInMatrix& Matrix::operator()(unsigned row, unsigned col)
{
	if (row >= rows_ || col >= cols_)
		throw std::invalid_argument("Matrix subscript out of bounds");
	return data_[cols_ * row + col];
}

numInMatrix Matrix::operator()(unsigned row, unsigned col) const
{
	if (row >= rows_ || col >= cols_)
		throw std::invalid_argument("const Matrix subscript out of bounds");
	return data_[cols_ * row + col];
}


numInMatrix& numInMatrix::operator=(const int value)
{
	numerator = value;
	denominator = 1;
	return *this;
}

numInMatrix numInMatrix::operator+(int value)
{
	return {numerator + denominator * value, denominator};
}

numInMatrix numInMatrix::operator-(int value)
{
	return {numerator - denominator * value, denominator};
}

numInMatrix numInMatrix::operator*(int value)
{
	return {numerator * value, denominator};
}

numInMatrix numInMatrix::operator/(int value)
{
	return {numerator, denominator * value};
}

numInMatrix numInMatrix::operator+(numInMatrix value)
{
	auto nok = NOK(denominator, value.denominator);
	return {nok / denominator * numerator + nok / value.denominator * value.numerator, nok};
}

numInMatrix numInMatrix::operator-(numInMatrix value)
{
	if (numerator == 0)
	{
		return {-value.numerator, value.denominator};
	}
	if (value.numerator == 0)
	{
		return {numerator, denominator};
	}
	auto nok = NOK(denominator, value.denominator);
	return {nok / denominator * numerator - nok / value.denominator * value.numerator, nok};
}

numInMatrix numInMatrix::operator*(const numInMatrix& value)
{
	return {numerator * value.numerator, denominator * value.denominator};
}

numInMatrix numInMatrix::operator/(numInMatrix value)
{
	if (value.numerator==0)
	{
		throw std::invalid_argument("Числитель должен быть не равен нулю");
	}
	return {numerator * value.denominator, denominator * value.numerator};
}

double numInMatrix::toDouble()
{
	if(numerator==0)
	{
		return 0;
	}
	return (numerator * 1.0) / denominator;
}

bool numInMatrix::operator<(const numInMatrix& num_in_matrix) const
{
	auto nok = NOK(denominator, num_in_matrix.denominator);
	auto leftValue = nok / denominator * numerator;
	auto rightValue = nok / num_in_matrix.denominator * num_in_matrix.numerator;
	if (leftValue < rightValue)
	{
		return true;
	}
	return false;
}

bool numInMatrix::operator!=(const numInMatrix& num_in_matrix) const
{
	if (this->numerator != num_in_matrix.numerator || this->denominator != num_in_matrix.denominator)
	{
		return true;
	}
	return false;
}

bool numInMatrix::operator==(const numInMatrix& num_in_matrix) const
{
	if (this->numerator != num_in_matrix.numerator || this->denominator != num_in_matrix.denominator)
	{
		return false;
	}
	return true;
}

//int NOD(int n1, int n2)
//{
//	if (n1 == n2)
//    {
//	    return n1;
//    }
//	
//    int d = n1 - n2;
//    if (d < 0) {
//        d = -d;
//    }
//    return NOD(n2, d);
//}
int NOD(int a, int b)
{
	if (b == 0 || a == 0)
	{
		if(a==0 && b ==0)
		{
			return 0;
		}
		if(a==0)
		{
			return abs(b);
		}
		if(b==0)
		{
			return abs(a);
		}
	}
	if (a < b)
	{
		std::swap(a, b);
	}

	while (a % b != 0)
	{
		a = a % b;
		std::swap(a, b);
	}
	return b;
}

// Наименьшее общее кратное
int NOK(int n1, int n2)
{
	return n1 * n2 / NOD(n1, n2);
}
