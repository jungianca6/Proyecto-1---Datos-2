cmake_minimum_required(VERSION 3.27)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proyecto_1 main.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

include_directories(${GTK4_INCLUDE_DIRS})
link_directories(${GTK4_LIBRARY_DIRS})
add_definitions(${GTK4_CFLAGS_OTHER})

target_link_libraries(Proyecto_1 ${GTK4_LIBRARIES})
