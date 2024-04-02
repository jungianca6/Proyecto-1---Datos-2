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
#include "Data.h"

using namespace std;
namespace fs = std::filesystem;


void obtenerMetadatosMP3(const string& ruta_archivo, Data*& lista) {
    TagLib::FileRef archivo(ruta_archivo.c_str());
    if (!archivo.isNull() && archivo.tag()) {
        TagLib::Tag* tag = archivo.tag();
        if (tag) {

            char nombre[64];
            char artista[64];
            char album[64];

            strncpy(nombre, tag->title().toCString(true), sizeof(nombre));
            strncpy(artista, tag->artist().toCString(true), sizeof(artista));
            strncpy(album, tag->album().toCString(true), sizeof(album));


            TagLib::MPEG::File mpegFile(ruta_archivo.c_str());
            int duracion_segundos = mpegFile.audioProperties()->length();
            int minutos = duracion_segundos / 60;
            int segundos = duracion_segundos % 60;

            cout << "Nombre: " << nombre << endl;
            cout << "Artista: " << artista << endl;
            cout << "Álbum: " << album << endl;
            cout << "Duración: " << minutos << " minutos " << segundos << " segundos" << endl;

            // Crear un nuevo nodo para la canción
            Data* nueva_cancion = new Data(nombre, artista, album, minutos, segundos, 0);
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



