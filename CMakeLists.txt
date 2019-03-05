cmake_minimum_required(VERSION 2.8)
project(el_wheel)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -fPIC")

include(cmake_modules/eigen.cmake)

include_directories(include)

enable_testing()
add_subdirectory(test)