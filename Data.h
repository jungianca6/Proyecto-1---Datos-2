//
// Created by spaceba on 31/03/24.
//

#ifndef PROYECTO_1_DATA_H
#define PROYECTO_1_DATA_H
#include <cstring>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>//sudo apt-get install libboost-all-dev

using namespace boost::uuids;
using namespace std;

struct Data{
    uuid id;
    char nombre[64];
    char artista[64];
    char album[64];
    int duracion_minutos;
    int duracion_segundos;
    int votes;
    Data* siguiente;

    Data(){
        id = boost::uuids::random_generator()();
    };

    Data(const char* _nombre, const char* _artista, const char* _album, int _duracion_minutos, int _duracion_segundos, int _votes)
            : duracion_minutos(_duracion_minutos), duracion_segundos(_duracion_segundos), siguiente(nullptr), votes(_votes) {
        strncpy(nombre, _nombre, sizeof(nombre));
        strncpy(artista, _artista, sizeof(artista));
        strncpy(album, _album, sizeof(album));
        id = boost::uuids::random_generator()();
    }

    void print_lista(Data *lista_canciones){
        cout << "\nLista de Canciones:\n";
        Data* temp = lista_canciones;
        while (temp) {
            cout << temp->id << "," << temp->nombre << ", " << temp->artista << ", " << temp->album << ", " << temp->duracion_minutos << " minutos " << temp->duracion_segundos << " segundos " <<
                 " votos " << temp->votes << "\n";
            temp = temp->siguiente;
        }
    }



    Data* buscar_nodo(Data* lista_canciones, const string& nombreCancion) {
        Data* temp = lista_canciones;
        while (temp) {
            if (temp->nombre == nombreCancion) {
                // Si se encuentra la canción, se devuelve el nodo actual
                return temp;
            }
            temp = temp->siguiente;
        }
        // Si no se encuentra la canción, se devuelve nullptr
        return nullptr;
    }

};


#endif //PROYECTO_1_DATA_H
