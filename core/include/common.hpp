#ifndef MAALA_COMMON_HPP
#define MAALA_COMMON_HPP

#include <limits>
#include <sstream>
#include <string>
#include <vector>

#define THROW_EXCEPTION(msg)                                                   \
  std::ostringstream em;                                                       \
  em << __FILE__ << " (" << __LINE__ << "): " << msg;                          \
  throw em.str();

#define UNCONST(Tobject, method, Treturn)                                      \
  const_cast<Treturn>(static_cast<const Tobject&>(*this).method)

namespace maala {

typedef std::vector<double> double1D;
typedef std::vector<std::vector<double>> double2D;

template<typename T>
constexpr bool
isEqual(const T a, const T b)
{
  return std::abs(a - b) <= std::numeric_limits<T>::epsilon();
}

}

#endif // ifndef MAALA_COMMON_HPP