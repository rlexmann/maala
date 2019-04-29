#include <algorithm>
#include <array>
#include <common.hpp>
#include <elimination.hpp>
#include <matrix.hpp>
#include <solver.hpp>
#include <twoPointBoundary.hpp>

namespace maala {

Matrix
twoPointBoundarySecondDegreeSolver(const FuncT* a,
                                   const FuncT* b,
                                   const FuncT* c,
                                   const FuncT* rhs,
                                   const double t0,
                                   const double y0,
                                   const double t1,
                                   const double y1,
                                   const size_t n) {
   const double h = (t1 - t0) / (n + 1);
   Matrix A(n + 2, n + 2);
   Matrix B(n + 2, 1);

   A(0, 0) = 1;
   B(0, 0) = y0;

   for (size_t i = 1; i <= n; ++i)
   {
      const double t = i * h;
      A(i, i - 1) = (2 * (*a)(t)) + (-h * (*b)(t));
      A(i, i) = (-4 * (*a)(t)) + (2 * h * h * (*c)(t));
      A(i, i + 1) = (2 * (*a)(t)) + (h * (*b)(t));
      B(i, 0) = (2 * h * h * (*rhs)(t));
   }

   A(n + 1, n + 1) = 1;
   B(n + 1, 0) = y1;

   A.concat(B).print();

   return gaussSolver(A, B);
}

} // namespace maala