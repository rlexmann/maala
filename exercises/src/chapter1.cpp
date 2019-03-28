#include <iostream>
#include <string>

#include <config.hpp>
#include <matrix.hpp>
#include <solver.hpp>

#include <chapters.hpp>

using namespace maala;

void
gaussEliminationExerice(const Matrix& A, const Matrix& B)
{

  Matrix C = Matrix::concat(A, B);
  std::cout << " concat(A,B) =" << std::endl;
  C.print();
  std::cout << std::endl;

  Matrix X = gaussSolver(A, B);
  std::cout << "X = gaussSolver(A,B) =" << std::endl;
  X.print();
  std::cout << std::endl;

  std::cout << "A*X == B" << std::endl;
  std::cout << ((A * X == B) ? "true" : "false") << std::endl;
  std::cout << "~~~~~~~~~~~~~~~~~" << std::endl;
}

void
exChapter1()
{
  try {
    // Tutorial 1.2
    std::vector<Matrix> A, b;
    A.push_back(Matrix("2,1,1;6,2,1;-2,2,1"));
    b.push_back(Matrix("1;-1;7"));
    // Example 1.2.1
    A.push_back(Matrix("0,1,-1;-2,4,-1;-2,5,-4"));
    b.push_back(Matrix("3;1;-2"));
    // Exercise 1.2.1
    A.push_back(Matrix("1,1,1;1,2,2;1,2,3"));
    b.push_back(Matrix("1;1;1"));
    // Exercise 1.2.2
    A.push_back(Matrix("2,-1,0;-1,2,-1;0,-1,1"));
    b.push_back(Matrix("0;0;1"));
    // Exercise 1.2.3
    A.push_back(Matrix("0,4,-3;-1,7,-5;-1,8,-6"));
    b.push_back(Matrix("3;4;5"));
    // Exercise 1.2.4
    A.push_back(Matrix("   1, 1, 1, 1; \
                           1, 1, 3, 3; \
                           1, 1, 2, 3; \
                           1, 3, 3, 3; "));
    b.push_back(Matrix("1;3;3;4"));

    for (size_t i = 0; i < A.size(); ++i) {
      gaussEliminationExerice(A[i], b[i]);
    }

  } catch (const std::string msg) {
    std::cerr << msg << '\n';
  }
}
