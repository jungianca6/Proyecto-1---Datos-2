set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.27)
project(Proyecto_1)
include_directories(include)


# Agrega la ruta a las bibliotecas de TagLib
link_directories(/usr/lib/x86_64-linux-gnu)

set(CMAKE_CXX_STANDARD 17 /)
add_executable(Proyecto_1 main.cpp
        ServerSocket.cpp
        Data.h
        Cancion.h
        DoubleList.cpp
        DoubleList.h
)


find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# Agregar la biblioteca de wxWidgets a tu objetivo
target_link_libraries(Proyecto_1 PRIVATE ${wxWidgets_LIBRARIES})

# Incluye los directorios de encabezados de TagLib
target_include_directories(Proyecto_1 PRIVATE /usr/include/taglib)
include_directories(Proyecto_1 PRIVATE /usr/include/taglib)

# Enlaza el ejecutable con las bibliotecas de TagLib
target_link_libraries(Proyecto_1 PRIVATE tag)


include_directories(${SNDFILE_INCLUDE_DIRS})
include_directories(${OGG_INCLUDE_DIRS})

# Busca la librería SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_MIXER_INCLUDE_DIRS})

# Enlaza el ejecutable con la biblioteca SDL2
target_link_libraries(Proyecto_1 PRIVATE ${SDL2_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})