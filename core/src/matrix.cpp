#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <common.hpp>
#include <matrix.hpp>

namespace maala {

std::vector<std::string>
splitString(const std::string& s, char delimiter) {
   // by Jonathan Boccara
   // https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }

   return tokens;
}

inline bool
isEmptyString(const std::string& s) {
   return std::all_of(s.begin(), s.end(), isspace);
}

Matrix::Matrix(const std::string& s)
  : m_dim{ 0, 0 }
  , m_mat{}
  , m_transposed{ false } {
   size_t m, n;
   std::vector<std::string> rows = splitString(s, ';');
   m = rows.size();
   for (size_t i = 0; i < m; i++)
   {
      std::string row = rows[i];
      std::vector<std::string> elements = splitString(row, ',');
      n = elements.size();
      if (0 == i)
      {
         this->reshape(m, n);
      }
      else if (1 == n && isEmptyString(elements[0]))
      {
         // empty row
         this->reshape(--m, m_dim[1]);
         continue;
      }
      else if (m_dim[1] != n)
      { THROW_EXCEPTION("Inconsistent row lengths."); }
      for (size_t j = 0; j < n; j++)
      {
         double element = std::stod(elements[j]);
         (*this)(i, j) = element;
      }
   }
}

Matrix::SliceDesc
Matrix::sliceDescFromStr(const std::string& s) {
   std::vector<size_t> m_rows, m_cols;
   const auto dimSpecStrings = splitString(s, ';');
   if (dimSpecStrings.size() != 2)
   {
      THROW_EXCEPTION("Invalid slice definition.")
   }

   size_t ind = 0;
   for (const auto& dimSpec : dimSpecStrings)
   {
      // <start (optional)>:<end (optional>
      auto dimLimits = splitString(dimSpec, ':');
      if (dimSpec != dimLimits[0])
      { // ':' delimiter found
         size_t low = isEmptyString(dimLimits[0]) ? 0 : std::stoi(dimLimits[0]);
         size_t high = (dimLimits.size() < 2 || isEmptyString(dimLimits[1]))
                         ? m_dim[ind] - 1
                         : std::stoi(dimLimits[1]);
         for (size_t i = low; i <= high; ++i)
         {
            if (0 == ind)
               m_rows.push_back(i);
            else
               m_cols.push_back(i);
         }
      }
      else
      {
         auto vals = splitString(dimSpec, ',');
         if (vals[0] == dimSpec && isEmptyString(vals[0]))
         {
            THROW_EXCEPTION("Invalid slice definition.")
         }

         for (const auto& val : vals)
         {
            size_t i = std::stoi(val);
            if (0 == ind)
               m_rows.push_back(i);
            else
               m_cols.push_back(i);
         }
      }

      ++ind;
   }
   return Matrix::SliceDesc(m_rows, m_cols);
}

Matrix
Matrix::operator()(const std::string& s) {
   return getSlice(sliceDescFromStr(s));
}

Matrix
Matrix::getSlice(const SliceDesc& sd) {
   bool allRows = sd.m_rows.empty(), allCols = sd.m_cols.empty();
   size_t m = allRows ? m_dim[0] : sd.m_rows.size();
   size_t n = allCols ? m_dim[1] : sd.m_cols.size();
   Matrix slice(m, n);
   for (size_t i = 0; i < m; ++i)
   {
      size_t si = allRows ? i : sd.m_rows[i];
      for (size_t j = 0; j < n; ++j)
      {
         size_t sj = allCols ? j : sd.m_cols[j];
         slice(i, j) = (*this)(si, sj);
      }
   }
   return slice;
}

Matrix
Matrix::getRow(const size_t i) {
   Matrix row(1, m_dim[1]);
   for (size_t j = 0; j < m_dim[1]; ++j)
      row(1, j) = (*this)(i, j);
   return row;
}

Matrix
Matrix::getCol(const size_t j) {
   Matrix col(1, m_dim[0]);
   for (size_t i = 0; i < m_dim[0]; ++i)
      col(1, i) = (*this)(i, j);
   return col.T();
}

void
Matrix::reshape(const size_t m, const size_t n) {
   m_dim = { m, n };
   m_mat.resize(m * n);
   for (double1D& row : m_mat)
      row.resize(n);
   m_mat.resize(m);
}

Matrix&
Matrix::T() {
   m_transposed = !m_transposed;
   std::swap(m_dim[0], m_dim[1]);
   return *this;
}

Matrix&
Matrix::swapRows(const size_t i, const size_t j) {
   if (i >= m_dim[0] || j >= m_dim[1])
   {
      THROW_EXCEPTION("Index greater than matrix dimension.");
   }

   if (m_transposed)
   {
      return (*this).T().swapCols(i, j).T();
   }

   if (i != j)
   {
      std::swap(m_mat[i], m_mat[j]);
   }

   return *this;
}

Matrix&
Matrix::swapCols(const size_t i, const size_t j) {
   if (i >= m_dim[0] || j >= m_dim[1])
   {
      THROW_EXCEPTION("Index greater than matrix dimension.");
   }

   if (m_transposed)
   {
      return (*this).T().swapRows(i, j).T();
   }

   if (i != j)
   {
      for (auto& row : m_mat)
      {
         std::swap(row[i], row[j]);
      }
   }

   return *this;
}

Matrix&
Matrix::multiplyRow(const double c, const size_t i) {
   for (size_t j = 0; j < m_dim[1]; ++j)
   {
      (*this)(i, j) *= c;
   }
   return *this;
}

Matrix&
Matrix::addMultipliedRow(const double c, const size_t i, const size_t j) {
   for (size_t k = 0; k < m_dim[1]; ++k)
   {
      (*this)(j, k) += this->valueAt(i, k) * c;
   }
   return *this;
}

Matrix
Matrix::matmul(const Matrix& A, const Matrix& B) {
   size_t am = A.dim()[0], an = A.dim()[1];
   size_t bm = B.dim()[0], bn = B.dim()[1];
   if (an != bm)
   {
      THROW_EXCEPTION("Incompatible matrices.");
   }
   size_t m = am, n = bn, t = an;
   Matrix C(m, n);
   for (size_t i = 0; i < m; ++i)
   {
      for (size_t j = 0; j < n; ++j)
      {
         for (size_t k = 0; k < t; ++k)
         {
            C(i, j) += A(i, k) * B(k, j);
         }
      }
   }
   return C;
}

Matrix
Matrix::concat(const Matrix& A, const Matrix& B) {
   size_t am = A.dim()[0], an = A.dim()[1];
   size_t bm = B.dim()[0], bn = B.dim()[1];
   if (am != bm)
   {
      THROW_EXCEPTION("Incompatible matrices.");
   }
   size_t m = am, n = an + bn;
   Matrix C(A);
   C.reshape(m, n);
   for (size_t i = 0; i < bm; ++i)
   {
      for (size_t j = 0; j < bn; ++j)
      {
         C(i, am + j) = B(i, j);
      }
   }
   return C;
}

bool
Matrix::operator==(const Matrix& B) {
   if (m_dim != B.dim())
   {
      return false;
   }

   for (size_t i = 0; i < m_dim[0]; ++i)
   {
      for (size_t j = 0; j < m_dim[1]; ++j)
      {
         if (!isEqual<double>((*this)(i, j), B(i, j)))
         {
            std::cout << ((*this)(i, j) == B(i, j)) << std::endl;
            return false;
         }
      }
   }
   return true;
}

std::ostream&
operator<<(std::ostream& os, const Matrix& A) {
   size_t m = A.dim()[0], n = A.dim()[1];
   for (size_t i = 0; i < m; ++i)
   {
      for (size_t j = 0; j < n; ++j)
      {
         if (0 != j)
         {
            os << '\t';
         }
         os << A.valueAt(i, j);
      }
      os << '\n';
   }
   return os;
}

Matrix
Matrix::zeros(const size_t m, const size_t n) {
   return Matrix(m, n, 0);
}

Matrix
Matrix::identity(const size_t n) {
   Matrix A(n, n, 0);
   for (size_t i = 0; i < n; ++i)
   {
      A(i, i) = 1;
   }
   return A;
}

} // namespace maala