cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -std=c++14")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/EmscriptenToolchain.cmake")

project (emscripten_example)
set(BINARY_NAME "em_exe")
add_executable(${BINARY_NAME} "main.cpp")
configure_file(index.html.in index.html)
