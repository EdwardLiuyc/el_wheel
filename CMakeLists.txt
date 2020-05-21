cmake_minimum_required(VERSION 2.8)
project(el_wheel)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fPIC")

include(cmake_modules/eigen.cmake)
include_directories(include)

enable_testing()
add_subdirectory(test)
add_subdirectory(src)
add_subdirectory(include)