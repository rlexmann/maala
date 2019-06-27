#ifndef MAALA_COMMON_HPP
#define MAALA_COMMON_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#define THROW_EXCEPTION(msg)                              \
   {                                                      \
      std::ostringstream em;                              \
      em << __FILE__ << " (" << __LINE__ << "): " << msg; \
      throw em.str();                                     \
   }

#define UNCONST(Tobject, method, Treturn) \
   const_cast<Treturn>(static_cast<const Tobject&>(*this).method)

namespace maala {

static void
TRACE(const std::string& msg) {
   std::cout << msg << std::endl;
}

typedef std::vector<double> double1D;
typedef std::vector<std::vector<double>> double2D;
typedef std::array<size_t, 2> range_t;

template<typename T>
constexpr bool
isEqual(const T a,
        const T b,
        const T precision = std::numeric_limits<T>::epsilon()) {
   return std::abs(a - b) <= precision;
}

// template <int N>
// using range = std::array<int, N>;

} // namespace maala

#endif // ifndef MAALA_COMMON_HPP