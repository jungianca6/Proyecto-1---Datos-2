#include <iostream>

using namespace std;

struct Node{
    string nombreCancion;
    Node *siguiente;
    Node *atras;
}*primerod, *ultimod;

//          4-> <-6-> <-7-> <-8-> <-9-> <-10-> <-15-> <-3
void printListadouble(){
    Node *actual = new Node();
    actual = primerod;
    if(primerod!=NULL){
        do{
            cout << actual->nombreCancion <<endl;
            actual = actual->siguiente;
        }while(actual!=NULL);
    } else {
        cout << "Vacía" <<endl;
    }

}

void insert_lastdouble() {
    Node *nuevo = new Node();
    cout << " Ingrese el nombre de la canción: ";
    cin >> nuevo -> nombreCancion;

    if (primerod == NULL) {
        primerod = nuevo;
        ultimod = nuevo;

    } else {
        ultimod->siguiente = nuevo;
        nuevo->atras = ultimod;
        ultimod = nuevo;
    }
}

void insert_firstdouble(){
    Node *nuevo = new Node();
    cout << " Ingrese el dato que quiere introducir: ";
    cin >> nuevo->nombreCancion;

    if (primerod == NULL){
        primerod = nuevo;
        ultimod = nuevo;
    } else{
        nuevo->siguiente = primerod;
        primerod->atras = nuevo;
        primerod = nuevo;
    }
}

void buscarNododouble(){
    Node *actual = new Node();
    actual = primerod;
    bool encontrado = false;
    string nodoBuscado;
    cout << "Ingrese el dato que quiere" <<endl;
    cin >> nodoBuscado;

    if(primerod!=NULL){
        do{
            if(actual->nombreCancion == nodoBuscado){
                cout << "Nodo con el dato ( " << nodoBuscado << " ) Encontrado" << endl;
                encontrado = true;
            }
            actual = actual->siguiente;
        }while(actual!=NULL && encontrado != true);
        if(!encontrado){
            cout << "Nodo no encontrado";
        }

    } else {
        cout << "nel";
    }

}

void eliminarNododouble(){
    Node *actual = new Node();
    actual = primerod;
    Node *anterior = new Node();
    anterior = NULL;
    bool encontrado = false;
    string nodoBuscado;
    cout << "Ingrese el dato que quiere eliminar: " <<endl;
    cin >> nodoBuscado;
    if(primerod!=NULL){
        do{
            if(actual->nombreCancion == nodoBuscado){
                cout << "Nodo con el dato ( " << nodoBuscado << " ) eliminado" << endl;

                if(actual == primerod){
                    primerod = primerod->siguiente;
                }else if(actual == ultimod){
                    ultimod = anterior;
                    primerod->atras= ultimod;
                }else{
                    actual->siguiente->atras = anterior;
                }
                encontrado = true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }while(actual!=NULL && encontrado != true);
        if(!encontrado){
            cout << "Nodo encontrado";
        }

    } else {
        cout << "nel";
    }
}