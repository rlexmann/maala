#ifndef MAALA_MATRIX_HPP
#define MAALA_MATRIX_HPP

#include <common.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace maala {

class Matrix
{
public:
  // constructors
  Matrix()
    : m_dim{ 0, 0 }
    , m_mat{}
    , m_transposed{ false }
  {}

  Matrix(const size_t m, const size_t n)
    : m_dim{ m, n }
    , m_mat(m, double1D(n, 0))
    , m_transposed{ false }
  {}

  Matrix(const size_t m, const size_t n, const double val)
    : m_dim{ m, n }
    , m_mat(m, double1D(n, val))
    , m_transposed{ false }
  {}

  Matrix(const double2D mat)
    : m_dim{ mat.size(), mat[0].size() }
    , m_mat{ mat }
  {
    for (double1D& row : m_mat) { // verify row consistency
      if (row.size() != m_dim[1]) {
        THROW_EXCEPTION("Inconsistent row lengths.");
      }
    }
  }

  Matrix(const std::string& s);

  // copy constructor
  Matrix(const Matrix& A)
    : m_dim{ A.dim() }
    , m_mat{ A.mat() }
    , m_transposed{ A.transposed() }
  {}

  // copy assignement operator
  Matrix& operator=(const Matrix& A)
  {
    if (this != &A) {
      m_dim = A.m_dim;
      m_mat = A.m_mat;
      m_transposed = A.m_transposed;
    }
    return *this;
  }

  // access methods
  const std::vector<size_t> dim() const { return m_dim; }
  const bool transposed() const { return m_transposed; }
  const double2D& mat() const { return m_mat; }

  const double& operator()(const size_t i, const size_t j) const
  {
    return m_transposed ? m_mat[j][i] : m_mat[i][j];
  }
  double& operator()(const size_t i, const size_t j)
  {
    return UNCONST(Matrix, operator()(i, j), double&);
  }
  double valueAt(const size_t i, const size_t j) const { return (*this)(i, j); }

  // modifiers
  void reshape(const size_t m, const size_t n);
  Matrix& T();
  Matrix& swapRows(const size_t i, const size_t j);
  Matrix& swapCols(const size_t i, const size_t j);

  static Matrix matmul(const Matrix& A, const Matrix& B);
  Matrix operator*(const Matrix& B) const { return matmul(*this, B); }

  static Matrix concat(const Matrix& A, const Matrix& B);
  Matrix concat(const Matrix& B) const { return concat(*this, B); }

  // print
  friend std::ostream& operator<<(std::ostream& os, const Matrix& A);
  void print() const { std::cout << *this; }

  //
  static Matrix zeros(const size_t m, const size_t n);
  static Matrix identity(const size_t n);

private:
  std::vector<size_t> m_dim;
  double2D m_mat;
  bool m_transposed{ false };
};

}

#endif // ifndef MAALA_MATRIX_HPP