// Lab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <mpirxx.h>
#include <iostream>
#include "Math.h"
#include "Matrix.h"

//#include "test.h"


//std::vector<std::vector<double>> analyze(int from, int to)
//{
//    std::vector<std::vector<double>> results = std::vector<std::vector<double>>(6);
//    for (int i = 0; i < 6; ++i)
//    {
//        results[i] = std::vector<double>(to - from+2);
//    }
//    for (int i = from; i < to + 1; ++i)
//    {
//        auto floatMatrix = MakeGilbertMatrix<float>(i);
//        auto floatInverted = floatMatrix.getInverted();
//        auto floatLeft = makeLeftResidualMatrix(&floatMatrix, floatInverted);
//        auto floatRight = makeRightResidualMatrix(&floatMatrix, floatInverted);
//        results[0][i] = getRowNorm(&floatLeft);
//        results[1][i] = getRowNorm(&floatRight);
//
//        auto doubleMatrix = MakeGilbertMatrix<double>(i);
//        auto doubleInverted = doubleMatrix.getInverted();
//        auto doubleLeft = makeLeftResidualMatrix(&doubleMatrix, doubleInverted);
//        auto doubleRight = makeRightResidualMatrix(&doubleMatrix, doubleInverted);
//        results[2][i] = getRowNorm(&doubleLeft);
//        results[3][i] = getRowNorm(&doubleRight);
//        if (i<13)
//        {
//            auto myNumMatrix = MakeGilbertMatrix<numInMatrix>(i);
//            auto myNumInverted = myNumMatrix.getInverted();
//            auto myNumLeft = makeLeftResidualMatrix(&myNumMatrix, myNumInverted);
//            auto myNumRight = makeRightResidualMatrix(&myNumMatrix, myNumInverted);
//            results[4][i] = getRowNorm(&myNumLeft);
//            results[5][i] = getRowNorm(&myNumRight);
//        }
//        else
//        {
//            results[4][i] = NAN;
//            results[5][i] = NAN;
//        }
//    }
//    return results;
//}



int main()
{
    //mpz_class a, b, c;
    //a = 1234;
    //b = "-5678";
    //c = a + b;
    //std::cout << "sum is " << c << "\n";
    //std::cout << "absolute value is " << abs(c) << "\n";


    auto order = 100;
    
    auto m = MakeGilbertMatrix<mpq_class>(order);
    std::cout << "----------------- initial matrix ------------------" << std::endl;
    PrintMatrix(&m);

    std::cout << "----------------- inversed -----------------------" << std::endl;
    auto inv = m.getInverted();
    PrintMatrix(inv);

    //std::cout << "--------------------initial * inversed------------------" << std::endl;
    auto C = m * inv;
    auto idenity = Matrix<mpz_class>::GenerateIdentityMatrix(order);
    C = C - &idenity;
    PrintMatrix(&C);
    auto left = makeLeftResidualMatrix(&m, inv);
    auto right = makeRightResidualMatrix(&m, inv);

    //PrintMatrix(&left);
    //PrintMatrix(&right);
    //auto leftNorm = getRowNorm(&left);
    //auto rightNorm = getRowNorm(&right);
    //std::cout << "left norm = " <<leftNorm << std::endl;
    //std::cout << "right norm = " <<rightNorm << std::endl;
    auto s = std::string();
    std::cin >> s;
    //std::vector<std::string> headers = { "float l","float r","double l", "double r", "myNum l", "myNum R"};
    //auto nums = analyze(1, 50);
    //auto strNums = std::vector<std::vector<std::string>>(6);
    //auto precision = 2;
    //for (int i = 0; i < nums.size(); ++i)
    //{
    //    strNums[i] = std::vector<std::string>(nums[0].size());
	   // for (int j = 0; j < nums[0].size(); ++j)
	   // {
    //        std::stringstream ss;
    //        ss << std::fixed << std::setprecision(precision) << nums[i][j];
    //        strNums[i][j] = ss.str();

	   // }
    //}
    //printTable(normalizeTable(makeTable(headers, strNums)));
}
