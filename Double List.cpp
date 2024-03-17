#include <iostream>
#include <string>

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

void insert_lastdouble(string nombreCancion) {
    Node *nuevo = new Node();
    nuevo -> nombreCancion = nombreCancion;
    cout << "Dato ingresado (ultimo): " << nombreCancion << endl;

    if (primerod == NULL) {
        primerod = nuevo;
        ultimod = nuevo;

    } else {
        ultimod->siguiente = nuevo;
        nuevo->atras = ultimod;
        ultimod = nuevo;
    }
}

void insert_firstdouble(string nombreCancion) {
    Node *nuevo = new Node();
    nuevo -> nombreCancion = nombreCancion;
    cout << "Dato ingresado (primero): " << nombreCancion << endl;

    if (primerod == NULL){
        primerod = nuevo;
        ultimod = nuevo;
    } else{
        nuevo->siguiente = primerod;
        primerod->atras = nuevo;
        primerod = nuevo;
    }
}

void buscarNododouble(string nodoBuscado){
    Node *actual = primerod;
    bool encontrado = false;
    cout << "Dato buscado: " << nodoBuscado << endl;



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

void eliminarNododouble(string nodoBuscado){
    Node *actual = new Node();
    actual = primerod;
    Node *anterior = new Node();
    anterior = NULL;
    bool encontrado = false;
    cout << "Dato eliminado: " << endl;

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

int findlengthdouble(){
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
        arr[index++] = actual->nombreCancion;
        actual = actual->siguiente;
    }
    // print array
    for (int i = 0; i < len; i++){
        cout << arr[i] << " ";
    }
}