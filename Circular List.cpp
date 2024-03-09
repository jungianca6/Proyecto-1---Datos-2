#include <iostream>

using namespace std;

struct Nodo{
    string nombreCancion;
    Nodo *siguiente;
    Nodo *atras;
}*primero, *ultimo;

void printLista(){
    Nodo *actual = new Nodo();
    actual = primero;
    if(primero!=NULL){
        do{
            cout << actual->nombreCancion <<endl;
            actual = actual->siguiente;
        }while(actual!=primero);

    } else {
        cout << "Vacía" <<endl;
    }

}

void insert_last() {
    Nodo *nuevo = new Nodo();
    cout << " Ingrese el nombre de la canción: ";
    cin >> nuevo -> nombreCancion;

    if (primero == NULL) {
        primero = nuevo;
        ultimo = nuevo;
        primero->siguiente = primero;
        primero->atras = ultimo;

    } else {
        ultimo->siguiente = nuevo;
        nuevo->atras = ultimo;
        nuevo->siguiente = primero;
        ultimo = nuevo;
        primero->atras = ultimo;
    }

}
//          (3)<-4-> <-6-> <-7-> <-8-> <-9-> <-10-> <-15-> <-3->(4)
void insert_first(){
    Nodo *nuevo = new Nodo();
    cout << " Ingrese el dato que quiere introducir: ";
    cin >> nuevo->nombreCancion;

    if (primero == NULL){
        primero = nuevo;
        ultimo = nuevo;
        primero->siguiente = primero;
        primero->atras = ultimo;
    } else{
        nuevo->siguiente = primero;
        primero->atras = nuevo;
        primero = nuevo;
        primero->atras = ultimo;
        ultimo->siguiente = primero;
    }
}

void buscarNodo(){
    Nodo *actual = new Nodo();
    actual = primero;
    bool encontrado = false;
    string nodoBuscado;
    cout << "Ingrese el dato que quiere" <<endl;
    cin >> nodoBuscado;

    if(primero!=NULL){
        do{
            if(actual->nombreCancion == nodoBuscado){
                cout << "Nodo con el dato ( " << nodoBuscado << " ) Encontrado" << endl;
                encontrado = true;
            }
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);
        if(!encontrado){
            cout << "Nodo encontrado";
        }

    } else {
        cout << "nel";
    }

}

void eliminarNodo(){
    Nodo *actual = new Nodo();
    actual = primero;
    Nodo *anterior = new Nodo();
    anterior = NULL;
    bool encontrado = false;
    string nodoBuscado;
    cout << "Ingrese el dato que quiere eliminar: " <<endl;
    cin >> nodoBuscado;

    if(primero!=NULL){
        do{
            if(actual->nombreCancion == nodoBuscado){
                cout << "Nodo con el dato ( " << nodoBuscado << " ) eliminado" << endl;

                if(actual == primero){
                    primero = primero->siguiente;
                    primero->atras = ultimo;
                    ultimo->siguiente = primero;
                }else if(actual == ultimo){
                    ultimo = anterior;
                    ultimo->siguiente = primero;
                    primero->atras= ultimo;
                }else{
                    anterior->siguiente = actual->siguiente;
                    actual->siguiente->atras = anterior;
                }
                encontrado = true;
            }
            anterior = actual;
            actual = actual->siguiente;
        }while(actual!=primero && encontrado != true);
        if(!encontrado){
            cout << "Nodo encontrado";
        }

    } else {
        cout << "nel";
    }
}