file(GLOB_RECURSE CppModelProject_headers ${PROJECT_SOURCE_DIR}/src/*/*.h)
file(GLOB_RECURSE CppModelProject_sources ${PROJECT_SOURCE_DIR}/src/*/*.cpp)
add_library(CppModelProject_lib STATIC ${CppModelProject_headers} ${CppModelProject_sources})

