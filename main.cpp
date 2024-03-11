#include <iostream>
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "chrono"
#include <stdio.h>
#include <fstream>

#include "Circular List.cpp"
#include "Double List.cpp"
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "chrono"
#include <stdio.h>
#include <fstream>

using namespace std;

struct Cancion{
    char nombre[30];
    char artista[30];
    int duracion;
    int id;
};

void add_to_end(Cancion data, string filename){
    // Abrir el archivo en modo binario para escritura
    ofstream archivo(filename, ios::binary | ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
    }

    // Escribir los datos en el archivo binario
    archivo.write(reinterpret_cast<const char *>(&data), sizeof(data));

    // Cerrar el archivo al finalizar
    archivo.close();
}

Cancion search_id(int id, string filename){
    ifstream archivo(filename, ios::binary);

    // Nombre a buscar
    int id_a_encontrar = id;

    // Variable para almacenar el struct leído del archivo
    Cancion cancion;

    // Leer el archivo hasta el final
    while (archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion))) {
        // Verificar si el nombre coincide con el nombre buscado
        if (cancion.id == id_a_encontrar) {
            // Cerrar el archivo al finalizar
            archivo.close();
            return cancion;
        }
    }

}

Cancion search_by_artists(string artist, string filename){

}

Cancion search_by_index(int index, string filename){
    ifstream archivo(filename, ios::binary);

    // Variable para almacenar el struct leído del archivo
    Cancion cancion;

    //Mover el puntero hasta la posision deseada
    archivo.seekg((index-1)*sizeof(cancion));

    // Leer el archivo hasta el final
    archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion));
    return cancion;

}


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

    cout << busqueda.nombre << endl;
    cout << busqueda.artista << endl;
    cout << busqueda.id << endl;
    cout << busqueda.duracion << endl;


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
