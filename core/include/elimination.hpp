#ifndef MAALA_ELIMINATION_HPP
#define MAALA_ELIMINATION_HPP

#include <matrix.hpp>

namespace maala {

Matrix&
gauss(Matrix&);

Matrix&
gaussJordan(Matrix&);

} // namespace maala

#endif // ifndef MAALA_ELIMINATION_HPP