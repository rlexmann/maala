#ifndef MAALA_TWO_POINT_BOUNDARY_HPP
#define MAALA_TWO_POINT_BOUNDARY_HPP

#include <matrix.hpp>

namespace maala {

class FuncT {
 public:
   virtual double operator()(const double t) const = 0;
};

class ConstCoeff : public FuncT {
 public:
   ConstCoeff(const double c)
     : m_c{ c } {}

   virtual double operator()(const double t) const { return m_c; }

 private:
   double m_c;
};

class LinearCoeff : public FuncT {
 public:
   LinearCoeff(const double c)
     : m_c{ c } {}

   virtual double operator()(const double t) const { return m_c * t; }

 private:
   double m_c;
};

Matrix
twoPointBoundarySecondDegreeSolver(const FuncT* a,
                                   const FuncT* b,
                                   const FuncT* c,
                                   const FuncT* rhs,
                                   const double t0,
                                   const double y0,
                                   const double t1,
                                   const double y1,
                                   const size_t n);

}

#endif // ifndef MAALA_TWO_POINT_BOUNDARY_HPP