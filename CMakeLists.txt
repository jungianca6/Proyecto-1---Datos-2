cmake_minimum_required(VERSION 3.27)
project(Proyecto_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proyecto_1 main.cpp)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Agregar la biblioteca de wxWidgets a tu objetivo
target_link_libraries(Proyecto_1 ${wxWidgets_LIBRARIES})


