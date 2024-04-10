//
// Created by spaceba on 1/04/24.
//

#ifndef PROYECTO_1_PAGEDARRAY_H
#define PROYECTO_1_PAGEDARRAY_H

#include <string>
#include "Cancion.h"
#include "DoubleList.h"
#include <filesystem>
#include <fstream>
#include "Admin_paginas.h"

using namespace std;
namespace fs = std::filesystem;
using namespace std;


class PagedArray{
public:
    PagedArray(){}

    string filename = "/home/spaceba/CLionProjects/Server/archivo.bin";
    int largo = cantidad_de_canciones("/home/spaceba/Music");
    Cancion* canciones[10];

    Cancion operator[](int index) {
        /*
        int pagina_index = (index - 1) / admin.tamano_maximo; // Calcular el índice de la página
        int cancion_index = (index - 1) % admin.tamano_maximo; // Calcular el índice de la canción dentro de la página

        Pagina& pagina = admin.paginas[pagina_index]; // Obtener la página correspondiente

        // Verificar si la página está cargada en memoria
        if (!pagina.cargada) {
            // Si la página no está cargada, cargar su contenido desde el archivo
            pagina.cargarContenidoDesdeArchivo();
            pagina.cargada = true; // Marcar la página como cargada
        }

        // Retornar la canción correspondiente
        return pagina.canciones[cancion_index];
         */
    }


    //Busca una cancion por el indice
    Cancion search_by_index(int index); //ELiminar porque realiza la misma funcion que la sobrecarga del metodo
    //Elimina una cancion
    void delete_song(int song_id);
    //Obtiene la cancion deseada por el ID
    Cancion search_id(uuid id);
    //Annade una cancion al final
    void add_to_end(Cancion data);
    //Obtiene la cantidad de canciones que hay en la carpeta
    static int cantidad_de_canciones(const string &ruta_carpeta);
    //Obtiene la lista de las canciones
    void get_songs(Cancion *&canciones);
    //Limpia el archivo binario
    void clear_file();
};



#endif //PROYECTO_1_PAGEDARRAY_H
