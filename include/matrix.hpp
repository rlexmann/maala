#ifndef MAALA_MATRIX_HPP
#define MAALA_MATRIX_HPP

#include <iostream>
#include <string>
#include <vector>

namespace maala {

    class Matrix
    {
    public:
        // constructors
        Matrix()
        : m_dim {0,0}, m_mat {}
        {};

        Matrix(const int m, const int n, const double val)
        : m_dim {m,n}, m_mat (m*n,val)
        {};

        // access methods
        const std::vector<int> dim() const { return m_dim; }
        std::vector<double>& mat() { return m_mat; }
        const double& operator()(const int i, const int j) const;
        double& operator()(const int i, const int j) {
            return const_cast<double&>(static_cast<const Matrix&>(*this)(i,j));
        }
        double valueAt(const int i, const int j) const {
            return static_cast<const Matrix&>(*this)(i,j);
        };

        // modifiers
        void reshape(const int m, const int n);
        Matrix& T();

        // print
        friend std::ostream& operator<<(std::ostream& os, const Matrix& A);

    private:
        std::vector<int> m_dim;
        std::vector<double> m_mat;
        bool m_transposed {false};
    };

    Matrix zeros (const int m, const int n);
    Matrix matrixFromString(const std::string& s);
    
    int printMatrix (const Matrix& A);
}

#endif // ifndef MAALA_MATRIX_HPP