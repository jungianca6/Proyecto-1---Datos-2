//
// Created by spaceba on 31/03/24.
//

#include "DoubleList.h"
#include "Paged_Array.h"
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/mpegheader.h>
#include <ogg/ogg.h>
#include <gst/gst.h>
#include <glog/logging.h>
#include "ServerSocket.h"
#include "Data.h"


namespace fs = std::filesystem;

// Cargar el archivo INI
INIReader ini = INIReader("/home/dell/Escritorio/Proyecto-1-Datos-2/config.ini");
string filename_double_list = ini.GetString("BIN", "directorio", "/home/dell/Escritorio/Proyecto-1-Datos-2/archivo.bin");
GstElement *pipeline;
GstElement *source;
GstElement *volume;
Node *primerod = nullptr;
Node *ultimod = nullptr;



void DoubleList::printListadouble() {
    Node *actual = new Node();
    actual = primerod;
    if (primerod != NULL) {
        do {
            cout << "Path: " << actual->data.path << endl;
            cout << "ID: " << actual->data.id << endl;
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
            LOG(WARNING) << "Nodo no encontrado.";
            cout << "Nodo no encontrado";
        }

    } else {
        LOG(WARNING) << "Lista vacia";
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
            LOG(WARNING) << "Nodo no encontrado";
            cout << "Nodo no encontrado";
        }
    } else {
        LOG(WARNING) << "Lista vacia";
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
            LOG(WARNING) << "Nodo no encontrado";
            cout << "Nodo no encontrado";
        }
    } else {
        LOG(WARNING) << "Lista vacia";
        cout << "nel";
    }
}

void DoubleList::play_song(bool paginada) {
    Node *actual = primerod;
    if (primerod != NULL) {
        do {
            if (paginada!=true) {
                if (!pipeline) {
                    // Crear un nuevo pipeline
                    pipeline = gst_pipeline_new("audio-player");

                    // Crear los elementos necesarios
                    source = gst_element_factory_make("filesrc", "file-source");
                    GstElement *parse = gst_element_factory_make("mpegaudioparse", "mp3-parser");
                    GstElement *decoder = gst_element_factory_make("mpg123audiodec", "mp3-decoder");
                    volume = gst_element_factory_make("volume", "volume-name");
                    GstElement *converter = gst_element_factory_make("audioconvert", "audio-converter");
                    GstElement *resample = gst_element_factory_make("audioresample", "audio-resampler");
                    GstElement *sink = gst_element_factory_make("autoaudiosink", "audio-output");

                    if (!pipeline || !source || !parse || !decoder || !volume || !converter || !resample || !sink) {
                        std::cerr << "Error al crear los elementos." << std::endl;
                    } else {
                        // Establecer el archivo fuente
                        string path = actual->data.path;
                        g_object_set(G_OBJECT(source), "location",
                                     path.c_str(), NULL);
                        cout << "Musica encontrada" << endl;

                        // Añadir los elementos al pipeline
                        gst_bin_add_many(GST_BIN(pipeline), source, parse, decoder, converter, resample, sink, NULL);

                        cout << "Elementos añadidos" << endl;

                        if (!gst_element_link_many(source, parse, decoder, converter, resample, sink, NULL)) {
                            std::cerr << "Error al enlazar los elementos." << std::endl;
                            gst_object_unref(pipeline);
                            pipeline = nullptr; // Establecer pipeline a nullptr si hay un error
                        } else {
                            // Iniciar la reproducción
                            GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
                            if (ret == GST_STATE_CHANGE_FAILURE) {
                                std::cerr << "Error al iniciar la reproducción." << std::endl;
                            } else {
                                cout << "Reproduccion" << endl;
                            }
                        }
                    }
                }else{
                    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
                    if (ret == GST_STATE_CHANGE_FAILURE) {
                        std::cerr << "Error al reiniciar la reproducción." << std::endl;
                    } else {
                        cout << "Reproduccion reiniciada" << endl;
                    }
                }
                actual = actual->siguiente;  //PARA QUE SE REPRODUZCA LA SIGUIENTE
            } else {

            }

        } while (actual != NULL);
    } else {
        LOG(WARNING) << "Lista vacia";
        cout << "nel";
    }
}

void DoubleList::Pausa(){
    LOG(INFO) << "Cancion pausada";
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
}
void DoubleList::Anterior() {
    LOG(INFO) << "Canción anterior";

    if (!primerod) {
        cout << "La lista de reproducción está vacía." <<endl;
        return;
    }


    Node *actual = ultimod->atras; // Obtener el anterior nodo

    gst_element_set_state(pipeline, GST_STATE_PAUSED);
    sleep(1);
    gst_element_set_state(pipeline, GST_STATE_READY);
    string path = actual->data.path;
    g_object_set(G_OBJECT(source), "location", path.c_str(), NULL);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    ultimod = actual;
    cout<<"anterior"<<endl;

}
void DoubleList::Siguiente(){
    LOG(INFO) << "Siguiente Canción";
    gst_element_set_state(pipeline, GST_STATE_PAUSED);

    if (!primerod) {
        cout << "La lista de reproducción está vacía." <<endl;
        return;
    }

    Node *actual = primerod->siguiente; // Obtener el siguiente nodo

    gst_element_set_state(pipeline, GST_STATE_NULL);
    sleep(1);
    gst_element_set_state(pipeline, GST_STATE_READY);
    string path = actual->data.path;
    g_object_set(G_OBJECT(source), "location", path.c_str(), NULL);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    primerod = actual;
}

void DoubleList::Volumen(){
}

void DoubleList::eliminarNododouble(string nodoBuscado) {
    Node *actual = new Node();
    actual = primerod;
    Node *anterior = new Node();
    anterior = NULL;
    bool encontrado = false;
    cout << "Dato eliminado: " << endl;

    if (primerod != NULL) {
        do {
            if (actual->data.nombre == nodoBuscado) {
                cout << "Nodo con el dato ( " << nodoBuscado << " ) eliminado" << endl;

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
            LOG(WARNING) << "Nodo no encontrado";
            cout << "Nodo encontrado";
        }

    } else {
        LOG(WARNING) << "Lista vacia";
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
        dataJson["id"] = to_string(current->data.id);
        dataJson["nombre"] = current->data.nombre;
        dataJson["artista"] = current->data.artista;
        dataJson["album"] = current->data.album;
        dataJson["duracion_minutos"] = current->data.duracion_minutos;
        dataJson["duracion_segundos"] = current->data.duracion_segundos;
        dataJson["votes"] = current->data.votes;
        j.push_back(dataJson);
        current = current->siguiente;
    }
    delete current;
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
            char path[128];

            strncpy(nombre, tag->title().toCString(true), sizeof(nombre));
            strncpy(artista, tag->artist().toCString(true), sizeof(artista));
            strncpy(album, tag->album().toCString(true), sizeof(album));
            strncpy(path, ruta_archivo.c_str(), sizeof(album));



            TagLib::MPEG::File mpegFile(ruta_archivo.c_str());
            int duracion_segundos = mpegFile.audioProperties()->length();
            int minutos = duracion_segundos / 60;
            int segundos = duracion_segundos % 60;

            cout << "Path: " << ruta_archivo << endl;
            cout << "Nombre: " << nombre << endl;
            cout << "Artista: " << artista << endl;
            cout << "Álbum: " << album << endl;
            cout << "Duración: " << minutos << " minutos " << segundos << " segundos" << endl;



            // Crear un nuevo nodo para la canción
            Data* nueva_cancion = new Data(path ,nombre, artista, album, minutos, segundos, 0);
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

void DoubleList::List_to_Array() {
    Node *actual = primerod;
    Paged_Array pagedArray;
    pagedArray.clear_file();
    while (actual != NULL) {
        Cancion* cancion = new Cancion(actual->data.path, actual->data.id,actual->data.nombre,actual->data.artista,actual->data.album,actual->data.duracion_minutos,
                                      actual->data.duracion_segundos, actual->data.votes);

        pagedArray.add_to_end(*cancion);
        actual = actual->siguiente;
    }
}

string DoubleList::get_by_index(int index) {
    Node *actual = primerod;
    if (index == 0){
        return actual->data.nombre;
    }
    else{
        for (int i=0; i <= index; i++)
            actual = actual->siguiente;
        return actual->data.nombre;
    }
}

// Función para eliminar el contenido de la lista y liberar memoria
void DoubleList::clear() {
    Node* current = primerod;
    while (current) {
        Node* next = current->siguiente;
        delete current;
        current = next;
    }
    primerod = ultimod = nullptr;
}

void DoubleList::create_list_from_file(){
    ifstream archivo(filename_double_list, ios::binary);
    cout << "llego" << endl;
    Cancion cancion_leida;

    int i = 0;

    while(archivo.read(reinterpret_cast<char *>(&cancion_leida), sizeof(Cancion))){
        if (cancion_leida.nombre[0] != '\0'){
            cout << cancion_leida.nombre << endl;

            Data* data = new Data(cancion_leida.path, cancion_leida.nombre, cancion_leida.artista, cancion_leida.album, cancion_leida.duracion_minutos,
                                 cancion_leida.duracion_segundos, cancion_leida.votes);
            insert_lastdouble(*data);
            i++;
            delete data;
        }
        else{
            break;
        }

    }
    printListadouble();
    // Cerrar el archivo al finalizar la lectura
    archivo.close();
}