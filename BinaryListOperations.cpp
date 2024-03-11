//
// Created by spaceba on 10/03/24.
//
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Cancion{
    char nombre[30];
    char artista[30];
    int duracion;
    int id;
};

//Annade una cancion al final
void add_to_end(Cancion data, string filename){
    // Abrir el archivo en modo binario para escritura
    ofstream archivo(filename, ios::binary | ios::app);

    // Escribir los datos en el archivo binario
    archivo.write(reinterpret_cast<const char *>(&data), sizeof(data));

    // Cerrar el archivo al finalizar
    archivo.close();
}

//Obtiene la cancion deseada por el ID
Cancion search_id(int id, string filename){
    ifstream archivo(filename, ios::binary);

    // Variable para almacenar el struct leído del archivo
    Cancion cancion;

    // Leer el archivo hasta el final
    while (archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion))) {
        // Verificar si el nombre coincide con el nombre buscado
        if (cancion.id == id) {
            // Cerrar el archivo al finalizar
            archivo.close();
            return cancion;
        }
    }

}

//Obtiene la lista de las canciones
Cancion* get_songs(string filename, Cancion* canciones){
    ifstream archivo(filename, ios::binary);

    // Variable para contar el número de personas leídas del archivo
    int num_personas = 0;

    // Leer el archivo hasta el final y almacenar cada persona en el array
    while (archivo.read(reinterpret_cast<char*>(&canciones[num_personas]), sizeof(Cancion))) {
        // Incrementar el contador de personas
        num_personas++;

        // Verificar si se excede el tamaño máximo del array
        if (num_personas >= 100) {
            cerr << "Se ha alcanzado el límite máximo de personas" << endl;
            break;
        }
    }
    // Cerrar el archivo al finalizar la lectura
    archivo.close();

    return canciones;
}

//Obtiene la cancion mediante un indice
Cancion search_by_index(int index, string filename){
    ifstream archivo(filename, ios::binary);

    // Variable para almacenar el struct leído del archivo
    Cancion cancion;

    //Mover el puntero hasta la posision deseada
    archivo.seekg((index-1)*sizeof(cancion));

    // Leer el archivo hasta el final
    archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion));
    return cancion;

}
