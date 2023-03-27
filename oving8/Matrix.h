#include <iostream>
#include <assert.h>
#include <utility>

class Matrix{
    private:
        int rows;
        int cols;
        double** matrix;

        double& at(int row, int col);
        double at(int row, int col) const;

    public:
        Matrix(int rows, int cols);
        explicit Matrix(int rows);
        Matrix(const Matrix& rhs);

        ~Matrix();

        double get(int row, int col) const;
        void set(int row, int col, double value);

        int getRows() const {return rows;};
        int getCols() const {return cols;}

        double* operator[](int);

        Matrix& operator=(Matrix);
        Matrix& operator+=(const Matrix&);
        Matrix operator+(const Matrix&) const;

        Matrix operator-() const;
        Matrix operator-(const Matrix&) const;
        Matrix& operator-=(const Matrix&);

        Matrix operator*(double) const;
        Matrix& operator*=(double);
        
};

std::ostream& operator<<(std::ostream&, const Matrix&);

Matrix operator*(double, const Matrix&);