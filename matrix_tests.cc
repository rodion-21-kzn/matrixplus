//
// Created by Oznak Banshee on 7/11/23.
//

#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class MatrixTest : public testing::Test {
protected:
    S21Matrix *matrix_1x1;
    S21Matrix *matrix_2x2;
    S21Matrix *matrix_3x3;
    S21Matrix *matrix_2x3;

    void SetUp() {
        matrix_1x1 = new S21Matrix(1,1);
        matrix_2x2 = new S21Matrix(2,2);
        matrix_2x3 = new S21Matrix(2,3); //
        matrix_3x3 = new S21Matrix(3,3);

        matrix_1x1->operator()(0,0) = DBL_MAX;

        matrix_2x2->operator()(0,0) = 1;
        matrix_2x2->operator()(0,1) = 2;
        matrix_2x2->operator()(1,0) = 3;
        matrix_2x2->operator()(1,1) = 4;

        matrix_3x3->operator()(0,0) = 1;
        matrix_3x3->operator()(0,1) = 2;
        matrix_3x3->operator()(0,2) = 3;
        matrix_3x3->operator()(1,0) = 0;
        matrix_3x3->operator()(1,1) = 4;
        matrix_3x3->operator()(1,2) = 2;
        matrix_3x3->operator()(2,0) = 5;
        matrix_3x3->operator()(2,1) = 2;
        matrix_3x3->operator()(2,2) = 1;


    }

    void TearDown() {
        delete matrix_1x1;
        delete matrix_2x2;
        delete matrix_2x3;
        delete matrix_3x3;
    }
};

TEST_F(MatrixTest, ConstructorDefault) {
    S21Matrix test;
    EXPECT_EQ(test.get_cols(), 0);
    EXPECT_EQ(test.get_rows(), 0);
}

TEST_F(MatrixTest, ConstructorExeption1) {
    EXPECT_THROW(S21Matrix test(3,0), std::logic_error);
}

TEST_F(MatrixTest, ConstructorExeption2) {
    EXPECT_THROW(S21Matrix test(-1,2), std::logic_error);
}

TEST_F(MatrixTest, ConstructorParametrized) {
    S21Matrix test(2,3);
    EXPECT_EQ(test.get_cols(), 3);
    EXPECT_EQ(test.get_rows(), 2);
}

TEST_F(MatrixTest, ConstructorCopy) {
    S21Matrix test(*matrix_2x2);
    EXPECT_EQ(test.get_cols(), 2);
    EXPECT_EQ(test.get_rows(), 2);
    EXPECT_EQ(matrix_2x2->get_rows(), 2);
}

TEST_F(MatrixTest, ConstructorMove) {
    S21Matrix test(std::move(*matrix_2x2));
    EXPECT_EQ(test.get_cols(), 2);
    EXPECT_EQ(test.get_rows(), 2);
    EXPECT_EQ(matrix_2x2->get_rows(), 0);
}

TEST_F(MatrixTest, SetCols1) {
    matrix_2x2->set_cols(3);
    EXPECT_EQ(matrix_2x2->get_cols(), 3);
    EXPECT_EQ(matrix_2x2->operator()(1,2), 0);
}

TEST_F(MatrixTest, SetCols2) {
    matrix_2x2->set_cols(1);
    EXPECT_EQ(matrix_2x2->get_cols(), 1);
}

TEST_F(MatrixTest, SetColsExeption) {
    EXPECT_THROW(matrix_2x2->set_cols(-1), std::logic_error);
}

TEST_F(MatrixTest, SetRows1) {
    matrix_3x3->set_rows(3);
    EXPECT_EQ(matrix_3x3->get_rows(), 3);
    EXPECT_EQ(matrix_3x3->operator()(2,2), 1);
}

TEST_F(MatrixTest, SetRows2) {
    matrix_3x3->set_rows(2);
    EXPECT_EQ(matrix_3x3->get_rows(), 2);
}

TEST_F(MatrixTest, SetRowsExeption) {
    EXPECT_THROW(matrix_3x3->set_rows(0), std::logic_error);
}

TEST_F(MatrixTest, EqMatrix) {
    S21Matrix test(2, 2);
    EXPECT_EQ(matrix_3x3->EqMatrix(*matrix_3x3), 1);
    EXPECT_EQ(matrix_3x3->EqMatrix(*matrix_2x3), 0);
    EXPECT_EQ(test.EqMatrix(*matrix_2x2), 0);
}

TEST_F(MatrixTest, EqMatrixOverload) {
    S21Matrix test(2, 2);
    EXPECT_EQ(*matrix_3x3 == *matrix_3x3, 1);
    EXPECT_EQ(*matrix_3x3 == *matrix_2x3, 0);
    EXPECT_EQ(test == *matrix_2x2, 0);
}

TEST_F(MatrixTest, SumMatrix) {
    S21Matrix result(2, 2);
    result(0,0) = 2;
    result(0,1) = 4;
    result(1,0) = 6;
    result(1,1) = 8;
    matrix_2x2->SumMatrix(*matrix_2x2);
    EXPECT_EQ(*matrix_2x2 == result, 1);
}

TEST_F(MatrixTest, SumMatrixOverload1) {
    S21Matrix result(2, 2);
    result(0,0) = 2;
    result(0,1) = 4;
    result(1,0) = 6;
    result(1,1) = 8;
    *matrix_2x2 = *matrix_2x2 + *matrix_2x2;
    EXPECT_EQ(*matrix_2x2 == result, 1);
}

TEST_F(MatrixTest, SumMatrixOverload2) {
    S21Matrix result(2, 2);
    result(0,0) = 2;
    result(0,1) = 4;
    result(1,0) = 6;
    result(1,1) = 8;
    *matrix_2x2 += *matrix_2x2;
    EXPECT_EQ(*matrix_2x2 == result, 1);
}

TEST_F(MatrixTest, SumMatrixExeption1) {
    EXPECT_THROW(matrix_2x2->SumMatrix(*matrix_2x3), std::logic_error);
}

TEST_F(MatrixTest, SumMatrixExeption2) {
    EXPECT_THROW(matrix_1x1->SumMatrix(*matrix_1x1), std::overflow_error);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}