#pragma once
struct numInMatrix
{
public:
    numInMatrix();
    numInMatrix(long long value);
    //numInMatrix(double value);
    //numInMatrix(const numInMatrix& nim);
    numInMatrix(long long numer, long long denom);
    long long numerator, denominator;
    numInMatrix& operator = (long long value);
    numInMatrix operator + (long long value) const;
    numInMatrix operator - (long long value) const;
    numInMatrix operator * (long long value) const;
    numInMatrix operator / (long long value) const;

    numInMatrix operator + (const numInMatrix& value) const;
    numInMatrix operator - (const numInMatrix& value) const;
    numInMatrix operator*(const numInMatrix& value) const;
    numInMatrix operator / (const numInMatrix& value) const;

    bool operator<(const numInMatrix& num_in_matrix) const;
    bool operator>(const numInMatrix& num_in_matrix) const;
    bool operator!=(const numInMatrix& num_in_matrix) const;
    bool operator==(const numInMatrix& num_in_matrix) const;
    explicit operator double() const;
};

long long NOK(long long n1, long long n2);
long long NOD(long long n1, long long n2);


