#include "pch.h"
#include "../Lab2/Math.h"
#include "../Lab2/Math.cpp"
#include "../Lab2/Matrix.h"
#include "../Lab2/Matrix.cpp"

bool matrixEqualeMatrix(Matrix* a, Matrix *b)
{
	if (a->getColCount()!=b->getColCount() || a->getRowCount()!=b->getRowCount())
	{
		return false;
	}
	for (int i = 0; i < a->getRowCount(); ++i)
	{
		for (int j = 0; j < a->getColCount(); ++j)
		{
			if (a->operator()(i,j)!=b->operator()(i,j))
			{
				return false;
			}
		}
	}
	return true;
}
TEST(gilbertTest, TestName) {
	auto gb = MakeGilbertMatrix(3);
	EXPECT_EQ(1.0, gb(0, 0));
	EXPECT_EQ(1.0/2, gb(0, 1));
	EXPECT_EQ(1.0 /3, gb(0, 2));
	EXPECT_EQ(1.0 /2, gb(1, 0));
	EXPECT_EQ(1.0 /3, gb(1, 1));
	EXPECT_EQ(1.0 /4, gb(1, 2));
	EXPECT_EQ(1.0 /3, gb(2, 0));
	EXPECT_EQ(1.0 /4, gb(2, 1));
	EXPECT_EQ(1.0 /5, gb(2, 2));
}

TEST(minortest, threeXthreeMatrix) {
	auto gb = MakeGilbertMatrix(3);

	auto m00 = gb.get_minor(0, 0);
	auto em00 = new Matrix(2, 2);
	em00->operator()(0, 0) = 1.0 / 3;
	em00->operator()(0, 1) = 1.0 / 4;
	em00->operator()(1, 0) = 1.0 / 4;
	em00->operator()(1, 1) = 1.0 / 5;

	auto m01 = gb.get_minor(0, 1);
	auto em01 = new Matrix(2, 2);
	em01->operator()(0, 0) = 1.0 / 2;
	em01->operator()(0, 1) = 1.0 / 4;
	em01->operator()(1, 0) = 1.0 / 3;
	em01->operator()(1, 1) = 1.0 / 5;

	auto m02 = gb.get_minor(0, 2);
	auto em02 = new Matrix(2, 2);
	em02->operator()(0, 0) = 1.0 / 2;
	em02->operator()(0, 1) = 1.0 / 3;
	em02->operator()(1, 0) = 1.0 / 3;
	em02->operator()(1, 1) = 1.0 / 4;

	auto m10 = gb.get_minor(1, 0);
	auto em10 = new Matrix(2, 2);
	em10->operator()(0, 0) = 1.0 / 2;
	em10->operator()(0, 1) = 1.0 / 3;
	em10->operator()(1, 0) = 1.0 / 4;
	em10->operator()(1, 1) = 1.0 / 5;

	auto m11 = gb.get_minor(1, 1);
	auto em11 = new Matrix(2, 2);
	em11->operator()(0, 0) = 1.0 / 1;
	em11->operator()(0, 1) = 1.0 / 3;
	em11->operator()(1, 0) = 1.0 / 3;
	em11->operator()(1, 1) = 1.0 / 5;

	auto m12 = gb.get_minor(1, 2);
	auto em12 = new Matrix(2, 2);
	em12->operator()(0, 0) = 1.0 / 1;
	em12->operator()(0, 1) = 1.0 / 2;
	em12->operator()(1, 0) = 1.0 / 3;
	em12->operator()(1, 1) = 1.0 / 4;

	auto m20 = gb.get_minor(2, 0);
	auto em20 = new Matrix(2, 2);
	em20->operator()(0, 0) = 1.0 / 2;
	em20->operator()(0, 1) = 1.0 / 3;
	em20->operator()(1, 0) = 1.0 / 3;
	em20->operator()(1, 1) = 1.0 / 4;

	auto m21 = gb.get_minor(2, 1);
	auto em21 = new Matrix(2, 2);
	em21->operator()(0, 0) = 1.0 / 1;
	em21->operator()(0, 1) = 1.0 / 3;
	em21->operator()(1, 0) = 1.0 / 2;
	em21->operator()(1, 1) = 1.0 / 4;

	auto m22 = gb.get_minor(2, 2);
	auto em22 = new Matrix(2, 2);
	em22->operator()(0, 0) = 1.0 / 1;
	em22->operator()(0, 1) = 1.0 / 2;
	em22->operator()(1, 0) = 1.0 / 2;
	em22->operator()(1, 1) = 1.0 / 3;

	EXPECT_TRUE(matrixEqualeMatrix(em00, m00));
	EXPECT_TRUE(matrixEqualeMatrix(em01, m01));
	EXPECT_TRUE(matrixEqualeMatrix(em02, m02));
	EXPECT_TRUE(matrixEqualeMatrix(em10, m10));
	EXPECT_TRUE(matrixEqualeMatrix(em11, m11));
	EXPECT_TRUE(matrixEqualeMatrix(em12, m12));
	EXPECT_TRUE(matrixEqualeMatrix(em20, m20));
	EXPECT_TRUE(matrixEqualeMatrix(em21, m21));
	EXPECT_TRUE(matrixEqualeMatrix(em22, m22));
}

TEST(minortest, twoXtwoMatrix) {
	auto gb = MakeGilbertMatrix(2);

	auto m00 = gb.get_minor(0, 0);
	auto em00 = new Matrix(1, 1);
	em00->operator()(0, 0) = 1.0 / 3;

	auto m01 = gb.get_minor(0, 1);
	auto em01 = new Matrix(1, 1);
	em01->operator()(0, 0) = 1.0 / 2;

	auto m10 = gb.get_minor(1, 0);
	auto em10 = new Matrix(1, 1);
	em10->operator()(0, 0) = 1.0 / 2;

	auto m11 = gb.get_minor(1, 1);
	auto em11 = new Matrix(1, 1);
	em11->operator()(0, 0) = 1.0 / 1;

	EXPECT_TRUE(matrixEqualeMatrix(em00, m00));
	EXPECT_TRUE(matrixEqualeMatrix(em01, m01));
	EXPECT_TRUE(matrixEqualeMatrix(em10, m10));
	EXPECT_TRUE(matrixEqualeMatrix(em11, m11));
}

TEST(determinantTest, oneXoneMatrix)
{
	auto m1 = new Matrix(1, 1);
	auto m2 = new Matrix(1, 1);
	auto m3 = new Matrix(1, 1);
	auto m4 = new Matrix(1, 1);
	m1->operator()(0,0) = 1;
	m2->operator()(0, 0) = 57;
	m3->operator()(0, 0) = 1.0/2;
	m4->operator()(0, 0) = 3.14;

	EXPECT_EQ(1.0, Det(m1));
	EXPECT_EQ(57.0, Det(m2));
	EXPECT_EQ(1.0/2, Det(m3));
	EXPECT_EQ(3.14, Det(m4));

}

TEST(determinantTest, twoXtwoMatrix)
{
	auto m1 = new Matrix(2, 2);
	m1->operator()(0, 0) = 5;
	m1->operator()(0, 1) = 7;
	m1->operator()(1, 0) = -4;
	m1->operator()(1, 1) = 1;

	auto expextedDet = 33.0;

	EXPECT_NEAR(expextedDet, Det(m1),0.000001);
}

TEST(determinantTest, twoXtwoMatrix2)
{
	auto m1 = MakeGilbertMatrix(2);

	auto expextedDet = 1.0/12;

	EXPECT_NEAR(expextedDet, Det(&m1),0.000001);
}

TEST(determinantTest, gilbertThreeMatrix)
{
	auto m1 = MakeGilbertMatrix(3);

	auto expextedDet = 1.0 / 2160;

	EXPECT_NEAR(expextedDet, Det(&m1), 0.000001);
}

TEST(determinantTest, gilbertFourMatrix)
{
	auto m1 = MakeGilbertMatrix(4);

	auto expextedDet = 1.0 / 6048000;

	EXPECT_NEAR(expextedDet, Det(&m1), 0.000001);
}

TEST(multipleTest, test1)
{
	auto k = Matrix(2, 2);
	auto l = Matrix(2, 1);
	k(0, 0) = -2;
	k(0, 1) = 1;
	k(1, 0) = 5;
	k(1, 1) = 4;

	l(0, 0) = 3;
	l(1, 0) = -1;

	auto kl = k * &l;

	EXPECT_EQ(1, kl.getColCount());
	EXPECT_EQ(2, kl.getRowCount());
	EXPECT_EQ(-7, kl(0, 0));
	EXPECT_EQ(11, kl(1, 0));
}
TEST(multipleTest, test2)
{
	auto k = Matrix(4, 4);
	auto l = Matrix(4, 4);
	k(0, 0) = 1;
	k(0, 1) = 0;
	k(0, 2) = 2;
	k(0, 3) = -1;
	k(1, 0) = -2;
	k(1, 1) = 0;
	k(1, 2) = -4;
	k(1, 3) = 2;
	k(2, 0) = 1;
	k(2, 1) = 0;
	k(2, 2) = 2;
	k(2, 3) = -1;
	k(3, 0) = 3;
	k(3, 1) = 0;
	k(3, 2) = 6;
	k(3, 3) = -3;

	l(0, 0) = 2;
	l(0, 1) = 1;
	l(0, 2) = 3;
	l(0, 3) = -1;
	l(1, 0) = -4;
	l(1, 1) = -2;
	l(1, 2) = -6;
	l(1, 3) = 2;
	l(2, 0) = 2;
	l(2, 1) = 1;
	l(2, 2) = 3;
	l(2, 3) = -1;
	l(3, 0) = 6;
	l(3, 1) = 3;
	l(3, 2) = 9;
	l(3, 3) = -3;
	auto kl = k * &l;

	//PrintMatrix(&kl);
	EXPECT_EQ(4, kl.getColCount());
	EXPECT_EQ(4, kl.getRowCount());
	EXPECT_EQ(0, kl(0, 0));
	EXPECT_EQ(0, kl(1, 0));
}

TEST(countOfSymInNumber, test1)
{
	EXPECT_EQ(3, countOfSymsBeforeSeparator(500));
	EXPECT_EQ(4, countOfSymsBeforeSeparator(-500));
	EXPECT_EQ(1, countOfSymsBeforeSeparator(1));
	EXPECT_EQ(1, countOfSymsBeforeSeparator(0.5));
	EXPECT_EQ(2, countOfSymsBeforeSeparator(-1));
	EXPECT_EQ(2, countOfSymsBeforeSeparator(-0.5));
}