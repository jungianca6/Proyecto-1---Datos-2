//
// Created by spaceba on 31/03/24.
//

#ifndef PROYECTO_1_DATA_H
#define PROYECTO_1_DATA_H
#include <cstring>

struct Data {
    char nombre[64];
    char artista[64];
    char album[64];
    int duracion_minutos;
    int duracion_segundos;
    int votes;

    Data* siguiente;

    Data(){};

    Data(const char* _nombre, const char* _artista, const char* _album, int _duracion_minutos, int _duracion_segundos, int _votes)
            : duracion_minutos(_duracion_minutos), duracion_segundos(_duracion_segundos), siguiente(nullptr), votes(_votes) {
        strncpy(nombre, _nombre, sizeof(nombre));
        strncpy(artista, _artista, sizeof(artista));
        strncpy(album, _album, sizeof(album));
    }

};


#endif //PROYECTO_1_DATA_H
