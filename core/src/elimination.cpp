#include <algorithm>
#include <common.hpp>
#include <matrix.hpp>

namespace maala {

Matrix&
gauss(Matrix& A)
{
  size_t i, pi = 0, pj = 0;
  auto dim = A.dim();
  size_t nRows = dim[0], nCols = dim[1];
  size_t maxRank = std::min(nRows, nCols);

  while (nRows > pi && nCols > pj) {
    for (i = pi; i < nRows; ++i) { // search for non-zero pivot
      if (0.0 != A(i, pj))
        break;
    }
    if (nRows == i) { // non-zero pivot not found
      ++pj;
      continue;
    } else {
      A.swapRows(i, pi);
    }

    for (i = pi + 1; i < nRows; ++i) { // eliminate positions below the pivot
      if (0.0 == A(i, pj))
        continue; // position already clear

      double c = -A(i, pj) / A(pi, pj);
      A.addMultipliedRow(c, pi, i);
      A(i, pj) = 0.0; // ensure that the position below pivot is really cleared
    }
    ++pi;
    ++pj;
  }
  return A;
}

Matrix&
gaussJordan(Matrix& A)
{
   size_t i, pi = 0, pj = 0;
   auto dim = A.dim();
   size_t nRows = dim[0], nCols = dim[1];
   size_t maxRank = std::min(nRows, nCols);

   while (nRows > pi && nCols > pj) {
      for (i = pi; i < nRows; ++i) { // search for non-zero pivot
         if (0.0 != A(i, pj))
            break;
      }
      if (nRows == i) { // non-zero pivot not found
         ++pj;
         continue;
      }
      else {
         A.swapRows(i, pi);
      }

      for (i = 0; i < nRows; ++i) { // eliminate positions both above and below the pivot
         if (i == pi) {
            A.multiplyRow(1 / A(pi, pj), i);
            continue;
         }
         if (0.0 == A(i, pj))
            continue; // position already clear

         double c = -A(i, pj) / A(pi, pj);
         A.addMultipliedRow(c, pi, i);
         A(i, pj) = 0.0; // ensure that the eliminated position is really cleared
      }
      ++pi;
      ++pj;
   }
   return A;
}

}