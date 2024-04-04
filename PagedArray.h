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
