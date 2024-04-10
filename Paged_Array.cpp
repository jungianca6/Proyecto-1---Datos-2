//
// Created by spaceba on 6/04/24.
//

#include "Paged_Array.h"
//
// Created by spaceba on 1/04/24.
//

#include <iostream>
#include <string>
#include <fstream>
#include "Cancion.h"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;


int largo = Paged_Array::cantidad_de_canciones("/home/dell/Escritorio/Musica");
string filename = "/home/dell/Escritorio/Proyecto-1-Datos-2/archivo.bin";


int Paged_Array::cantidad_de_canciones(const string& ruta_carpeta) {
    int i = 0;
    for (const auto& entry : fs::directory_iterator(ruta_carpeta)) {
        if (entry.is_regular_file()) {
            string extension = entry.path().extension();
            if (extension == ".mp3" || extension == ".MP3") {
                i++;
            }
        }
    }
    return i;
}

//Annade una cancion al final
void Paged_Array::add_to_end(Cancion data){
    // Abrir el archivo en modo binario para escritura
    ofstream archivo(filename, ios::binary | ios::app);

    // Escribir los datos en el archivo binario
    archivo.write(reinterpret_cast<const char *>(&data), sizeof(data));

    // Cerrar el archivo al finalizar
    archivo.close();
}


//Obtiene la cancion deseada por el ID
Cancion Paged_Array::search_id(uuid id){
    ifstream archivo(filename, ios::binary);

    // Variable para almacenar el struct leído del archivo
    Cancion cancion;

    // Leer el archivo hasta el final
    while (archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion))) {
        // Verificar si el id coincide con el nombre buscado
        if (cancion.id == id) {
            // Cerrar el archivo al finalizar
            archivo.close();
            return cancion;
        }
    }
}

/*
//ELiminar cancion segun el ID
void Paged_Array::delete_song(int song_id){
    ifstream archivo(filename, ios::binary);

    // Variable para contar el número de canciones leídas del archivo
    int number_of_songs = 0;

    // Leer el archivo hasta el final y almacenar cada persona en el array
    while (archivo.read(reinterpret_cast<char*>(&canciones[number_of_songs]), sizeof(Cancion))) {
        // Incrementar el contador de personas
        number_of_songs++;

        // Verificar si se excede el tamaño máximo del array
        if (number_of_songs >= 10) {
            cerr << "Se ha alcanzado el límite máximo de personas" << endl;
            break;
        }
    }
    // Cerrar el archivo al finalizar la lectura
    archivo.close();

    ofstream escritura(filename, ios::binary);

    for(int i = 0; i < number_of_songs; i++){
        if (canciones[i]->duracion_minutos != song_id){
            // Escribir los datos en el archivo binario
            escritura.write(reinterpret_cast<const char *>(&canciones[i]), sizeof(Cancion));
        }
    }
    escritura.close();
}
*/

//Obtiene la canci;on mediante un indice
Cancion Paged_Array::search_by_index(int index){
    ifstream archivo(filename, ios::binary);

    // Variable para almacenar el struct leído del archivo
    Cancion cancion;

    //Mover el puntero hasta la posision deseada
    archivo.seekg((index-1)*sizeof(cancion));

    // Leer el archivo hasta el final
    archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion));
    return cancion;
}

void Paged_Array::clear_file(){
    ofstream archivo(filename, std::ofstream::trunc);
    if (archivo.is_open()) {
        archivo.close();
        std::cout << "El archivo \"" << filename << "\" ha sido limpiado." << std::endl;
    } else {
        std::cerr << "No se pudo abrir el archivo \"" << filename << "\" para limpiar." << std::endl;
    }
}