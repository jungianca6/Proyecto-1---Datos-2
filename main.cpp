#include <iostream>
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


int hola(){
    for(int i=0; i<100; i++){
        sleep(1);
        cout << "hola desde la otra funcion" << i << endl;
    };
    return 0;
}

int main() {
    int portNumber = 12346; // Puerto en el que escuchará el servidor
    ServerSocket servidor = ServerSocket(portNumber);
    thread hilo(&ServerSocket::acceptConnections, &servidor);

    // Nombre del archivo binario en el que deseas escribir
    string filename = "/home/darga19/CLionProjects/Server/archivo.bin";

    // Abrir el archivo en modo binario para escritura
    ofstream archivo(filename, ios::binary | ios::app);

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo " << filename << std::endl;
        return 1;
    }

    // Datos que deseas escribir en el archivo
    Cancion cancion = {"Creo-Rock-Thing", "Brayan", 10,10};

    // Escribir los datos en el archivo binario
    archivo.write(reinterpret_cast<const char *>(&cancion), sizeof(cancion));

    // Cerrar el archivo al finalizar
    archivo.close();


    hilo.join();


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


    return 0;
     */
    return 0;
}

