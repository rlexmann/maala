#include <iostream>
#include <string>

#include <matrix.hpp>
#include <elimination.hpp>

int main () {
   using namespace maala;
   
   try {
      Matrix A = zeros(3,3);
      std::cout << "A =" << std::endl;
      printMatrix(A);
      std::cout << std::endl;

      maala::Matrix B = maala::matrixFromString("0,1,2;3,4,5;6,7,8;9,10,11;");
      std::cout << "B =" << std::endl;
      std::cout << B;
      std::cout << std::endl;

      std::cout << "B.T() =" << std::endl;
      std::cout << B.T();
      std::cout << std::endl;

      Matrix C({ {1,2},{3,4} });
      std::cout << "C =" << std::endl;
      std::cout << C;
      std::cout << std::endl;

      std::cout << "B.swapRows(0,2) =" << std::endl;
      std::cout << B.swapRows(0,2);
      std::cout << std::endl;

      std::cout << "B.swapCols(1,2) =" << std::endl;
      std::cout << B.swapCols(1, 2);
      std::cout << std::endl;

      std::cout << "gauss(B) =" << std::endl;
      std::cout << gauss(B.T());
      std::cout << std::endl;
   }
   catch (const std::string msg) {
      std::cerr << msg << '\n';
   }

   std::cout << std::endl << "Press Return to exit..." << std::endl;
   std::getline(std::cin, std::string());

   return 0;
}