#include <iostream>
#include <string>

#include <config.hpp>
#include <elimination.hpp>
#include <matrix.hpp>
#include <solver.hpp>

int
main()
{
  using namespace maala;

  try {
    Matrix A({ { 2, 1, 1 }, { 6, 2, 1 }, { -2, 2, 1 } });
    Matrix B("1;-1;7");
    Matrix C = Matrix::concat(A, B);
    std::cout << "C =" << std::endl;
    C.print();
    std::cout << std::endl;

    std::cout << "X = gaussSolver(A,B) =" << std::endl;
    Matrix X = gaussSolver(A, B);
    X.print();
    std::cout << std::endl;

    std::cout << "A*X =" << std::endl;
    std::cout << A * X;
    std::cout << std::endl;
  } catch (const std::string msg) {
    std::cerr << msg << '\n';
  }

#ifdef WIN32
  std::cout << std::endl << "Press Return to exit..." << std::endl;
  std::string input;
  std::getline(std::cin, input);
#endif

  return 0;
}
