#include <iostream>
#include "Circular List.cpp"
#include "Double List.cpp"

using namespace std;

int main() {
    int opcion_menu=0;
    string nombreCancion;
    string nodoBuscado;
    do
    {
        cout << "\n|---------------------------------------|";
        cout << "\n|        ° LISTA CIRCULAR DOBLE °       |";
        cout << "\n|--------------------|------------------|";
        cout << "\n| 1. Insertar final  | 5. Print         |";
        cout << "\n| 2. Insertar inicio | 6. Array         |";
        cout << "\n| 3. Buscar          |                  |";
        cout << "\n| 4. Eliminar        |                  |";
        cout << "\n|--------------------|------------------|";
        cout << "\n\n Escoja una Opcion: ";
        cin >> opcion_menu;
        switch(opcion_menu){
            case 1:
                cout << "\n Inserta un nodo en la lista (ultimo): ";
                cin >> nombreCancion;
                insert_lastdouble(nombreCancion);
                break;
            case 2:
                cout << "\n Inserta un nodo en la lista (primero): ";
                cin >> nombreCancion;
                insert_firstdouble(nombreCancion);
                break;
            case 3:
                cout << "\n Inserta el nodo que quieras buscar: ";
                cin >> nodoBuscado;
                buscarNododouble(nodoBuscado);
                break;
            case 4:
                cout << "\n Inserta el nodo que quieras eliminar: ";
                cin >> nodoBuscado;
                eliminarNododouble(nodoBuscado);
                break;
            case 5:
                cout << "\n Lista printeada:\n";
                printListadouble();
                break;
            case 6:
                cout << "\n Convertido en array:\n";
                convertArraydouble();
                break;
            default:
                cout << "\n Opcion no valida\n";
                break;
        }
    } while (opcion_menu != 6);


    return 0;
}