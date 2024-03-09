#include <iostream>
#include "Circular List.cpp"
#include "Double List.cpp"

using namespace std;

void insert_last();
void insert_first();
void printLista();
void buscarNodo();
void eliminarNodo();
void convertArray();
void insert_lastdouble();
void insert_firstdouble();
void printListadouble();
void buscarNododouble();
void eliminarNododouble();
void convertArraydouble();

int main() {
    int opcion_menu=0;
    do
    {
        cout << "\n|---------------------------------------|";
        cout << "\n|        ° LISTA CIRCULAR DOBLE °       |";
        cout << "\n|--------------------|------------------|";
        cout << "\n| 1. Insertar final  | 5. Array         |";
        cout << "\n| 2. Insertar inicio | 6. Salir         |";
        cout << "\n| 3. Buscar          |                  |";
        cout << "\n| 4. Eliminar        |                  |";
        cout << "\n|--------------------|------------------|";
        cout << "\n\n Escoja una Opcion: ";
        cin >> opcion_menu;
        switch(opcion_menu){
            case 1:
                cout << "\n\n INSERTA NODO EN LA LISTA \n\n";
                insert_lastdouble();
                break;
            case 2:
                cout << "\n\n BUSCAR UN NODO EN LA LISTA \n\n";
                insert_firstdouble();
                break;
            case 3:
                cout << "\n\n BUSCAR UN NODO EN LA LISTA \n\n";
                buscarNododouble();
                break;
            case 4:
                cout << "\n\n ELIMINAR UN NODO DE LA LISTA \n\n";
                eliminarNododouble();
                break;
            case 5:
                printListadouble();
                break;
            case 6:
                cout << "\n\n CONVERTIDO EN ARRAY \n\n";
                convertArraydouble();
                break;
            default:
                cout << "\n\n Opcion No Valida \n\n";
                break;
        }
    } while (opcion_menu != 6);

    return 0;
}