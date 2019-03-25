cmake_minimum_required(VERSION 3.6)

project (maala)
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

configure_file (${INCLUDE_DIR}/config.hpp.in ${INCLUDE_DIR}/config.hpp)

include_directories (include)
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp" "${INCLUDE_DIR}/*.hpp")

add_executable (Demo ${SOURCES})
set_target_properties(
  Demo PROPERTIES
    VS_STARTUP_PROJECT Demo
    SUFFIX ".exe"
)
