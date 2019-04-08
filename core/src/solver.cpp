#include <algorithm>
#include <common.hpp>
#include <elimination.hpp>
#include <matrix.hpp>

namespace maala {

Matrix
backSubstitution(const Matrix& A, const size_t rhsCols) {
   size_t m = A.dim()[0], n = A.dim()[1] - rhsCols;
   Matrix X(n, rhsCols, 0);
   for (size_t i = m - 1; i + 1 > 0; --i)
   {
      for (size_t k = 0; k < rhsCols; ++k)
      {
         double rhs = A(i, n + k);
         for (size_t j = n - 1; j > i; --j)
         {
            rhs -= A(i, j) * X(j, k);
         }
         if (isEqual<double>(A(i, i), 0.0))
         {
            if (isEqual<double>(rhs, 0.0))
            {
               X(i, k) = 1.0;
               continue;
            } else
            { return Matrix(n, rhsCols, std::nan("")); }
         }
         X(i, k) = rhs / A(i, i);
      }
   }
   return X;
}

Matrix
gaussSolver(const Matrix& A, const Matrix& B) {
   Matrix C = Matrix::concat(A, B);
   gauss(C);
   return backSubstitution(C, B.dim()[1]);
}

Matrix
gaussJordanSolver(const Matrix& A, const Matrix& B) {
   Matrix C = Matrix::concat(A, B);
   gaussJordan(C);
   std::vector<size_t> solCols(B.dim()[1], A.dim()[1]);
   for (size_t j = 1; j < solCols.size(); ++j)
   {
      solCols[j] += j;
   }
   return C.getSlice(Matrix::SliceDesc(std::vector<size_t>(), solCols));
}

} // namespace maala