// C ++ программа для поиска обратной матрицы.


#include <iostream>
#include <vector>
#include "test.h"

#include "Math.h"

using namespace std;


//http://espressocode.top/finding-inverse-of-a-matrix-using-gauss-jordan-method/ https://www.geeksforgeeks.org/finding-inverse-of-a-matrix-using-gauss-jordan-method/
Matrix* InverseOMatrix(Matrix* matrix)

{
	numInMatrix temp{0,1};

    int order = matrix->getColCount();

	// копируем начальную матрицу
    auto augmentedMatrix = Matrix(order,order*2);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
        	augmentedMatrix(i,j) = matrix->operator()(i,j);
        }
    }
    // заполняем правую часть расширенной матрицы единичной матрицей
    for (int i = 0; i < order; i++) {
        for (int j = order; j < 2 * order; j++) {
            if (j == (i + order))
            {
                augmentedMatrix(i, j) = 1;
            }
            else
            {
                augmentedMatrix(i, j) = 0;
            }
        }
    }
	for (int nrow = 0; nrow < order; ++nrow)
	{
        auto divider = augmentedMatrix(nrow, nrow);
        for (int i = 0; i < order*2; ++i)
        {
            augmentedMatrix(nrow, i) = augmentedMatrix(nrow, i) / divider;
        }

        for (int lowerRow = nrow+1; lowerRow < order; ++lowerRow)
        {
            auto factor = augmentedMatrix(lowerRow, nrow);
            for (int i = 0; i < order*2; ++i)
            {
                augmentedMatrix(lowerRow, i) = augmentedMatrix(lowerRow, i)- factor * augmentedMatrix(nrow, i);
            }
        }
	}
    PrintMatrix(&augmentedMatrix);
	for (int col = order - 1; col >= 1; --col)
	{
		for (int row = col - 1; row >= 0; --row)
		{
            std::cout << row << " " << col << std::endl;
            auto factor = augmentedMatrix(row, col);
            for (int i = 0; i < order*2; ++i)
            {
                augmentedMatrix(row, i) = augmentedMatrix(row, i)- augmentedMatrix(col, i) * factor;
            }
		}
	}

    PrintMatrix(&augmentedMatrix);
    auto result = new Matrix(order, order);
	for (int i = 0; i < order; ++i)
	{
		for (int j = 0; j < order; ++j)
		{
            result->operator()(i,j) = augmentedMatrix(i, order + j);
		}
	}
    return result;
}

