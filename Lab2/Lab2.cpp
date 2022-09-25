// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Math.h"
#include "Matrix.h"
#include "test.h"
int main()
{
    //std::getchar();
    Matrix m = MakeGilbertMatrix(12);
    /*Matrix m =  Matrix(3, 3);
    m(0, 0) = 3;
    m(0, 1) = 4;
    m(0, 2) = 2;
    m(1, 0) = 2;
    m(1, 1) = -1;
    m(1, 2) = -3;
    m(2, 0) = 1;
    m(2, 1) = 5;
    m(2, 2) = 1;*/
    std::cout << "-----------------initialmatrix------------------" << std::endl;
    PrintMatrix(&m);
    //std::cout << "-----------------inverced by first-----------------------" << std::endl;
    //PrintMatrix(inverse(&m));
    //auto C =  m*inverse(&m);
    auto idenity = Matrix::GenerateIdentityMatrix(12);
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
    numInMatrix n{5,1};
    n = n / 2;
    std::cout << n.numerator << " " << n.denominator;
    std::cin >> s;
}

