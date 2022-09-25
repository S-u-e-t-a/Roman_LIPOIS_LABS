// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math.h"
#include "Matrix.h"
//#include "test.h"
int main()
{
    Matrix m = MakeGilbertMatrix(12);
    std::cout << "----------------- initial matrix ------------------" << std::endl;
    PrintMatrix(&m);
    auto idenity = Matrix::GenerateIdentityMatrix(12);
    auto s = std::string();
    std::cout << "----------------- inversed -----------------------" << std::endl;
    auto inv = m.getInverted();
    PrintMatrix(inv);
    auto C = m * inv;
    C = C - &idenity;
    std::cout << "--------------------initial * inversed------------------" << std::endl;
    PrintMatrix(&C);
    numInMatrix n{5,1};
    n = n / 2;
    std::cout << n.numerator << " " << n.denominator;
    std::cin >> s;
}

