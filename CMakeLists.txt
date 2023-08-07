cmake_minimum_required(VERSION 3.16)
project(CppModelProject)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# add include
include_directories(${PROJECT_SOURCE_DIR}/third_party/gtest/include)
include_directories(${PROJECT_SOURCE_DIR}/src/**/)

add_subdirectory(src)
add_subdirectory(test)
# add executable
add_executable(CppModelProject benchmark.cpp src/MyClass/MyClass.h src/MyClass/MyClass.cpp src/MultipleManager/MultipleManager.cpp src/MultipleManager/MultipleManager.h)


