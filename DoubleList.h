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
    void printListadouble();
    void insert_lastdouble(Data new_data);
    void insert_firstdouble(Data new_data);
    void buscarNododouble(string cancionbuscada);
    void eliminarNododouble(Data nodoBuscado);
    int findlengthdouble();
    void convertArraydouble();
    // Método para convertir el objeto en formato JSON
    json toJson();

    void voteUp(string cancionbuscada);
    void voteDown(string cancionbuscada);
};


#endif //PROYECTO_1_DOUBLELIST_H