cmake_minimum_required(VERSION 3.16)
project(slimpajama)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem serialization)
find_package(jsoncpp REQUIRED)


include_directories(${GTEST_INCLUDE_DIRS})

# add include
include_directories(${PROJECT_SOURCE_DIR}/third_party/gtest/include)
include_directories(${PROJECT_SOURCE_DIR}/src/**/)
include_directories(${PROJECT_SOURCE_DIR}/src/preprocessing/*)
include_directories(
        /usr/include/unicode
)

add_subdirectory(src)
add_subdirectory(test)
# add executable
add_executable(slimpajama benchmark.cpp
        src/preprocessing/normalize_text.h
        src/preprocessing/normalize_text.cpp
        src/preprocessing/filter.h
        src/preprocessing/filter.cpp
        src/preprocessing/ToHash.h
        src/preprocessing/ToHash.cpp
        src/dedup/DuplicatePairs.h
        src/dedup/DuplicatePairs.cpp
        src/utils/Utils.h
        src/utils/Utils.cpp
        src/utils/MinHash.h
        )
target_include_directories(slimpajama PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(slimpajama
        ${Boost_LIBRARIES}
        jsoncpp
        icudata
        icui18n
        icuio
        icutest
        icutu
        icuuc
        )





