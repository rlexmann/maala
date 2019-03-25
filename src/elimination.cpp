#include <algorithm>
#include <common.hpp>
#include <matrix.hpp>

namespace maala {

Matrix& gauss(Matrix& A) {
   size_t i, j, pi = 0, pj = 0;
   auto dim = A.dim();
   double nRows = dim[0], nCols = dim[1];
   size_t maxRank = std::min(nRows, nCols);

   while (nRows > pi && nCols > pj) {
      for (i = pi; i < nRows; ++i) { // search for non-zero pivot
         if (0.0 != A(i, pj)) break;
      }
      if (nRows == i) { // non-zero pivot not found
         ++pj;
         continue;
      }
      else {
         A.swapRows(i, pi);
      }

      for (i = pi + 1; i < nRows; ++i) { // eliminate positions below the pivot
         if (0.0 == A(i, pj)) continue; // position already clear

         double c = A(i, pj) / A(pi, pj);
         A(i, pj) = 0.0;
         for (j = pj + 1; j < nCols; ++j) {
            A(i, j) -= A(pi, j)*c;
         }
      }
      ++pi;
      ++pj;
   }
   return A;
}

}