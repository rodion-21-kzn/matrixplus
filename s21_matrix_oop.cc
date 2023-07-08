#include "s21_matrix_oop.h"


int main() {
    S21Matrix s21_test_matrix(2,2);
    S21Matrix s21_eq_matrix(2,2);
    s21_test_matrix.InputData();
    s21_eq_matrix.InputData();
    if (s21_test_matrix == s21_eq_matrix) {
        std::cout << "true";
    } else {
        std::cout << "false";
    }
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

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows_ > 0 && cols_ > 0) {
        AllocatingMemory();
    } else {
        throw std::logic_error("Wrong arguments");
    }
}

S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
    if (rows_ > 0 && cols_ > 0) {
        AllocatingMemory();
        CopyMatrixData(other);
    } else {
        matrix_ = nullptr;
    }
}

S21Matrix::S21Matrix(S21Matrix &&other) : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
    DeleteMatrix();
}

// SUPPORT

void S21Matrix::CopyMatrixData(const S21Matrix &other) {
    for (int i = 0; i < rows_; ++i) {
        for (int k = 0; k < cols_; ++k) {
            matrix_[i][k] = other.matrix_[i][k];
        }
    }
}

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
        std::cout << "\n";
    }
}


void S21Matrix::AllocatingMemory() {
    matrix_ = new double* [rows_];
    for (int i = 0; i < rows_; ++i) {
        matrix_[i] = new double[cols_];
    }
}

void S21Matrix::DeleteMatrix() {
    if (matrix_ != nullptr) {
        for (int i = 0; i < rows_; ++i) {
            delete[] matrix_[i];
        }
        delete[] matrix_;
        matrix_ = nullptr;
        rows_ = 0;
        cols_ = 0;
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
    if (cols_ != cols) {
        S21Matrix new_matrix(rows_, cols);

    }
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

// OPERATORS

bool S21Matrix::operator==(const S21Matrix& other) {
    return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
    if (this != &other) {
        S21Matrix temp(other);

        std::swap(rows_, temp.rows_);
        std::swap(cols_, temp.cols_);
        std::swap(matrix_, temp.matrix_);

    }
    return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
    if (this != &other) {

        std::swap(rows_, other.rows_);
        std::swap(cols_, other.cols_);
        std::swap(matrix_, other.matrix_);

        other.rows_ = 0;
        other.cols_ = 0;
        other.matrix_ = nullptr;
    }

    return *this;
}

// старая реализация
//S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
//    if (this != &other) {
//        DeleteMatrix();
//        rows_ = other.rows_;
//        cols_ = other.cols_;
//        if (rows_ > 0 && cols_ > 0) {
//            AllocatingMemory();
//            CopyMatrixData(other);
//        } else {
//            matrix_ = nullptr;
//        }
//    }
//    return *this;
//}