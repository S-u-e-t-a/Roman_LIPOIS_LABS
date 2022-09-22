// C ++ программа для поиска обратной матрицы.


#include <iostream>
#include <vector>
#include "test.h"

#include "Math.h"

using namespace std;



Matrix* InverseOMatrix(Matrix* matrix)

{
	double temp;

    int order = matrix->getColCount();

    // Создаем расширенную матрицу
    // Добавить идентификационную матрицу
    // порядка в конце исходной матрицы.
    auto augmentedMatrix = Matrix(order,order*2);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
        	augmentedMatrix(i,j) = matrix->operator()(i,j);
        }
    }
    for (int i = 0; i < order; i++) {
        for (int j = order; j < 2 * order; j++) {
            // Добавить '1' в диагональных местах
            // матрица для создания идентичности matirx
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

    // Меняем строку матрицы, смена ряда начнется с последнего ряда
    for (int i = order - 1; i > 0; i--) {

        // Меняем местами каждый элемент двух строк
         if (augmentedMatrix(i - 1, 0) < augmentedMatrix(i,0))
         for (int j = 0; j <2 * order; j ++) {

         // Перестановка строки, если выше условие выполнено.
         temp = augmentedMatrix(i,j);
         augmentedMatrix(i, j) = augmentedMatrix(i-1,j);
         augmentedMatrix(i-1,j) = temp;
        }
    }

    // Заменить строку на сумму самого себя и константа, кратная другой строке матрицы

    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            if (j != i) {
                temp = augmentedMatrix(j,i) / augmentedMatrix(i,i);
                for (int k = 0; k < 2 * order; k++) {
                    augmentedMatrix(j,k) -= augmentedMatrix(i,k) * temp;
                }
            }
        }
    }

    // Умножаем каждую строку на ненулевое целое число.
    // Делим элемент строки по диагональному элементу

    for (int i = 0; i < order; i++) {
        temp = augmentedMatrix(i,i);
        for (int j = 0; j < 2 * order; j++) {
            augmentedMatrix(i,j) = augmentedMatrix(i,j) / temp;
        }
    }

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

