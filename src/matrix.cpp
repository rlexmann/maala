#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <common.hpp>
#include <matrix.hpp>

namespace maala {

    const double& Matrix::operator()(const int i, const int j) const {
        if (!m_transposed) {
            return m_mat[i*m_dim[0] + j];
        } else {
            return m_mat[i + j*m_dim[1]];
        }
    };

    std::ostream& operator<<(std::ostream& os, const Matrix& A) {
        std::vector<int> dim = A.dim();
        int m = dim[0];
        int n = dim[1];
        for (int i = 0; i<m; i++) {
            for (int j = 0; j<n; j++) {
                if (j != 0) {
                    os << '\t';
                }
                os << A.valueAt(i,j);
            }
            os << '\n';
        }
        return os;
    }

    void Matrix::reshape(const int m, const int n) {
        m_dim = std::vector<int> {m,n};
        m_mat.resize(m*n);
    }

    Matrix& Matrix::T() {
        m_transposed = !m_transposed;
        return *this;
    }

    Matrix zeros (const int m, const int n) {
        if (0 >= m || 0 >= n) {
            THROW_EXCEPTION("Non-positive matrix dimension(s)!");
        }

        return Matrix(m,n,0);
    }

    std::vector<std::string> splitString(const std::string& s, char delimiter) {
       // by Jonathan Boccara
       // https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
       std::vector<std::string> tokens;
       std::string token;
       std::istringstream tokenStream(s);
       while (std::getline(tokenStream, token, delimiter)) {
          tokens.push_back(token);
       }

       return tokens;
    }

    Matrix matrixFromString(const std::string& s) {
        Matrix A;
        int m, n;

        std::vector<std::string> rows = splitString(s,';');
        m = static_cast<int>(rows.size());
        for (int i = 0; i < m; i++) {
            std::string row = rows[i];
            std::vector<std::string> elements = splitString(row,',');
            n = static_cast<int>(elements.size());
            if (0 == i) {
                A.reshape(m,n);
            }
            else if (A.dim()[1] != n) {
                THROW_EXCEPTION("Inconsistent row lengths.");
            }
            for (int j = 0; j < n; j++) {
                double element = std::stod(elements[j]);
                A(i,j) = element;
            }
        }

        return A;
    }

    int printMatrix (const Matrix& A) {
        std::vector<int> dim = A.dim();
        int m = dim[0];
        int n = dim[1];
        for (int i = 0; i<m; i++) {
            for (int j = 0; j<n; j++) {
                if (j != 0) {
                    std::cout << '\t';
                }
                std::cout << A(i,j);
            }
            std::cout << '\n';
        }

        return 0;
    }
}