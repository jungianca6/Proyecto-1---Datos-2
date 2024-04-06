//
// Created by spaceba on 31/03/24.
//

#include <iostream>
#include <string>
#include "Data.h"
#include <nlohmann/json.hpp>
#ifndef PROYECTO_1_DOUBLELIST_H
#define PROYECTO_1_DOUBLELIST_H

using namespace std;
using namespace nlohmann;


class Node {
public:
    Data data;
    Node *siguiente;
    Node *atras;
};

class DoubleList {
private:
    Node *primerod = nullptr;
    Node *ultimod = nullptr;
public:
    //Imprime la lista
    void printListadouble();
    // Inserta un elemento al final
    void insert_lastdouble(Data new_data);
    // Inserta un elemento al principio
    void insert_firstdouble(Data new_data);
    // Elimina un nodo
    void eliminarNododouble(string nodoBuscado);
    // Busca un nodo
    void buscarNododouble(string cancionbuscada);
    // Encuentra el largo de la lista
    int findlengthdouble();
    // Método para convertir el objeto en formato JSON
    json toJson();
    //Vota por una cancion a favor
    void voteUp(string cancionbuscada);
    //Vota por una cancion a favor
    void voteDown(string cancionbuscada);
    //Lee las canciones en la carpeta y crea un arreglo de Data
    void leerArchivosMP3(const string& ruta_carpeta, Data*& lista);
    //Obtiene los metadatos de las canciones obtenidas
    void obtenerMetadatosMP3(const string& ruta_archivo, Data*& lista);
    //Agarra los nodos de la lista y los escribe en disco
    void List_to_Array();
    //
    void play_song(string cancionbuscada);
};


#endif //PROYECTO_1_DOUBLELIST_H