#include <iostream>
#include <string>

#include <matrix.hpp>

int main () {
    using namespace maala;
    
    try {
        Matrix A = zeros(3,3);
        std::cout << "A =" << std::endl;
        printMatrix(A);

        std::cout << std::endl;

        maala::Matrix B = maala::matrixFromString("0,1,2;3,4,5;6,7,8;");
        std::cout << "B =" << std::endl;
        std::cout << B;

        std::cout << std::endl;

        std::cout << "B.T() =" << std::endl;
        std::cout << B.T();
    }
    catch (const std::string msg) {
        std::cerr << msg << '\n';
    }

    return 0;
}