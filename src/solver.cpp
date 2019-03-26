#include <algorithm>
#include <common.hpp>
#include <matrix.hpp>
#include <elimination.hpp>

namespace maala {

Matrix backSubstitution(const Matrix& A, const size_t solutionCols) {
   size_t m = A.dim()[0], n = A.dim()[1] - solutionCols;
   Matrix X(n, solutionCols, 0);
   for (size_t i = m - 1; i + 1 > 0; --i) {
      for (size_t j = 0; j < solutionCols; ++j) {
         double sumSolved = 0.0;
         for (size_t k = n - 1; k > i; --k) {
            sumSolved += A(i, k)*X(k, j);
         }
         X(i, j) = (A(i, m + j) - sumSolved) / A(i, i);
      }
   }
   return X;
}

Matrix gaussSolver(const Matrix& A, const Matrix& B) {
   size_t am = A.dim()[0], an = A.dim()[1];
   size_t bm = B.dim()[0], bn = B.dim()[1];
   Matrix C = Matrix::concat(A, B);
   gauss(C);
   return backSubstitution(C, bn);
}

}