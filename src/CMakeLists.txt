file(GLOB_RECURSE slimpajama_headers ${PROJECT_SOURCE_DIR}/src/*/*.h)
file(GLOB_RECURSE slimpajama_sources ${PROJECT_SOURCE_DIR}/src/*/*.cpp)
add_library(slimpajama_lib STATIC ${slimpajama_headers} ${slimpajama_sources})

