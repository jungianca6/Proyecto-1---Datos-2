#include <iostream>

using namespace std;

struct Nodo{
    string nombreCancion;
    Nodo *siguiente;
    Nodo *atras;
}*primero, *ultimo;

void printLista(){
    Nodo *actual = primero;
    if(primero!=NULL){
        do{
            cout << actual->nombreCancion <<endl;
            actual = actual->siguiente;
        }while(actual!=primero);

    } else {
        cout << "Vacía" <<endl;
    }

}

void insert_last(string nombreCancion) {
    Nodo *nuevo = new Nodo();
    nuevo -> nombreCancion = nombreCancion;
    cout << "Dato insertado (ultimo): " << nombreCancion <<endl;

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
void insert_first(string nombreCancion) {
    Nodo *nuevo = new Nodo();
    nuevo -> nombreCancion = nombreCancion;
    cout << "Dato insertado (primero): " << nombreCancion <<endl;

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

void buscarNodo(string nodoBuscado){
    Nodo *actual = primero;
    bool encontrado = false;
    cout << "Dato buscado: " << nodoBuscado <<endl;

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

void eliminarNodo(string nodoBuscado){
    Nodo *actual = primero;
    Nodo *anterior = NULL;
    bool encontrado = false;
    cout << "Dato eliminado: " << nodoBuscado <<endl;

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

int findlength(){
    Nodo *actual = primero;
    int cnt = 0;
    while (actual != NULL) {
        cnt++;
        actual = actual->siguiente;
    }
    return cnt;
}

void convertArray(){
    int len = findlength();
    string arr[len];
    int index = 0;
    Nodo *actual = primero;

    while(actual != NULL){
        arr[index++] = actual->nombreCancion;
        actual = actual->siguiente;
    }
    for (int i = 0; i < len; i++) {
        cout << arr[i] << " ";
    }
}