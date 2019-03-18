#ifndef MAALA_MATRIX_HPP
#define MAALA_MATRIX_HPP

#include <iostream>
#include <string>
#include <vector>
#include <common.hpp>

namespace maala {
    typedef std::vector<double>              double1D;
    typedef std::vector<std::vector<double>> double2D;

    class Matrix
    {
    public:
        // constructors
        Matrix()
        : m_dim{0,0}, m_mat{}
        {}

        Matrix(const size_t m, const size_t n, const double val)
        : m_dim{m,n}, m_mat(m,double1D(n,val))
        {}

        Matrix(const double2D mat)
        : m_dim{mat.size(),mat[0].size()}, m_mat{mat}
        {
            for (double1D& row : m_mat) { // verify row consistency
                if (row.size() != m_dim[1]) {
                    THROW_EXCEPTION("Inconsistent row lengths.");
                }
            }
        }

        // access methods
        const std::vector<size_t> dim() const { return m_dim; }
        double2D& mat() { return m_mat; }
        const double& operator()(const size_t i, const size_t j) const;
        double& operator()(const size_t i, const size_t j) {
            return const_cast<double&>(static_cast<const Matrix&>(*this)(i,j));
        }
        double valueAt(const size_t i, const size_t j) const {
            return static_cast<const Matrix&>(*this)(i,j);
        }

        // modifiers
        void reshape(const size_t m, const size_t n);
        Matrix& T();

        // print
        friend std::ostream& operator<<(std::ostream& os, const Matrix& A);

    private:
        std::vector<size_t> m_dim;
        double2D m_mat;
        bool m_transposed {false};
    };

    Matrix zeros (const size_t m, const size_t n);
    Matrix matrixFromString(const std::string& s);
    
    void printMatrix (const Matrix& A);
}

#endif // ifndef MAALA_MATRIX_HPP