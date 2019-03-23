#include <iostream>
#include <string>

#include <matrix.hpp>
#include <elimination.hpp>
#include <solver.hpp>

int main () {
   using namespace maala;
   
   try {
      Matrix A({ {2,1,1},{6,2,1},{-2,2,1} });
      Matrix B = matrixFromString("1;-1;7");
      Matrix C = concat(A, B);
      std::cout << "C =" << std::endl;
      std::cout << C;
      std::cout << std::endl;

      std::cout << "gaussSolver(A,B) =" << std::endl;
      std::cout << gaussSolver(A,B);
      std::cout << std::endl;
   }
   catch (const std::string msg) {
      std::cerr << msg << '\n';
   }

   std::cout << std::endl << "Press Return to exit..." << std::endl;
   std::getline(std::cin, std::string());

   return 0;
}