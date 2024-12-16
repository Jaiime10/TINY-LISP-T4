cmake_minimum_required(VERSION 3.10)
project(TinyLispInterpreter)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(TinyLispInterpreter src/Variant.cpp
        main.cpp
)

# Enlazar la biblioteca nlohmann/json

