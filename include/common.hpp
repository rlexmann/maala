#ifndef MAALA_COMMON_HPP
#define MAALA_COMMON_HPP

#include <string>
#include <cstring>

#define THROW_EXCEPTION(msg) \
    char exceptMsg[256]; \
    sprintf(exceptMsg,"%s (%d): %s",__FILE__, __LINE__, msg); \
    throw std::string(exceptMsg);

#endif // ifndef MAALA_MATRIX_HPP