#include "s21_matrix_oop.h"


int main() {
    S21Matrix s21_test_matrix(1,1);
    s21_test_matrix.InputData();
    S21Matrix result = s21_test_matrix.InverseMatrix();
    result.PrintData();
    return 0;
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

// GET and SET

int S21Matrix::GetRows() const {
    return rows_;
}

int S21Matrix::GetCols() const {
    return cols_;
}

void S21Matrix::SetCols(int cols) {
    if (cols <= 0) throw std::logic_error("Wrong argument");
    if (cols_ != cols) {
        S21Matrix temp_matrix(rows_, cols);
        int min_cols = std::min(cols_, cols);
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < min_cols; ++j) {
                temp_matrix.matrix_[i][j] = matrix_[i][j];
            }
        }
        *this = std::move(temp_matrix);
    }
}

void S21Matrix::SetRows(int rows) {
    if (rows <= 0) throw std::logic_error("Wrong argument");
    if (rows_ != rows) {
        S21Matrix temp_matrix(rows, cols_);
        int min_rows = std::min(rows, rows_);
        for (int i = 0; i < min_rows; ++i) {
            for (int j = 0; j < cols_; ++j) {
                temp_matrix.matrix_[i][j] = matrix_[i][j];
            }
        }
        *this = std::move(temp_matrix);
    }
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
    if (cols_ != other.rows_) {
        throw std::logic_error("These sizes of matrix are incorrect");
    } else {
        S21Matrix temp(rows_, other.cols_);
        for (int i = 0; i < temp.rows_; ++i) {
            for (int j = 0; j < temp.cols_; ++j) {
                for (int k = 0; k < other.rows_; ++k) {
                    temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
                }
            }
        }
        *this = std::move(temp);
    }
}

S21Matrix S21Matrix::Transpose() {
    S21Matrix result_matrix(cols_, rows_);
    for (int i = 0; i < result_matrix.rows_; ++i) {
        for (int j = 0; j < result_matrix.cols_; ++j) {
            result_matrix.matrix_[i][j] = matrix_[j][i];
        }
    }
    return result_matrix;
}

S21Matrix S21Matrix::CalcComplements() {
    if (rows_ != cols_) {
        throw std::logic_error("Matrix is not square");
    }
    S21Matrix result_matrix(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            double determinant = 0;
            double complement = 0;
            S21Matrix minor = this->FillMinor(i, j);
            determinant = minor.Determinant();
            complement = determinant * pow(-1, i+j);
            result_matrix.matrix_[i][j] = complement;
        }
    }
    return result_matrix;
}

double S21Matrix::Determinant() {
    double result = 0;
    if (rows_ != cols_) {
        throw std::logic_error("Matrix is not square");
    } else if (rows_ == 1) {
        result = matrix_[0][0];
    } else if (rows_ == 2) {
        result = matrix_[0][0]*matrix_[1][1] - matrix_[0][1]*matrix_[1][0];
    } else {
        for (int i = 0; i < cols_; ++i) {
            double determinant = 0;
            S21Matrix minor = this->FillMinor(0, i);
            determinant = minor.Determinant();
            result = result + (matrix_[0][i] * determinant * pow(-1, i));
        }
    }
    return result;
}

S21Matrix S21Matrix::InverseMatrix() {
    double determinant = 0;
    if (rows_ != cols_) {
        throw std::logic_error("Matrix is not square");
    }
    determinant = this->Determinant();
    if (determinant == 0) {
        throw std::logic_error("Determinant is zero");
    }
    S21Matrix result_matrix(*this);
    if (rows_ == 1) {
        result_matrix.matrix_[0][0] = 1 / determinant;
    } else {
        result_matrix = result_matrix.CalcComplements();
        result_matrix = result_matrix.Transpose();
        result_matrix.MulNumber(1/determinant);
    }
    return result_matrix;
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

S21Matrix S21Matrix::FillMinor(int delete_row, int delete_column) {
    int minor_row = 0;
    int minor_column = 0;
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (i != delete_row && j != delete_column) {
                minor.matrix_[minor_row][minor_column] = matrix_[i][j];
                if (minor_column + 1 >= minor.cols_) {
                    ++minor_row;
                    minor_column = 0;
                } else {
                    ++minor_column;
                }
            }
        }
    }
    return minor;
}

//S21Matrix S21Matrix::InverseMatrix() {
//    double determinant = 0;
//    if (rows_ != cols_) {
//        throw std::logic_error("Matrix is not square");
//    }
//    determinant = this->Determinant();
//    if (determinant == 0) {
//        throw std::logic_error("Determinant is zero");
//    }
//    S21Matrix result_matrix(*this);
//    if (rows_ == 1) {
//        result_matrix.matrix_[0][0] = 1 / determinant;
//    } else {
//        S21Matrix complements;
//        S21Matrix transpose;
//        complements = this->CalcComplements();
//        transpose = complements.Transpose();
//        transpose.MulNumber(1/determinant);
//        result_matrix = std::move(transpose);
//    }
//    return result_matrix;
//}