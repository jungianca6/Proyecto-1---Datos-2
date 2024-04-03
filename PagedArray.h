//
// Created by spaceba on 1/04/24.
//

#ifndef PROYECTO_1_PAGEDARRAY_H
#define PROYECTO_1_PAGEDARRAY_H

#include <string>
#include "Cancion.h"
#include "DoubleList.h"

using namespace std;


class PagedArray : public DoubleList{
public:
    Cancion * canciones;
    string filename = "/home/spaceba/CLionProjects/Server/archivo.bin";
    int largo = cantidad_de_canciones("/home/spaceba/Music");

    Cancion search_by_index(int index);

    void delete_song(int song_id);

    Cancion search_id(int id);

    void add_to_end(Cancion data);

    static int cantidad_de_canciones(const string &ruta_carpeta);

    void get_songs(Cancion *&canciones);
};



#endif //PROYECTO_1_PAGEDARRAY_H
