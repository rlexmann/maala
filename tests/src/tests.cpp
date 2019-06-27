#include <iostream>
#include <string>

#include <config.hpp>
#include <elimination.hpp>
#include <matrix.hpp>
#include <solver.hpp>

#include <tests.hpp>

using namespace maala;

bool
gaussEliminationTest(const Matrix& A, const Matrix& B, const Matrix& Xref) {
   Matrix C = Matrix::concat(A, B);
   Matrix X = gaussSolver(A, B);
   return (A * X == B); // && X == Xref);
}

bool
gaussJordanEliminationTest(const Matrix& A,
                           const Matrix& B,
                           const Matrix& Xref) {
   Matrix C = Matrix::concat(A, B);
   Matrix X = gaussJordanSolver(A, B);
   (A * X).round(1e-9).print();
   return ((A * X).round(1e-12) == B); // && X == Xref);
}

void
testSuite1() {
   try
   {
      std::vector<Matrix> A, b, X;
      // Tutorial 1.2
      A.push_back(Matrix("2,1,1;6,2,1;-2,2,1;"));
      b.push_back(Matrix("1;-1;7;"));
      X.push_back(Matrix("-1;2;1;"));
      // Example 1.2.1
      A.push_back(Matrix("0,1,-1;-2,4,-1;-2,5,-4"));
      b.push_back(Matrix("3;1;-2"));
      X.push_back(Matrix("10;6;3;"));
      // Exercise 1.2.1
      A.push_back(Matrix("1,1,1;1,2,2;1,2,3"));
      b.push_back(Matrix("1;1;1"));
      X.push_back(Matrix("1;0;0"));
      // Exercise 1.2.2
      A.push_back(Matrix("2,-1,0;-1,2,-1;0,-1,1"));
      b.push_back(Matrix("0;0;1"));
      X.push_back(Matrix("1;2;3"));
      // Exercise 1.2.3
      A.push_back(Matrix("0,4,-3;-1,7,-5;-1,8,-6"));
      b.push_back(Matrix("3;4;5"));
      X.push_back(Matrix("1;0;-1"));
      // Exercise 1.2.4
      A.push_back(Matrix(" 1, 1, 1, 1; \
                         1, 1, 3, 3; \
                         1, 1, 2, 3; \
                         1, 3, 3, 3; "));
      b.push_back(Matrix("1;3;3;4"));
      X.push_back(Matrix("-0.5;0.5;0;1"));
      // Exercise 1.2.5
      A.push_back(Matrix(" 4,-8, 5; \
                         4,-7, 4; \
                         3,-4, 2; "));
      b.push_back(Matrix::identity(3));
      X.push_back(Matrix("2,-4,3;4,-7,4;5,-8,4"));
      // Exercise 1.2.8
      // A.push_back(Matrix(" -1, 3,-2; \
      //                   -1, 4,-3; \
      //                   -1, 5,-4; "));
      // b.push_back(Matrix("1;0;0;"));
      // X.push_back(Matrix("nan;nan;nan"));
      // Exercise 1.2.9
      A.push_back(Matrix(" -1, 3,-2; \
                         -1, 4,-3; \
                         -1, 5,-4; "));
      b.push_back(Matrix("4;5;6;"));
      X.push_back(Matrix("0;2;1"));
      // Exercise 1.2.10
      double2D points = { { 1, 1 }, { 2, 2 }, { 3, 0 } };
      Matrix coeff(3, 3), rhs(3, 1);
      for (size_t i = 0; i < points.size(); ++i)
      {
         for (size_t j = 0; j < 3; ++j)
         {
            coeff(i, j) = std::pow(points[i][0], j);
         }
         rhs(i, 0) = points[i][1];
      }
      A.push_back(coeff);
      b.push_back(rhs);
      X.push_back(Matrix("-3;5.5;-1.5"));

      for (size_t i = 0; i < A.size(); ++i)
      {
         std::cout << (gaussEliminationTest(A[i], b[i], X[i]) ? "passed"
                                                              : "failed")
                   << std::endl;
      }
      // Exercise 1.2.11
      A.push_back(Matrix(" .4, .0, .0, .2; \
                         .0, .4, .3, .2; \
                         .0, .3, .4, .2; \
                         .6, .3, .3, .4; "));
      b.push_back(Matrix("12;25;26;37"));
      X.push_back(Matrix("10;20;30;40"));
      // a)
      gaussEliminationTest(*A.rbegin(), *b.rbegin(), *X.rbegin());
      // b)
      //((*A.rbegin()) * Matrix("20;20;20;40;")).print();
   }
   catch (const std::string msg)
   { std::cerr << msg << '\n'; }
}

void
testSuite2() {
   try
   {
      std::vector<Matrix> A, b, X;
      // Tutorial 1.3
      A.push_back(Matrix(" 2, 2, 6; \
                           2, 1, 7; \
                          -2,-6,-7; "));
      b.push_back(Matrix(" 4; \
                           6; \
                          -1; "));
      X.push_back(Matrix("0;-1;1"));
      // Exercise 1.3.1
      A.push_back(Matrix(" 0, 4,-3; \
                          -1, 7,-5; \
                          -1, 8,-6; "));
      b.push_back(Matrix(" 3; \
                           4; \
                           5; "));
      X.push_back(Matrix("1;0;-1"));
      // Exercise 1.3.2
      A.push_back(Matrix(" 1, 1, 1, 1; \
                           1, 2, 2, 2; \
                           1, 2, 3, 3; \
                           1, 2, 3, 4; "));
      b.push_back(Matrix(" 1; \
                           0; \
                           0; \
                           0; "));
      X.push_back(Matrix("2,-1,0,0").T());
      // Exercise 1.3.3
      A.push_back(Matrix(" 2,-1, 0; \
                          -1, 2,-1; \
                           0,-1, 1; "));
      b.push_back(Matrix::identity(3));
      X.push_back(Matrix("1,1,1;1,2,2;1,2,3;"));

      for (size_t i = 0; i < A.size(); ++i)
      {
         std::cout << (gaussJordanEliminationTest(A[i], b[i], X[i]) ? "passed"
                                                                    : "failed")
                   << std::endl;
      }
   }
   catch (const std::string msg)
   { std::cerr << msg << '\n'; }
}