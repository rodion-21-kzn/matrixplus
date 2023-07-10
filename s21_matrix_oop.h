//
// Created by Oznak Banshee on 5/18/23.
//

#ifndef MATRIXPLUS_S21_MATRIX_OOP_H
#define MATRIXPLUS_S21_MATRIX_OOP_H

#include <iostream>
#include <cmath>
#include <cfloat>

class S21Matrix {
private: // паблик и прайват поменять местами
    // Attributes
    int rows_, cols_;         // Rows and columns
    double **matrix_;         // Pointer to the memory where the matrix is allocated

    void AllocatingMemory(); // переиспользую в конструкторах


public:
    S21Matrix();              // Default constructor
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);

    ~S21Matrix();             // Destructor

    // Matrix func

    bool EqMatrix(const S21Matrix& other);
    void SumMatrix(const S21Matrix& other);
    void SubMatrix(const S21Matrix& other);
    void MulNumber(const double num);
    void MulMatrix(const S21Matrix& other);
    S21Matrix Transpose();
    S21Matrix CalcComplements();
    double Determinant();
    S21Matrix InverseMatrix();

    // GET and SET

    int get_rows() const;
    int get_cols() const;
    void set_cols(int cols);
    void set_rows(int rows);

    // SUPPORT

    void PrintData();
    void InputData();
    void DeleteMatrix();
    void CopyMatrixData(const S21Matrix &other);
    S21Matrix FillMinor(int delete_row, int delete_column);

    // Operators

    bool operator==(const S21Matrix& other);
    S21Matrix& operator=(const S21Matrix& other); // копирование
    S21Matrix& operator=(S21Matrix&& other); // перемещение
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
};



#endif //MATRIXPLUS_S21_MATRIX_OOP_H
