#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "matrix.hpp"

namespace maala {

    Matrix::Matrix() {
        m_dim = std::vector<int> {0,0};
        m_mat = std::vector<double> {};
    }

    Matrix::Matrix(int m, int n, double val) {
        m_dim = std::vector<int> {m,n};
        m_mat = std::vector<double>(m*n,val);
    }

    double Matrix::get(int i, int j) {
        if (!m_transposed) {
            return m_mat[i*m_dim[0] + j];
        } else {
            return m_mat[i + j*m_dim[1]];
        }
    }

    double& Matrix::operator()(int i, int j) {
        if (!m_transposed) {
            return m_mat[i*m_dim[0] + j];
        } else {
            return m_mat[i + j*m_dim[1]];
        }
    };

    int Matrix::reshape(int m, int n) {
        m_dim = std::vector<int> {m,n};
        m_mat.resize(m*n);
        return 0;
    }

    Matrix& Matrix::T() {
        m_transposed = !m_transposed;
        return *this;
    }

    Matrix zeros (int m, int n) {
        if (0 >= m || 0 >= n) {
            throw "Non-positive matrix dimension(s)!";
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
        int m,n {-1};

        std::vector<std::string> rows = splitString(s,';');
        m = rows.size();
        // for (std::string row: rows) {
        for (int i = 0; i < m; i++) {
            std::string row = rows[i];
            std::vector<std::string> elements = splitString(row,',');
            if (n == -1) {
                n = elements.size();
                A.reshape(m,n);
            }
            // for (std::string element: elements) {
            for (int j = 0; j < n; j++) {
                double element = std::stod(elements[j]);
                // A_row.push_back(std::stod(element));
                A(i,j) = element;
            }
            // A.mat.push_back(A_row);
        }
        // A.m = A.mat.size();
        // A.n = A.mat[0].size();

        return A;
    }

    int printMatrix (Matrix& A) {
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