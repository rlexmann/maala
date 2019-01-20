#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "matrix.hpp"

namespace maala {

    double Matrix::get(int i, int j) {
        if (!transposed) {
            return mat[i][j];
        } else {
            return mat[j][i];
        }
    }

    double& Matrix::operator()(int i, int j) {
        return mat[i][j];
    };

    Matrix zeros (int m, int n) {
        if (0 >= m || 0 >= n) {
            throw "Non-positive matrix dimension(s)!";
        }

        Matrix A;

        for (int i = 0; i<m; i++) {
            std::vector<double> row;
            for (int j = 0; j<n; j++) {
                row.push_back(0);
            }
            A.mat.push_back(row);
        }
        A.m = A.mat.size();
        A.n = A.mat[0].size();

        return A;
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

        std::vector<std::string> rows = splitString(s,';');
        for (std::string row: rows) {
            std::vector<std::string> elements = splitString(row,',');
            std::vector<double> A_row;
            for (std::string element: elements) {
                A_row.push_back(std::stod(element));
            }
            A.mat.push_back(A_row);
        }
        A.m = A.mat.size();
        A.n = A.mat[0].size();

        return A;
    }

    int printMatrix (Matrix& A) {
        int m = A.m;
        int n = A.n;
        for (int i = 0; i<m; i++) {
            for (int j = 0; j<n; j++) {
                if (j != 0) {
                    std::cout << '\t';
                }
                std::cout << A.get(i,j);
            }
            std::cout << '\n';
        }

        return 0;
    }
}