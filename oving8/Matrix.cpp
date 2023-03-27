#include "Matrix.h"

Matrix::Matrix(int rows, int cols): rows{rows}, cols{cols}{
    assert(rows > 0 && cols > 0);
    matrix = new double*[rows];
    for(int row{0}; row < rows; row++){
        matrix[row] = new double[cols]{0};
    }
}

Matrix::Matrix(int rows): Matrix(rows, rows){
    for(int x{0}; x < rows; x++){
        matrix[x][x] = 1;
    }
}

Matrix::Matrix(const Matrix& rhs){
    rows = rhs.rows;
    cols = rhs.cols;

    matrix = new double*[rows];
    for(int row{0}; row < rows; row++){
        matrix[row] = new double[cols];
        for(int col{0}; col < cols; col++){
            this->at(row, col) = rhs.at(row, col);
        }
    }
}

Matrix::~Matrix(){
    for(int x{0}; x < rows; x++){
        delete[] matrix[x];
        matrix[x] = nullptr;
    }
    delete[] matrix;
    matrix = nullptr;
}

double &Matrix::at(int row, int col){
    assert(row >= 0 && row < rows);
    assert(col >= 0 && col < cols);
    return matrix[row][col];
}

double Matrix::at(int row, int col) const{
    assert(row >= 0 && row < rows);
    assert(col >= 0 && col < cols);
    return matrix[row][col];
}

double Matrix::get(int row, int col) const{
    return at(row, col);
}

void Matrix::set(int row, int col, double value){
    at(row, col) = value;
}

double* Matrix::operator[](int idx){
    assert(idx >= 0 && idx < rows);
    return matrix[idx];
}

std::ostream& operator<<(std::ostream& os, const Matrix& m){
    for(int row{0}; row < m.getRows(); row++){
        for(int col{0}; col < m.getCols(); col++){
            os << m.get(row, col) << " ";
        }
        os << '\n';
    }
    return os;
}

Matrix& Matrix::operator=(Matrix rhs){
    std::swap(this->matrix, rhs.matrix);
    std::swap(this->cols, rhs.cols);
    std::swap(this->rows, rhs.rows);
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& rhs){
    assert(this->rows == rhs.rows && this->cols == rhs.cols);

    for(int row{0}; row < rows; row++){
        for(int col{0}; col < cols; col++){
            this->at(row, col) += rhs.at(row, col);
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& rhs) const{
    assert(this->rows == rhs.rows && this->cols == rhs.cols);

    return Matrix{*this} += rhs;
}

Matrix Matrix::operator-() const{
    Matrix s(this->rows, this->cols);

    for(int row{0}; row < rows; row++){
        for(int col{0}; col < cols; col++){
            s.at(row, col) = -this->at(row, col);
        }
    }
    return s;
}

Matrix Matrix::operator-(const Matrix& rhs) const{
    return Matrix{*this} -= rhs;
}

Matrix& Matrix::operator-=(const Matrix& rhs){
    assert(this->rows == rhs.rows && this->cols == rhs.cols);

    for(int row{0}; row < rows; row++){
        for(int col{0}; col < cols; col++){
            this->at(row, col) -= rhs.at(row, col);
        }
    }
    return *this;
}

Matrix Matrix::operator*(double multi) const{
    Matrix s(this->rows, this->cols);

    for(int row{0}; row < rows; row++){
        for(int col{0}; col < cols; col++){
            s.at(row, col) = this->at(row, col) * multi;
        }
    }
    return s;
}

Matrix operator*(double multi, const Matrix& m){
    Matrix s(m.getRows(), m.getCols());

    for(int row{0}; row < s.getRows(); row++){
        for(int col{0}; col < s.getCols(); col++){
            s.set(row, col, m.get(row, col) * multi);
        }
    }
    return s;

}

Matrix& Matrix::operator*=(double multi){
    for(int row{0}; row < rows; row++){
        for(int col{0}; col < cols; col++){
            this->at(row, col) *= multi;
        }
    }
    return *this;
}