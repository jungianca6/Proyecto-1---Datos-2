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

using namespace std;
namespace fs = std::filesystem;
using namespace std;


class PagedArray{
public:
    string filename = "/home/spaceba/CLionProjects/Server/archivo.bin";
    int largo = cantidad_de_canciones("/home/spaceba/Music");
    Cancion* canciones[10];

    Cancion operator[](int index){
        ifstream archivo(filename, ios::binary);

        // Variable para almacenar el struct leído del archivo
        Cancion cancion;

        //Mover el puntero hasta la posision deseada
        archivo.seekg((index-1)*sizeof(cancion));

        // Leer el archivo hasta el final
        archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion));
        return cancion;
    };

    Cancion search_by_index(int index);

    void delete_song(int song_id);

    Cancion search_id(int id);

    void add_to_end(Cancion data);

    static int cantidad_de_canciones(const string &ruta_carpeta);

    void get_songs(Cancion *&canciones);

    void clear_file();
};



#endif //PROYECTO_1_PAGEDARRAY_H
