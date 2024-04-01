//
// Created by spaceba on 31/03/24.
//

#include <iostream>
#include <string>
#include "Data.h"
#ifndef PROYECTO_1_DOUBLELIST_H
#define PROYECTO_1_DOUBLELIST_H
using namespace std;

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
    void buscarNododouble(Data nodoBuscado);
    void eliminarNododouble(Data nodoBuscado);
    int findlengthdouble();
    void convertArraydouble();
};


#endif //PROYECTO_1_DOUBLELIST_H