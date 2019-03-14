#ifndef MAALA_COMMON_HPP
#define MAALA_COMMON_HPP

#include <string>

#define THROW_EXCEPTION(msg) \
    std::ostringstream em; \
    em << __FILE__ << " (" << __LINE__ << "): " << msg; \
    throw em.str();

#endif // ifndef MAALA_MATRIX_HPP