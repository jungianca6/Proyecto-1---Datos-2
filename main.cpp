#include <iostream>
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "chrono"
#include <stdio.h>
#include "Circular List.cpp"
#include "Double List.cpp"
#include "BinaryListOperations.cpp"


using namespace std;


int main() {

    int portNumber = 12346; // Puerto en el que escuchará el servidor
    ServerSocket servidor = ServerSocket(portNumber);
    thread hilo(&ServerSocket::acceptConnections, &servidor);

    // Datos que deseas escribir en el archivo
    Cancion cancion = {"Creo-B", "Mario", 300,3};

    // Nombre del archivo binario en el que deseas escribir
    string filename = "/home/spaceba/CLionProjects/Server/archivo.bin";

    //add_to_end(cancion, filename);
    Cancion busqueda = search_by_index(3, filename);

    // Array para almacenar todas las personas del archivo, es static para que permanezca
    Cancion canciones[10];
    Cancion* lista = get_songs(filename, canciones);

    // Mostrar los datos de todas las personas almacenadas
    for (int i = 0; i < 10; ++i) {
        cout << "Persona " << i+1 << ":" << endl;
        cout << "Nombre: " << lista[i].nombre << endl;
        cout << "Edad: " << lista[i].artista << endl;
        cout << "Altura: " << lista[i].id << endl;
        cout << "Altura: " << lista[i].duracion << endl;
        cout << endl;
    }



    /*
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
*/


    hilo.join();
    return 0;
}
