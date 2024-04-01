#include <iostream>
#include <string>
#include "Metadata.cpp"
using namespace std;

class Node {
public:
    Data data;
    Node *siguiente;
    Node *atras;
};

class ListaDoble {
private:
    Node *primerod = nullptr;
    Node *ultimod = nullptr;
public:
    //          4-> <-6-> <-7-> <-8-> <-9-> <-10-> <-15-> <-3
    void printListadouble() {
        Node *actual = new Node();
        actual = primerod;
        if (primerod != NULL) {
            do {
                cout << actual->data.nombre << endl;
                cout << actual->data.artista << endl;
                cout << actual->data.duracion_minutos << endl;
                cout << actual->data.duracion_segundos << endl;
                cout << actual->data.album << endl;
                actual = actual->siguiente;
            } while (actual != NULL);
        } else {
            cout << "Vacía" << endl;
        }

    }

    void insert_lastdouble(Data new_data) {
        Node *nuevo = new Node();
        nuevo->data = new_data;
        cout << "Dato ingresado (ultimo): " << new_data.nombre << endl;

        if (primerod == NULL) {
            primerod = nuevo;
            ultimod = nuevo;

        } else {
            ultimod->siguiente = nuevo;
            nuevo->atras = ultimod;
            ultimod = nuevo;
        }
    }

    void insert_firstdouble(Data new_data) {
        Node *nuevo = new Node();
        nuevo->data = new_data;
        cout << "Dato ingresado (primero): " << new_data.nombre << endl;

        if (primerod == NULL) {
            primerod = nuevo;
            ultimod = nuevo;
        } else {
            nuevo->siguiente = primerod;
            primerod->atras = nuevo;
            primerod = nuevo;
        }
    }

    void buscarNododouble(Data nodoBuscado) {
        Node *actual = primerod;
        bool encontrado = false;
        cout << "Dato buscado: " << nodoBuscado.nombre << endl;


        if (primerod != NULL) {
            do {
                if (actual->data.nombre == nodoBuscado.nombre) {
                    cout << "Nodo con el dato ( " << nodoBuscado.nombre << " ) Encontrado" << endl;
                    encontrado = true;
                }
                actual = actual->siguiente;
            } while (actual != NULL && encontrado != true);
            if (!encontrado) {
                cout << "Nodo no encontrado";
            }

        } else {
            cout << "nel";
        }

    }

    void eliminarNododouble(Data nodoBuscado) {
        Node *actual = new Node();
        actual = primerod;
        Node *anterior = new Node();
        anterior = NULL;
        bool encontrado = false;
        cout << "Dato eliminado: " << endl;

        if (primerod != NULL) {
            do {
                if (actual->data.nombre == nodoBuscado.nombre) {
                    cout << "Nodo con el dato ( " << nodoBuscado.nombre << " ) eliminado" << endl;

                    if (actual == primerod) {
                        primerod = primerod->siguiente;
                    } else if (actual == ultimod) {
                        ultimod = anterior;
                        primerod->atras = ultimod;
                    } else {
                        actual->siguiente->atras = anterior;
                    }
                    encontrado = true;
                }
                anterior = actual;
                actual = actual->siguiente;
            } while (actual != NULL && encontrado != true);
            if (!encontrado) {
                cout << "Nodo encontrado";
            }

        } else {
            cout << "nel";
        }
    }

    int findlengthdouble() {
        Node *actual = primerod;
        int cnt = 0;
        while (actual != NULL) {
            cnt++;
            actual = actual->siguiente;
        }
        return cnt;
    }

    void convertArraydouble() {
        int len = findlengthdouble();
        string arr[len];
        int index = 0;
        Node *actual = primerod;

        while (actual != NULL) {
            arr[index++] = actual->data.nombre;
            actual = actual->siguiente;
        }
        // print array
        for (int i = 0; i < len; i++) {
            cout << arr[i] << " ";
        }
    }
};