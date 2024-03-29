//
// Created by darga19 on 28/03/24.
//
#include <iostream>
#include <filesystem>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/mpegheader.h>

using namespace std;
namespace fs = std::filesystem;

struct Data {
    string nombre;
    string artista;
    string album;
    int duracion_minutos;
    int duracion_segundos;

    Data* siguiente;

    Data(const string& _nombre, const string& _artista, const string& _album, int _duracion_minutos, int _duracion_segundos)
            : nombre(_nombre), artista(_artista), album(_album), duracion_minutos(_duracion_minutos), duracion_segundos(_duracion_segundos), siguiente(nullptr) {}
};

void obtenerMetadatosMP3(const string& ruta_archivo, Data*& lista) {
    TagLib::FileRef archivo(ruta_archivo.c_str());
    if (!archivo.isNull() && archivo.tag()) {
        TagLib::Tag* tag = archivo.tag();
        if (tag) {
            string nombre = tag->title().toCString(true);
            string artista = tag->artist().toCString(true);
            string album = tag->album().toCString(true);

            TagLib::MPEG::File mpegFile(ruta_archivo.c_str());
            int duracion_segundos = mpegFile.audioProperties()->length();
            int minutos = duracion_segundos / 60;
            int segundos = duracion_segundos % 60;

            cout << "Nombre: " << nombre << endl;
            cout << "Artista: " << artista << endl;
            cout << "Álbum: " << album << endl;
            cout << "Duración: " << minutos << " minutos " << segundos << " segundos" << endl;

            // Crear un nuevo nodo para la canción
            Data* nueva_cancion = new Data(nombre, artista, album, minutos, segundos);
            // Agregar el nodo a la lista
            if (!lista) {
                lista = nueva_cancion;
            } else {
                Data* temp = lista;
                while (temp->siguiente) {
                    temp = temp->siguiente;
                }
                temp->siguiente = nueva_cancion;
            }
        }
    }
}

void leerArchivosMP3(const string& ruta_carpeta, Data*& lista) {
    for (const auto& entry : fs::directory_iterator(ruta_carpeta)) {
        if (entry.is_regular_file()) {
            string extension = entry.path().extension();
            if (extension == ".mp3" || extension == ".MP3") {
                cout << "\nArchivo: " << entry.path().filename() << endl;
                obtenerMetadatosMP3(entry.path().string(), lista);
            }
        }
    }
}

void print_lista(Data *lista_canciones){

    cout << "\nLista de Canciones:\n";
    Data* temp = lista_canciones;
    while (temp) {
        cout << temp->nombre << ", " << temp->artista << ", " << temp->album << ", " << temp->duracion_minutos << " minutos " << temp->duracion_segundos << " segundos " << "\n";
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