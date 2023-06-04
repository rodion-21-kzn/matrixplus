#include "s21_matrix_oop.h"


int main() {
    S21Matrix s21_test_matrix(0,0);
    return 0;
}

// OPERATIONS

bool S21Matrix::EqMatrix(const S21Matrix &other) {
    bool result = true;
    if ((rows_ != other.rows_) || (cols_ != other.cols_)) {
        result = false;
    } else {
        for (int i = 0; i < rows_; ++i) {
            for (int k = 0; k < cols_; ++k) {
                if (fabs(matrix_[i][k] - other.matrix_[i][k]) > FLT_EPSILON) {
                    result = false;
                }
            }
        }
    }
    return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::logic_error("Different sizes of matrix");
    } else {
        for (int i = 0; i < rows_; ++i) {
            for (int k = 0; k < cols_; ++k) {
               matrix_[i][k] += other.matrix_[i][k];
               if (std::isnan(matrix_[i][k]) || std::isinf(matrix_[i][k])) throw std::overflow_error("overflow of double");
            }
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::logic_error("Different sizes of matrix");
    } else {
        for (int i = 0; i < rows_; ++i) {
            for (int k = 0; k < cols_; ++k) {
                matrix_[i][k] -= other.matrix_[i][k];
                if (std::isnan(matrix_[i][k]) || std::isinf(matrix_[i][k])) throw std::overflow_error("overflow of double");
            }
        }
    }
}


void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; ++i) {
        for (int k = 0; k < cols_; ++k) {
            matrix_[i][k] *= num;
            if (std::isnan(matrix_[i][k]) || std::isinf(matrix_[i][k])) throw std::overflow_error("overflow of double");
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {

}

S21Matrix S21Matrix::Transpose() {
    return S21Matrix();
}

S21Matrix S21Matrix::CalcComplements() {
    return S21Matrix();
}

double S21Matrix::Determinant() {
    return 0;
}

S21Matrix S21Matrix::InverseMatrix() {
    return S21Matrix();
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

// GET and SET

int S21Matrix::GetRows() const {
    return rows_;
}

int S21Matrix::GetCols() const {
    return cols_;
}

void S21Matrix::SetCols(int cols) {

}

void S21Matrix::SetRows(int rows) {

}

void S21Matrix::SetSize(int rows, int cols) {
//    if (rows_ == rows && cols_ == cols) {
//        return;
//    }
//
//    S21Matrix new_matrix(rows, cols);
//    for (int i = 0; i < new_matrix.rows_; ++i) {
//        for (int k = 0; k < new_matrix.cols_; ++k) {
//            if (i >= rows_ || k >= cols_) {
//                new_matrix.matrix_[i][k] = 0;
//            } else {
//                new_matrix.matrix_[i][k] = matrix_[i][k];
//            }
//        }
//    }

}

