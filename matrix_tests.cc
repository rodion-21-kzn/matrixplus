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

TEST_F(MatrixTest, Constructor) {
    S21Matrix test;
    EXPECT_EQ(test.get_cols(), 0);
    EXPECT_EQ(test.get_rows(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}