
#ifndef PROYECTO_1_CANCION_H
#define PROYECTO_1_CANCION_H
#include <cstring>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>//sudo apt-get install libboost-all-dev

#include <nlohmann/json.hpp>
#include <cstring>

using json = nlohmann::json;
using namespace boost::uuids;

struct Cancion{
    uuid id;
    char path[128];
    char nombre[64];
    char artista[64];
    char album[64];
    int duracion_minutos;
    int duracion_segundos;
    int votes;

    //Constructor vacio
    Cancion(){
    }
    //Constructor con todos los atributos
    Cancion(const char* _path, uuid _id,const char* _nombre, const char* _artista, const char* _album, int _duracion_minutos, int _duracion_segundos, int _votes)
            : id(_id), duracion_minutos(_duracion_minutos), duracion_segundos(_duracion_segundos),votes(_votes) {
        strncpy(path, _path, sizeof(path));
        strncpy(nombre, _nombre, sizeof(nombre));
        strncpy(artista, _artista, sizeof(artista));
        strncpy(album, _album, sizeof(album));
    }

    void Vote_Up(){
        votes = votes + 1;
    }

    void Vote_Down(){
        votes = votes - 1;
    }

    // Función para convertir la Cancion a formato JSON
    json toJson() const {
        json j;
        j["id"] = id;
        j["path"] = path;
        j["nombre"] = nombre;
        j["artista"] = artista;
        j["album"] = album;
        j["duracion_minutos"] = duracion_minutos;
        j["duracion_segundos"] = duracion_segundos;
        j["votes"] = votes;
        return j;
    }



};


#endif //PROYECTO_1_DATA_H