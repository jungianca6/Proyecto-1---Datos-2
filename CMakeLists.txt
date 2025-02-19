set(CMAKE_CXX_STANDARD 17)
cmake_minimum_required(VERSION 3.27)
project(Proyecto_1)
include_directories(include)
include_directories(/usr/include/unicode)

# Agrega la ruta a las bibliotecas de TagLib
link_directories(/usr/lib/x86_64-linux-gnu)

set(CMAKE_CXX_STANDARD 17 /)
add_executable(Proyecto_1 main.cpp
        ServerSocket.cpp
        Data.h
        Cancion.h
        DoubleList.cpp
        DoubleList.h
        Pagina.cpp
        Pagina.h
        Admin_paginas.cpp
        Admin_paginas.h
        Paged_Array.cpp
        Paged_Array.h
        INIReader.cpp
        INIReader.h
        ini.h
        ini.c
        Queue.cpp
        Queue.h
)

# Incluye la carpeta de encabezados
target_include_directories(Proyecto_1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/libs)

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

# Encuentra e incluye las bibliotecas de GStreamer
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

include_directories(${GSTREAMER_INCLUDE_DIRS})
link_directories(${GSTREAMER_LIBRARY_DIRS})
add_definitions(${GSTREAMER_CFLAGS_OTHER})

# Enlaza el ejecutable con las bibliotecas de GStreamer
target_link_libraries(Proyecto_1 PRIVATE ${GSTREAMER_LIBRARIES})


find_package(glog REQUIRED)
target_link_libraries(Proyecto_1 PRIVATE glog::glog)