project( Expresly )
cmake_minimum_required( VERSION 3.1 )

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
set(CMAKE_CXX_FLAGS_MINSIZEREL "/MT")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MTd")

include_directories("${Expresly_SOURCE_DIR}/include")
add_subdirectory("${Expresly_SOURCE_DIR}/src")

add_subdirectory("${Expresly_SOURCE_DIR}/tests")