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


int hola(){
    for(int i=0; i<100; i++){
        sleep(1);
        cout << "hola desde la otra funcion" << i << endl;
    };
    return 0;
}

int main() {
    int portNumber = 12346; // Puerto en el que escuchará el servidor
    ServerSocket servidor = ServerSocket(portNumber);
    thread hilo(&ServerSocket::acceptConnections, &servidor);

    // Nombre del archivo binario en el que deseas escribir
    string filename = "/home/spaceba/CLionProjects/Server/archivo.bin";

    // Abrir el archivo en modo binario para escritura
    ofstream archivo(filename, ios::binary | ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return 1;
    }

    // Datos que deseas escribir en el archivo
    Cancion cancion = {"Creo-Rock-Thing", "Brayan", 10,10};

    // Escribir los datos en el archivo binario
    archivo.write(reinterpret_cast<const char *>(&cancion), sizeof(cancion));

    // Cerrar el archivo al finalizar
    archivo.close();




    hilo.join();
    return 0;
}
