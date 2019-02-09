#include <iostream>
#include <string>
#include <vector>

namespace maala {

    class Matrix
    {
    public:
        Matrix();
        Matrix(const int m, const int n, const double val);

        double get(const int i, const int j) const;
        double& operator()(const int i, const int j);
        friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
        std::vector<int> dim() const { return m_dim; }
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