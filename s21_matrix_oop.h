//
// Created by Oznak Banshee on 5/18/23.
//

#ifndef MATRIXPLUS_S21_MATRIX_OOP_H
#define MATRIXPLUS_S21_MATRIX_OOP_H

#include <iostream>
#include <cmath>
#include <cfloat>

class S21Matrix {
private:
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

    int GetRows() const;
    int GetCols() const;
    void SetCols(int cols);
    void SetRows(int rows);
    void SetSize(int rows, int cols);

    // SUPPORT

    void PrintData();
    void InputData();

};



#endif //MATRIXPLUS_S21_MATRIX_OOP_H
