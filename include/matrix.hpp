#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace maala {

    class Matrix {
    public:
        int m;
        int n;
        std::vector<std::vector<double>> mat;

        double get(int i, int j);
        double& operator()(int i, int j);

    private:
        bool transposed {false};
    };

    Matrix zeros (int m, int n);
    std::vector<std::string> splitString(const std::string& s, char delimiter);
    Matrix matrixFromString(const std::string& s);
    int printMatrix (Matrix& A);
}