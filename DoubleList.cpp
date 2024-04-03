//
// Created by spaceba on 31/03/24.
//

#include "DoubleList.h"
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/mpegheader.h>

namespace fs = std::filesystem;

Node *primerod = nullptr;
Node *ultimod = nullptr;

void DoubleList::printListadouble() {
    Node *actual = new Node();
    actual = primerod;
    if (primerod != NULL) {
        do {
            cout << "Nombre: " << actual->data.nombre << endl;
            cout << "Artista: " << actual->data.artista << endl;
            cout << "Duracion_minutos: " << actual->data.duracion_minutos << endl;
            cout << "Duracion_segundos: " << actual->data.duracion_segundos << endl;
            cout << "Album: " << actual->data.album << endl;
            cout << "Votes: " << actual->data.votes << endl;
            cout << endl;
            actual = actual->siguiente;
        } while (actual != NULL);
    } else {
        cout << "Vacía" << endl;
    }

}

void DoubleList::insert_lastdouble(Data new_data) {
    Node *nuevo = new Node();
    nuevo->data = new_data;
    cout << "Dato ingresado (ultimo): " << new_data.nombre << endl;

    if (primerod == NULL) {
        primerod = nuevo;
        ultimod = nuevo;

    } else {
        ultimod->siguiente = nuevo;
        nuevo->atras = ultimod;
        ultimod = nuevo;
    }
}

void DoubleList::insert_firstdouble(Data new_data) {
    Node *nuevo = new Node();
    nuevo->data = new_data;
    cout << "Dato ingresado (primero): " << new_data.nombre << endl;

    if (primerod == NULL) {
        primerod = nuevo;
        ultimod = nuevo;
    } else {
        nuevo->siguiente = primerod;
        primerod->atras = nuevo;
        primerod = nuevo;
    }
}

void DoubleList::buscarNododouble(string cancionbuscada) {
    Node *actual = primerod;
    bool encontrado = false;
    cout << "Dato buscado: " << cancionbuscada << endl;
    if (primerod != NULL) {
        do {
            if (actual->data.nombre == cancionbuscada) {
                cout << "Nodo con el dato ( " << cancionbuscada << " ) Encontrado" << endl;
                encontrado = true;
            }
            actual = actual->siguiente;
        } while (actual != NULL && encontrado != true);
        if (!encontrado) {
            cout << "Nodo no encontrado";
        }

    } else {
        cout << "nel";
    }

}

void DoubleList::voteUp(string cancionbuscada) {
    Node *actual = primerod;
    bool encontrado = false;
    cout << "Dato buscado: " << cancionbuscada << endl;
    if (primerod != NULL) {
        do {
            if (actual->data.nombre == cancionbuscada) {
                actual->data.votes = actual->data.votes + 1;
                encontrado = true;
            }
            actual = actual->siguiente;
        } while (actual != NULL && encontrado != true);
        if (!encontrado) {
            cout << "Nodo no encontrado";
        }
    } else {
        cout << "nel";
    }
}

void DoubleList::voteDown(string cancionbuscada) {
    Node *actual = primerod;
    bool encontrado = false;
    cout << "Dato buscado: " << cancionbuscada << endl;
    if (primerod != NULL) {
        do {
            if (actual->data.nombre == cancionbuscada) {
                actual->data.votes = actual->data.votes - 1;
                encontrado = true;
            }
            actual = actual->siguiente;
        } while (actual != NULL && encontrado != true);
        if (!encontrado) {
            cout << "Nodo no encontrado";
        }
    } else {
        cout << "nel";
    }
}


void DoubleList::eliminarNododouble(Data nodoBuscado) {
    Node *actual = new Node();
    actual = primerod;
    Node *anterior = new Node();
    anterior = NULL;
    bool encontrado = false;
    cout << "Dato eliminado: " << endl;

    if (primerod != NULL) {
        do {
            if (actual->data.nombre == nodoBuscado.nombre) {
                cout << "Nodo con el dato ( " << nodoBuscado.nombre << " ) eliminado" << endl;

                if (actual == primerod) {
                    primerod = primerod->siguiente;
                } else if (actual == ultimod) {
                    ultimod = anterior;
                    primerod->atras = ultimod;
                } else {
                    actual->siguiente->atras = anterior;
                }
                encontrado = true;
            }
            anterior = actual;
            actual = actual->siguiente;
        } while (actual != NULL && encontrado != true);
        if (!encontrado) {
            cout << "Nodo encontrado";
        }

    } else {
        cout << "nel";
    }
}

int DoubleList::findlengthdouble() {
    Node *actual = primerod;
    int cnt = 0;
    while (actual != NULL) {
        cnt++;
        actual = actual->siguiente;
    }
    return cnt;
}


json DoubleList::toJson(){
    json j;
    Node *current = primerod;
    while (current != nullptr) {
        json dataJson;
        dataJson["nombre"] = current->data.nombre;  // Suponiendo que Data tiene un miembro 'nombre'
        dataJson["artista"] = current->data.artista;  // Suponiendo que Data tiene un miembro 'artista'
        dataJson["album"] = current->data.album;  // Suponiendo que Data tiene un miembro 'artista'
        dataJson["duracion_minutos"] = current->data.duracion_minutos;  // Suponiendo que Data tiene un miembro 'artista'
        dataJson["duracion_segundos"] = current->data.duracion_segundos;  // Suponiendo que Data tiene un miembro 'artista'
        dataJson["votes"] = current->data.votes;  // Suponiendo que Data tiene un miembro 'artista'
        j.push_back(dataJson);
        current = current->siguiente;
    }
    return j;
}

void DoubleList::obtenerMetadatosMP3(const string& ruta_archivo, Data*& lista) {
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

void DoubleList::leerArchivosMP3(const string& ruta_carpeta, Data*& lista) {
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