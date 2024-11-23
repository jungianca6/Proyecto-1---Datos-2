//
// Created by spaceba on 12/04/24.
//
//
// Created by darga19 on 11/04/24.
//

#include <iostream>
#include "Queue.h"

using namespace std;

Queue_Node *primero = nullptr;
Queue_Node *ultimo = nullptr;

void PriorQueue::insertar_nodo(Data new_data){
    Queue_Node *nuevo_nodo = new Queue_Node();
    nuevo_nodo->data = new_data;
    if (primero == nullptr || nuevo_nodo->data.votes > primero->data.votes) {
        nuevo_nodo->siguiente = primero;
        primero = nuevo_nodo;
        if (ultimo == nullptr) {
            ultimo = nuevo_nodo;
        }
        return;
    }

    Queue_Node *actual = primero;
    while (actual->siguiente != nullptr && actual->siguiente->data.votes > nuevo_nodo->data.votes) {
        actual = actual->siguiente;
    }

    nuevo_nodo->siguiente = actual->siguiente;
    actual->siguiente = nuevo_nodo;

    if (actual == ultimo) {
        ultimo = nuevo_nodo;
    }
}

void PriorQueue::elim_nodo(Data data) {
    Queue_Node *actual = primero;
    Queue_Node *anterior = nullptr;

    // Buscar el nodo a eliminar por su nombre
    while (actual != nullptr && strcmp(data.nombre, actual->data.nombre) != 0) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual != nullptr) {
        if (actual == primero) {
            primero = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }

        if (actual == ultimo) {
            ultimo = anterior;
        }

        delete actual;
    }
}

void PriorQueue::actualizar_nodo(Data data) {
    elim_nodo(data);
    insertar_nodo(data);
}

// Print para probar
void PriorQueue::imprimir_datos() {
    Queue_Node *actual = primero;
    while (actual != nullptr) {
        cout << "ID: " << actual->data.id << std::endl;
        cout << "Path: " << actual->data.path << std::endl;
        cout << "Nombre: " << actual->data.nombre << std::endl;
        cout << "Artista: " << actual->data.artista << std::endl;
        cout << "Álbum: " << actual->data.album << std::endl;
        cout << "Duración: " << actual->data.duracion_minutos << " min "
                  << actual->data.duracion_segundos << " seg" << std::endl;
        cout << "Votos: " << actual->data.votes << std::endl;
        cout << "------------------------------" << std::endl;
        actual = actual->siguiente;
    }
    cout << "\n";
}