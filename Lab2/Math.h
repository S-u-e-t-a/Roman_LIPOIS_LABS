#pragma once

#include "Matrix.h"

Matrix MakeGilbertMatrix(int order);
void PrintMatrix(Matrix* m);
Matrix* inverse(Matrix* A);
double Det(Matrix* A);
int countOfSymsBeforeSeparator(double num);
std::string getBeautifulViewOfMatrix(Matrix* matrix, int precision);

