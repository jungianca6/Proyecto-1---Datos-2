cmake_minimum_required(VERSION 3.27)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 17 /)

add_executable(
        main.cpp
        ServerSocket.cpp
        ServerSocket.h
        "cmake-build-debug/Lista circular.cpp"
        "Circular List.cpp"
        "Double List.cpp"
)