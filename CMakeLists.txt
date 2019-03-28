cmake_minimum_required(VERSION 3.6)

project (maala)
set (MAALA_VERSION_MAJOR 1)
set (MAALA_VERSION_MINOR 0)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

# maala core

set(CORE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core/src)
set(CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core/include)

configure_file (${CORE_INCLUDE_DIR}/config.hpp.in ${CORE_INCLUDE_DIR}/config.hpp)

file(GLOB_RECURSE CORE_SOURCES
	"${CORE_SOURCE_DIR}/*.cpp"
	"${CORE_INCLUDE_DIR}/*.hpp"
)

add_library(maala_core SHARED ${CORE_SOURCES})
target_include_directories (maala_core PRIVATE ${CORE_INCLUDE_DIR})
target_include_directories (maala_core INTERFACE ${CORE_INCLUDE_DIR})
set_target_properties(maala_core PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# exercises

set(EX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/exercises/src)
set(EX_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/exercises/include)

file(GLOB_RECURSE EX_SOURCES
	"${EX_SOURCE_DIR}/*.cpp"
	"${EX_INCLUDE_DIR}/*.hpp"
)

add_executable (demo ${EX_SOURCES})
target_include_directories (demo PRIVATE ${EX_INCLUDE_DIR})
target_link_libraries (demo maala_core)
set_target_properties(demo PROPERTIES SUFFIX ".exe")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT demo)