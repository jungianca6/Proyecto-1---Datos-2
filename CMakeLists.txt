set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.27)
project(Proyecto_1)
include_directories(include)

set(CMAKE_PREFIX_PATH "/usr/include/wx-3.0;/usr/local/lib/cmake")

set(CMAKE_CXX_STANDARD 17 /)
add_executable(Proyecto_1 main.cpp
        ServerSocket.cpp
)

find_package(wxWidgets REQUIRED COMPONENTS core base)

include(${wxWidgets_USE_FILE})

# Agregar la biblioteca de wxWidgets a tu objetivo
target_link_libraries(Proyecto_1 PRIVATE ${wxWidgets_LIBRARIES})

# Incluye los directorios de encabezados de TagLib
target_include_directories(Proyecto_1 PRIVATE ${TAGLIB_INCLUDE_DIRS})

# Enlaza el ejecutable con las bibliotecas de TagLib
target_link_libraries(Proyecto_1 PRIVATE ${TAGLIB_LIBRARIES})