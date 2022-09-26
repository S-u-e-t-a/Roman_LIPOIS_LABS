#include "numInMatriix.h"

#include <stdexcept>

numInMatrix::numInMatrix()
{
	numerator = 0;
	denominator = 1;
}

numInMatrix::numInMatrix(long long value)
{
	numerator = value;
	denominator = 1;
}

numInMatrix::numInMatrix(long long numer, long long denom)
{
	if (denom == 0)
	{
		throw std::invalid_argument("Делитель не должен быть равен нулю!");
	}
	auto nod = NOD(numer, denom);
	numerator = numer / nod;
	denominator = denom / nod;
}

numInMatrix& numInMatrix::operator=(const long long value)
{
	numerator = value;
	denominator = 1;
	return *this;
}

numInMatrix numInMatrix::operator+(long long value) const
{
	return { numerator + denominator * value, denominator };
}

numInMatrix numInMatrix::operator-(long long value) const
{
	return { numerator - denominator * value, denominator };
}

numInMatrix numInMatrix::operator*(long long value) const
{
	return { numerator * value, denominator };
}

numInMatrix numInMatrix::operator/(long long value) const
{
	return { numerator, denominator * value };
}

numInMatrix numInMatrix::operator+(const numInMatrix& value) const
{
	auto nok = NOK(denominator, value.denominator);
	return { nok / denominator * numerator + nok / value.denominator * value.numerator, nok };
}

numInMatrix numInMatrix::operator-(const numInMatrix& value) const
{
	if (numerator == 0)
	{
		return { -value.numerator, value.denominator };
	}
	if (value.numerator == 0)
	{
		return { numerator, denominator };
	}
	auto nok = NOK(denominator, value.denominator);
	return { nok / denominator * numerator - nok / value.denominator * value.numerator, nok };
}

numInMatrix numInMatrix::operator*(const numInMatrix& value) const
{
	return { numerator * value.numerator, denominator * value.denominator };
}

numInMatrix numInMatrix::operator/(const numInMatrix& value) const
{
	if (value.numerator == 0)
	{
		throw std::invalid_argument("Числитель должен быть не равен нулю");
	}
	return { numerator * value.denominator, denominator * value.numerator };
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

bool numInMatrix::operator>(const numInMatrix& num_in_matrix) const
{
	auto nok = NOK(denominator, num_in_matrix.denominator);
	auto leftValue = nok / denominator * numerator;
	auto rightValue = nok / num_in_matrix.denominator * num_in_matrix.numerator;
	if (leftValue > rightValue)
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

numInMatrix::operator double() const
{
	if (numerator == 0)
	{
		return 0;
	}
	return (numerator * 1.0) / denominator;
}

long long NOD(long long a, long long b)
{
	if (b == 0 || a == 0)
	{
		if (a == 0 && b == 0)
		{
			return 0;
		}
		if (a == 0)
		{
			return abs(b);
		}
		if (b == 0)
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
long long NOK(long long n1, long long n2)
{
	auto nod = NOD(n1, n2);
	if (n1 > n2)
	{
		n1 = n1 / nod;
	}
	else
	{
		n2 = n2 / nod;
	}
	return n1 * n2;
}
