#include "Matrix.h"

Matrix::Matrix(unsigned rows, unsigned cols): rows_(rows), cols_(cols)//, data_ ← initialized below after the if...throw statement
{
    if (rows == 0 || cols == 0)
        throw std::invalid_argument("Matrix constructor has 0 size");
    data_ = std::vector<double>(rows_ * cols_);
}

Matrix::Matrix(const Matrix& matrix)
{
	rows_ = matrix.rows_;
	cols_ = matrix.cols_;
    data_ = std::vector<double>(rows_ * cols_);
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
    data_ = std::vector<double>(rows_*cols_);
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
    if (this->getColCount()!=m->getRowCount())
    {
        throw std::invalid_argument("Количество столбцов левой матрицы должно равняться количеству строк правой матрицы");
    }
    auto A = this;
    auto B = m;
    auto C = Matrix(A->getRowCount(), B->getColCount());
    auto p = this->getColCount();
    for (int i = 0; i < C.getRowCount(); ++i)
    {
	    for (int j = 0; j < C.getColCount(); ++j)
	    {
            auto cij = 0.0;
            for (int k = 0; k < p; ++k)
            {
                cij += A->operator()(i, k) * B->operator()(k, j);
            }
            C(i, j) = cij;
	    }
    }

    return C;
}

Matrix Matrix::operator-(const Matrix* m)
{
	if (this->getColCount()!=m->getColCount() || this->getRowCount()!=m->getRowCount())
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
    while (i<this->getRowCount())
    {
	    if (i==ii)
	    {
            i += 1;
            continue;
	    }
        auto j = 0;
	    while (j<this->getColCount())
	    {
            if (j == jj)
            {
                j += 1;
                continue;
            }
            int row, col;
            if (c==0)
            {
            	row = 0;
            	col = 0;
            }
            else
            {
                row = c/(minor->getRowCount());
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

double& Matrix::operator() (unsigned row, unsigned col)
{
    if (row >= rows_ || col >= cols_)
        throw std::invalid_argument("Matrix subscript out of bounds");
    return data_[cols_ * row + col];
}

double Matrix::operator() (unsigned row, unsigned col) const
{
    if (row >= rows_ || col >= cols_)
        throw std::invalid_argument("const Matrix subscript out of bounds");
    return data_[cols_ * row + col];
}