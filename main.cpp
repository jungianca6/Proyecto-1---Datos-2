#include <iostream>
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "chrono"
#include <stdio.h>
#include <fstream>

using namespace std;

struct Cancion{
    char nombre[30];
    char artista[30];
    int duracion;
    int id;
};


void add_to_end(Cancion data, string filename){
    // Abrir el archivo en modo binario para escritura
    ofstream archivo(filename, ios::binary | ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
    }

    // Escribir los datos en el archivo binario
    archivo.write(reinterpret_cast<const char *>(&data), sizeof(data));

    // Cerrar el archivo al finalizar
    archivo.close();
}

Cancion search_id(int id, string filename){
    ifstream archivo(filename, ios::binary);

    // Nombre a buscar
    int id_a_encontrar = id;

    // Variable para almacenar el struct leído del archivo
    Cancion cancion;

    // Leer el archivo hasta el final
    while (archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion))) {
        // Verificar si el nombre coincide con el nombre buscado
        if (cancion.id == id_a_encontrar) {
            // Cerrar el archivo al finalizar
            archivo.close();
            return cancion;
        }
    }

}

Cancion search_by_artists(string artist, string filename){

}

void search_by_index(int index, string filename){

}


int main() {
    int portNumber = 12346; // Puerto en el que escuchará el servidor
    ServerSocket servidor = ServerSocket(portNumber);
    thread hilo(&ServerSocket::acceptConnections, &servidor);

    // Datos que deseas escribir en el archivo
    Cancion cancion = {"Creo-Rock-Thing", "Brayan", 100,20};

    // Nombre del archivo binario en el que deseas escribir
    string filename = "/home/spaceba/CLionProjects/Server/archivo.bin";

    add_to_end(cancion, filename);
    Cancion busqueda = search_id(20, filename);

    cout << busqueda.nombre << endl;
    cout << busqueda.artista << endl;
    cout << busqueda.id << endl;
    cout << busqueda.duracion << endl;


    hilo.join();
    return 0;
}
