#include<algorithm>
#include <common.hpp>
#include <matrix.hpp>

namespace maala {

   Matrix& gauss(Matrix& A) {
      auto dim = A.dim();
      size_t maxRank = std::min(dim[0],dim[1]);
      for (size_t n = 0; n < maxRank; ++n) {
         size_t i;
         for (i = n; i < dim[0]; ++i) {
            if (0. != A(i, n)) break;
         }
         if (dim[0] == i)
            return A;
         A.swapRows(n, i);
         for (i = n + 1; i < dim[0]; ++i) {
            double c = A(i, n) / A(n, n);
            for (size_t j = n; j < dim[1]; ++j) {
               if (j == n)
                  A(i, j) = 0;
               else
                  A(i, j) -= A(n, j)*c;
            }
         }
      }
      return A;
   }

}