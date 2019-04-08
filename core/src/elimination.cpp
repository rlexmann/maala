#include <algorithm>
#include <common.hpp>
#include <matrix.hpp>

namespace maala {

inline bool
findNonZeroPivot(Matrix& A, const size_t pi, const size_t pj) {
   const auto nRows = A.dim()[0];
   size_t i;
   for (i = pi; i < nRows; ++i)
   { // search for non-zero pivot
      if (!isEqual<double>(0.0, A(i, pj)))
         break;
   }
   if (nRows == i)
   { // non-zero pivot not found
      return false;
   } else
   {
      A.swapRows(i, pi);
      return true;
   }
}

inline void
eliminatePosition(Matrix& A, const size_t i, const size_t pi, const size_t pj) {
   if (isEqual<double>(0.0, A(i, pj)))
      return; // position already clear

   double c = -A(i, pj) / A(pi, pj);
   A.addMultipliedRow(c, pi, i);
   A(i, pj) = 0.0; // ensure that the eliminated position is really cleared
}

Matrix&
gauss(Matrix& A) {
   size_t i, pi = 0, pj = 0;
   size_t nRows = A.dim()[0], nCols = A.dim()[1];

   while (nRows > pi && nCols > pj)
   {
      bool pivotFound = findNonZeroPivot(A, pi, pj);
      if (!pivotFound)
      { // non-zero pivot not found
         ++pj;
         continue;
      }

      for (i = pi + 1; i < nRows; ++i)
      { // eliminate positions below the pivot
         eliminatePosition(A, i, pi, pj);
      }
      ++pi;
      ++pj;
   }
   return A;
}

Matrix&
gaussJordan(Matrix& A) {
   size_t i, pi = 0, pj = 0;
   size_t nRows = A.dim()[0], nCols = A.dim()[1];

   while (nRows > pi && nCols > pj)
   {
      bool pivotFound = findNonZeroPivot(A, pi, pj);
      if (!pivotFound)
      { // non-zero pivot not found
         ++pj;
         continue;
      }

      for (i = 0; i < nRows; ++i)
      { // eliminate positions both above and below the pivot
         if (i == pi)
            A.multiplyRow(1 / A(pi, pj), i); // make pivot == 1.0
         else
            eliminatePosition(A, i, pi, pj);
      }
      ++pi;
      ++pj;
   }
   return A;
}

} // namespace maala