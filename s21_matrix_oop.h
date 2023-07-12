//
// Created by Oznak Banshee on 5/18/23.
//

#ifndef MATRIXPLUS_S21_MATRIX_OOP_H
#define MATRIXPLUS_S21_MATRIX_OOP_H

#include <iostream>
#include <cmath>
#include <cfloat>

class S21Matrix {


public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other) noexcept;
    ~S21Matrix();
    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();
    int get_rows() const;
    int get_cols() const;
    void set_cols(int cols);
    void set_rows(int rows);
    bool operator==(const S21Matrix& other);
    S21Matrix& operator=(const S21Matrix& other);
    S21Matrix& operator=(S21Matrix&& other) noexcept;
    S21Matrix operator+(const S21Matrix& other);
    S21Matrix operator-(const S21Matrix& other);
    S21Matrix operator*(const S21Matrix& other);
    S21Matrix operator*(double x);
    S21Matrix& operator+=(const S21Matrix& other);
    S21Matrix& operator-=(const S21Matrix& other);
    S21Matrix& operator*=(const S21Matrix& other);
    S21Matrix& operator*=(double x);
    double& operator()(int i, int j);
    double operator()(int i, int j) const;

private:
    int rows_, cols_;
    double **matrix_;
    void AllocatingMemory();
    void DeleteMatrix();
    void CopyMatrixData(const S21Matrix &other);
    S21Matrix FillMinor(int delete_row, int delete_column);
};



#endif //MATRIXPLUS_S21_MATRIX_OOP_H
