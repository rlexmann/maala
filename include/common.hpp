#ifndef MAALA_COMMON_HPP
#define MAALA_COMMON_HPP

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

}

#endif // ifndef MAALA_COMMON_HPP