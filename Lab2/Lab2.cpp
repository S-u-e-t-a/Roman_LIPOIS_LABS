// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math.h"
#include "Matrix.h"
#include "test.h"
int main()
{
    std::getchar();
    Matrix m = MakeGilbertMatrix(11);
    std::cout << "-----------------initialmatrix------------------" << std::endl;
    PrintMatrix(&m);
    //std::cout << "-----------------inverced by first-----------------------" << std::endl;
    //PrintMatrix(inverse(&m));
    //auto C =  m*inverse(&m);
    auto idenity = Matrix::GenerateIdentityMatrix(11);
    //C = C - &idenity;
    //std::cout << "-----------------initial * invverced by first-----------------------" << std::endl;
    //PrintMatrix(&C);
    auto s = std::string();
    std::cout << "-----------------inverced by second -----------------------" << std::endl;
    auto inv = InverseOMatrix(&m);
    PrintMatrix(inv);
    auto C = m * inv;
    C = C - &idenity;
    std::cout << "--------------------initial * invverced by second------------------" << std::endl;
    PrintMatrix(&C);

    std::cin >> s;
}

