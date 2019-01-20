#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "matrix.hpp"

int main () {
    using namespace maala;
    
    try {
        // Matrix A(3,3,0);
        Matrix A = zeros(3,3);
        std::cout << "A =" << std::endl;
        printMatrix(A);

        std::cout << std::endl;

        maala::Matrix B = maala::matrixFromString("0,1,2;3,4,5;6,7,8;");
        std::cout << "B =" << std::endl;
        printMatrix(B);

        std::cout << std::endl;

    std::cout << "B.T() =" << std::endl;
        printMatrix(B.T());
    }
    catch (const char* msg) {
        std::cerr << msg << '\n';
    }

    return 0;
}