#include <iostream>
#include <vector>

class Matrix {
    public:
        int m;
        int n;
        std::vector<std::vector<double>> mat;
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

int printMatrix (Matrix* A) {
    bool startOfRow;

    for (std::vector<double> row: A->mat) {
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

int printMatrix2 (Matrix* A) {
    int m = A->m;
    int n = A->n;
    for (int i = 0; i<m; i++) {
        for (int j = 0; j<n; j++) {
            if (j != 0) {
                std::cout << '\t';
            }
            std::cout << A->mat[i][j];
        }
        std::cout << '\n';
    }

    return 0;
}

int main () {
    try {
        Matrix A = zeros(3,3);
        printMatrix2(&A);
    }
    catch (const char* msg) {
        std::cerr << msg << '\n';
    }

    return 0;
}