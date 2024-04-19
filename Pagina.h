//
// Created by spaceba on 6/04/24.
//

#ifndef PROYECTO_1_PAGINA_H
#define PROYECTO_1_PAGINA_H

#include "Cancion.h"
#include <filesystem>
#include <fstream>
#include "iostream"
#include "INIReader.h"

using namespace std;
namespace fs = filesystem;



class Pagina {
public:
    // Cargar el archivo INI
    INIReader ini_reader = INIReader("/home/dell/Escritorio/Proyecto-1-Datos-2/config.ini");
    string filename_admin = ini_reader.GetString("BIN", "directorio", "/home/dell/Escritorio/Proyecto-1-Datos-2/archivo.bin");
    Cancion* canciones; // Arreglo dinámico de canciones
    int tamanoMaximo; // Tamaño máximo de la página
    int id; //Identidicador de la pagina
    bool cargada;

    Pagina() {}
    // Constructor
    Pagina(int tamano) : tamanoMaximo(tamano) {
        canciones = new Cancion[tamanoMaximo]; // Inicializa el arreglo dinámico con el tamaño deseado
    }

    // Destructor
    ~Pagina() {
        delete[] canciones; // Libera la memoria del arreglo dinámico
    }

    void cargarContenidoDesdeArchivo();

    void descargarContenidoDesdeArchivo();
};


#endif //PROYECTO_1_PAGINA_H
