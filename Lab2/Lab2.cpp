// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math.h"
#include "Matrix.h"
//#include "test.h"
int main()
{
    auto order = 15;

    Matrix<double> m = MakeGilbertMatrix<double>(order);
    std::cout << "----------------- initial matrix ------------------" << std::endl;
    PrintMatrix(&m);

    std::cout << "----------------- inversed -----------------------" << std::endl;
    auto inv = m.getInverted();
    PrintMatrix(inv);

    std::cout << "--------------------initial * inversed------------------" << std::endl;
    auto C = m * inv;
    auto idenity = Matrix<numInMatrix>::GenerateIdentityMatrix(order);
    C = C - &idenity;
    PrintMatrix(&C);

    auto s = std::string();
    std::cin >> s;
}

