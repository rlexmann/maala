#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <common.hpp>
#include <matrix.hpp>

namespace maala {

   std::ostream& operator<<(std::ostream& os, const Matrix& A) {
      std::vector<size_t> dim = A.dim();
      size_t m = dim[0];
      size_t n = dim[1];
      for (size_t i = 0; i<m; i++) {
         for (size_t j = 0; j<n; j++) {
            if (j != 0) {
               os << '\t';
            }
            os << A.valueAt(i,j);
         }
         os << '\n';
      }
      return os;
   }

   void Matrix::reshape(const size_t m, const size_t n) {
      m_dim = {m,n};
      m_mat.resize(m*n);
      for (double1D& row : m_mat) { row.resize(n); }
      m_mat.resize(m);
   }

   Matrix& Matrix::T() {
      m_transposed = !m_transposed;
      std::swap(m_dim[0], m_dim[1]);
      return *this;
   }

   Matrix zeros (const size_t m, const size_t n) {
      if (0 >= m || 0 >= n) {
         THROW_EXCEPTION("Non-positive matrix dimension(s)!");
      }

      return Matrix(m,n,0);
   }

   std::vector<std::string> splitString(const std::string& s, char delimiter) {
      // by Jonathan Boccara
      // https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
      std::vector<std::string> tokens;
      std::string token;
      std::istringstream tokenStream(s);
      while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
      }

      return tokens;
   }

   Matrix matrixFromString(const std::string& s) {
      Matrix A;
      size_t m, n;

      std::vector<std::string> rows = splitString(s,';');
      m = rows.size();
      for (size_t i = 0; i < m; i++) {
         std::string row = rows[i];
         std::vector<std::string> elements = splitString(row,',');
         n = elements.size();
         if (0 == i) {
            A.reshape(m,n);
         }
         else if (A.dim()[1] != n) {
            THROW_EXCEPTION("Inconsistent row lengths.");
         }
         for (size_t j = 0; j < n; j++) {
            double element = std::stod(elements[j]);
            A(i,j) = element;
         }
      }

      return A;
   }

   void printMatrix (const Matrix& A) {
      std::cout << A;

      return;
   }
}