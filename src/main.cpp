#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "matrix.hpp"

int main () {
    using namespace maala;
    
    try {
        // Matrix A = zeros(3,3);
        // printMatrix(A);
        maala::Matrix B = maala::matrixFromString("0,1,2;3,4,5;6,7,8;");
        printMatrix(B);
    }
    catch (const char* msg) {
        std::cerr << msg << '\n';
    }

    return 0;
}