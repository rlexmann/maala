#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Matrix {
public:
    int m;
    int n;
    std::vector<std::vector<double>> mat;

    double get(int i, int j) {
        if (!transposed) {
            return mat[i][j];
        } else {
            return mat[j][i];
        }
    }

private:
    bool transposed {false};
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

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

Matrix matrixFromString(const std::string& s) {
    Matrix A;

    std::vector<std::string> rows = split(s,';');
    for (std::string row: rows) {
        std::vector<std::string> elements = split(row,',');
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
    bool startOfRow;

    for (std::vector<double> row: A.mat) {
        startOfRow = true;
        for (double a: row) {
            if (startOfRow) {
                startOfRow = false;
            } else {
                std::cout << '\t';
            }
            std::cout << a;
        }
        std::cout << '\n';
    }

    return 0;
}

int printMatrix2 (Matrix& A) {
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

int main () {
    try {
        Matrix A = zeros(3,3);
        printMatrix(A);
        Matrix B = matrixFromString("0,1,2;3,4,5;6,7,8;");
        printMatrix2(B);
    }
    catch (const char* msg) {
        std::cerr << msg << '\n';
    }

    return 0;
}