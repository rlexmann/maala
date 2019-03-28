#ifndef MAALA_SOLVER_HPP
#define MAALA_SOLVER_HPP

#include <matrix.hpp>

namespace maala {

Matrix
gaussSolver(const Matrix& A, const Matrix& B);

}

#endif // ifndef MAALA_SOLVER_HPP