#pragma once

#include <stdexcept>
#include <vector>
//https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op
class Matrix {
public:
    Matrix(unsigned rows, unsigned cols);
    double& operator() (unsigned row, unsigned col);        // Subscript operators often come in pairs
    double  operator() (unsigned row, unsigned col) const;  // Subscript operators often come in pairs
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
    std::vector<double> data_;
};



