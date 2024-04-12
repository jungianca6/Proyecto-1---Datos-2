
//
// Created by darga19 on 11/04/24.
//

#ifndef PROYECTO_1_QUEUE_H
#define PROYECTO_1_QUEUE_H

#include <iostream>
#include "Data.h"

using namespace std;

class Queue_Node {
public:
    Data data;
    Queue_Node *siguiente;
    Queue_Node *atras;
};

class PriorQueue {
private:
    Queue_Node *primero = nullptr;
    Queue_Node *ultimo = nullptr;
public:
    // Inserta un nodo de último
    void insertar_nodo(Data new_data);
    // Elimina un nodo
    void elim_nodo(Data new_data);
    // Actualiza la lista si es que un nodo cambia de votos
    void actualizar_nodo(Data data);
    //Print para probarlo
    void imprimir_datos();

};


#endif //PROYECTO_1_QUEUE_H
