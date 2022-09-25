#pragma once

#include <stdexcept>
#include <vector>
struct numInMatrix;

//https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op
class Matrix {
public:
    Matrix(unsigned rows, unsigned cols);
    numInMatrix& operator() (unsigned row, unsigned col);        // Subscript operators often come in pairs
    numInMatrix  operator() (unsigned row, unsigned col) const;  // Subscript operators often come in pairs
    // ...
    ~Matrix();                              // Destructor
    Matrix(const Matrix& m);               // Copy constructor
    Matrix& operator= (const Matrix& m);   // Assignment operator
    Matrix operator * (const Matrix* m);
    Matrix operator - (const Matrix* m);
    Matrix operator + (const Matrix* m);
    unsigned getRowCount() const;
    unsigned getColCount() const;
    static Matrix GenerateIdentityMatrix(int size);
    //Matrix* Minor
    Matrix* get_minor(int i, int j);
private:
    unsigned rows_, cols_;
    std::vector<numInMatrix> data_;
};

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
    numInMatrix operator + (long long value);
    numInMatrix operator - (long long value);
    numInMatrix operator * (long long value);
    numInMatrix operator / (long long value);

    numInMatrix operator + (numInMatrix value);
    numInMatrix operator - (numInMatrix value);
    numInMatrix operator*(const numInMatrix& value);
    //numInMatrix operator * (numInMatrix value);
    numInMatrix operator / (numInMatrix value);
    double toDouble();
    bool operator<(const numInMatrix& num_in_matrix) const;
    bool operator!=(const numInMatrix& num_in_matrix) const;
    bool operator==(const numInMatrix& num_in_matrix) const;
};

long long NOK(long long n1, long long n2);
long long NOD(long long n1, long long n2);
