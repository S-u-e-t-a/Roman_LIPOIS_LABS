// C ++ программа дл€ поиска обратной матрицы.


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
    // заполн€ем правую часть расширенной матрицы единичной матрицей
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
    //PrintMatrix(&augmentedMatrix);
    // сортировка строк
    for (int i = order - 1; i > 0; i--) {
         if (augmentedMatrix(i - 1, 0) < augmentedMatrix(i,0))
         {
             for (int j = 0; j < 2 * order; j++) {
                 temp = augmentedMatrix(i, j);
                 augmentedMatrix(i, j) = augmentedMatrix(i - 1, j);
                 augmentedMatrix(i - 1, j) = temp;
             }
         }
    }

    PrintMatrix(&augmentedMatrix);

    // «аменить строку на сумму самого себ€ и константа, кратна€ другой строке матрицы

    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            if (j != i) {
                numInMatrix ji = augmentedMatrix(j, i);
                numInMatrix ii = augmentedMatrix(i, i);
                //
                temp = augmentedMatrix(j,i) / augmentedMatrix(i,i);
                for (int k = 0; k < 2 * order; k++) 
                {
                    numInMatrix ik = augmentedMatrix(i, k);
                    numInMatrix at = ik * temp;
                    augmentedMatrix(j, k) = augmentedMatrix(j, k) - augmentedMatrix(i, k) * temp;
                    //augmentedMatrix(j,k) -= augmentedMatrix(i,k) * temp;
                }
            }
        }
        PrintMatrix(&augmentedMatrix);

    }
    PrintMatrix(&augmentedMatrix);
    // ”множаем каждую строку на ненулевое целое число.
    // ƒелим элемент строки по диагональному элементу

    for (int i = 0; i < order; i++) {
        temp = augmentedMatrix(i,i);
        for (int j = 0; j < 2 * order; j++) {
            augmentedMatrix(i,j) = augmentedMatrix(i,j) / temp;
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
    PrintMatrix(result);
    return result;
}

