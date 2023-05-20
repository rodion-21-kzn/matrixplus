#include "s21_matrix_oop.h"

int main() {
    S21Matrix s21_test_matrix(0,0);
    return 0;
}

// OPERATIONS

bool S21Matrix::EqMatrix(const S21Matrix &other) {
    bool result = true;

    return false;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {

}

void S21Matrix::SubMatrix(const S21Matrix &other) {

}

// КОНСТРУКТОРЫ

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {} // дефолт конструктор

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) { // не дефолт конструктор ПРОВЕРИТЬ
    if (rows_ > 0 && cols_ > 0) {
        AllocatingMemory();
    } else {
        rows_ = 0;
        cols_ = 0;
        matrix_ = nullptr;
    }
}

S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
    if (rows_ > 0 && cols_ > 0) {
        AllocatingMemory();
        for (int i = 0; i < rows_; ++i) {
            for (int k = 0; k < cols_; ++k) {
                matrix_[i][k] = other.matrix_[i][k];
            }
        }
    }
}

S21Matrix::S21Matrix(S21Matrix &&other) : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    if (matrix_ != nullptr) {
        for (int i = 0; i < rows_; ++i) {
            delete [] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
        rows_ = 0;
        cols_ = 0;
    }
}

// SUPPORT

void S21Matrix::InputData() {
    for (int i = 0; i < rows_; ++i) {
        for (int k = 0; k < cols_; ++k) {
            std::cin >> matrix_[i][k];
        }
    }
}

void S21Matrix::PrintData() {
    for (int i = 0; i < rows_; ++i) {
        for (int k = 0; k < cols_; ++k) {
            std::cout << matrix_[i][k] << " ";
        }
    }
    std::cout << "\n";
}


void S21Matrix::AllocatingMemory() {
    matrix_ = new double* [rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_];
    }
}