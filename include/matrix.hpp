#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace maala {

    class Matrix
    {
    public:
        Matrix();
        Matrix(int m, int n, double val);

        double get(int i, int j);
        double& operator()(int i, int j);
        std::vector<int>& dim() { return m_dim; }
        std::vector<double>& mat() { return m_mat; }
        int reshape(int m, int n);
        Matrix& T();
    private:
        std::vector<int> m_dim;
        std::vector<double> m_mat;
        bool m_transposed {false};
    };

    Matrix zeros (int m, int n);
    std::vector<std::string> splitString(const std::string& s, char delimiter);
    Matrix matrixFromString(const std::string& s);
    int printMatrix (Matrix& A);
}