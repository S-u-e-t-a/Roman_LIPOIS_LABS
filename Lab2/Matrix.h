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
    numInMatrix(int value);
    //numInMatrix(double value);
    //numInMatrix(const numInMatrix& nim);
    numInMatrix(int numer, int denom);
    int numerator, denominator;
    numInMatrix& operator = (int value);
    numInMatrix operator + (int value);
    numInMatrix operator - (int value);
    numInMatrix operator * (int value);
    numInMatrix operator / (int value);

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

int NOK(int n1, int n2);
int NOD(int n1, int n2);
