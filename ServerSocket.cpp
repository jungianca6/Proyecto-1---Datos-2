//
// Created by spaceba on 8/03/24.
//

#include "ServerSocket.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include "DoubleList.h"
#include "Admin_paginas.h"
#include "Paged_Array.h"
#include "INIReader.h"


using namespace std;
using namespace nlohmann;

// Cargar el archivo INI
INIReader reader("/home/spaceba/CLionProjects/Server/config.ini");
DoubleList lista_enlazada;
int tamano_maximo_de_pagina = reader.GetInteger("Pagina", "tamano_maximo_de_pagina", 1);
int cantidad_de_paginas_cargadas = reader.GetInteger("Pagina", "cantidad_de_paginas_cargadas", 1);
Admin_paginas admin(tamano_maximo_de_pagina,cantidad_de_paginas_cargadas);
Paged_Array arreglo_paginado(&admin);
bool paginacion;
//Lista de canciones recogidas de los archivos
Data* carpeta_de_canciones;

void ServerSocket::acceptConnections() {
    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddrSize = sizeof(clientAddress);

        // Aceptar conexiones entrantes
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddrSize);
        if (clientSocket == -1) {
            LOG(ERROR) << "Error al aceptar la conexión entrante";
            exit(1);
        }
        // Mensaje de conexión
        cout << "Cliente conectado" << endl;


        // Recibir el JSON del cliente
        json receivedJsonData = receiveJsonData(clientSocket);
        string command = receivedJsonData["command"];


        // Acciones del servidor segun el comando que ingrese
        if (command == "Get-Playlist") {
            cout << "Obtener el playlist" << endl;
            //
            //Insertar funcion para obtener los nodos de la lista y convertirlos en texto
            //

            //Verifica que la paginacion este desactivada
            if (!paginacion) {
                lista_enlazada.printListadouble();

                json lista_json = lista_enlazada.toJson();
                // Imprimir el JSON
                cout << lista_json.dump(4) << endl;

                //Envia la respuesta al cliente
                send_response(command, "OK", clientSocket, to_string(lista_json));
                close(clientSocket);
            }
            //Verifica que la paginacion este desactivada
            if (paginacion) {
                //crea un json donde se va a almacenar la lista
                json lista_json;
                //itera sobre el array para obtener todas las canciones
                for (int i= 0; i < admin.total_de_canciones; i++){
                    json jsonData;
                    jsonData = arreglo_paginado[i].toJson();
                    lista_json.push_back(jsonData);
                }

                cout << lista_json.dump(4) << endl;

                //Envia la respuesta al cliente
                send_response(command, "OK", clientSocket, to_string(lista_json));
                close(clientSocket);

            }
        }
        if (command == "Vote-up") {
            //Obtiene el id de la cancion que se desea modificar
            string nombre = receivedJsonData["nombre"];

            //Verifica si la paginacion esta desactivada
            if (!paginacion) {
                lista_enlazada.printListadouble();
                cout << "Votar por una cancion +1" << "id:" << nombre << endl;
                //Vota a la cancion
                lista_enlazada.voteUp(nombre);
                lista_enlazada.printListadouble();


                //Envia la respuesta al cliente
                send_response(command, "OK", clientSocket);
                close(clientSocket);
            }
            if (paginacion) {
                for (int i = 0; i < admin.total_de_canciones; i++) {
                    if (arreglo_paginado[i].nombre == nombre) {
                        cout << arreglo_paginado[i].nombre << endl;
                        cout << arreglo_paginado[i].votes << endl;
                        cout << "Votando..."<< endl;
                        arreglo_paginado.vote_up(i);
                        cout << arreglo_paginado[i].votes << endl;
                        break;
                    }
                    //Envia la respuesta al cliente
                    send_response(command, "OK", clientSocket);
                    close(clientSocket);
                }
            }
        }
        if (command == "Vote-down") {
            //Obtiene el id de la cancion que se desea modificar
            string nombre = receivedJsonData["nombre"];

            //Verifica si la paginacion esta desactivada
            if (!paginacion) {
                lista_enlazada.printListadouble();
                cout << "Votar por una cancion -1" << "id:" << nombre << endl;
                //Vota a la cancion
                lista_enlazada.voteDown(nombre);
                lista_enlazada.printListadouble();

                //Envia la respuesta al cliente
                send_response(command, "OK", clientSocket);
                close(clientSocket);
            }
            if (paginacion) {
                for (int i = 0; i < admin.total_de_canciones; i++) {
                    if (arreglo_paginado[i].nombre == nombre) {
                        cout << arreglo_paginado[i].nombre << endl;
                        cout << arreglo_paginado[i].votes << endl;
                        cout << "Votando..."<< endl;
                        arreglo_paginado.vote_down(i);
                        cout << arreglo_paginado[i].votes << endl;
                        break;
                    }
                    //Envia la respuesta al cliente
                    send_response(command, "OK", clientSocket);
                    close(clientSocket);
                }

            } else {
                //Envia la respuesta al cliente
                send_response(command, "ERROR", clientSocket);
                LOG(ERROR) << "Error al enviar la respuesta al cliente";
                close(clientSocket);
            }

            cout << receivedJsonData << endl;
            // Cerrar el socket del cliente
            close(clientSocket);
        }
    }
}

json ServerSocket::receiveJsonData(int clientSocket) {
    char buffer[4096]; // Buffer para almacenar los datos recibidos
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        LOG(ERROR) << "Error al recibir datos del cliente";
        exit(1);
    }
    // Convertir los datos recibidos en una cadena de texto JSON
    string jsonString(buffer, bytesRead);

    // Interpretar la cadena JSON como un objeto JSON
    json jsonData = json::parse(jsonString);
    return jsonData;
}

void ServerSocket::send_response(string command, string status, int clientsocket){
    json response = {
            {"command", command},
            {"status", status}
    };
    // Serializar el objeto JSON a una cadena de texto
    string jsonString = response.dump();
    // Enviar la cadena JSON al cliente
    send(clientsocket, jsonString.c_str(), jsonString.length(), 0);
}

void ServerSocket::send_response(string command, string status, int clientsocket, string list) {
    json response = {
            {"command", command},
            {"status", status},
            {"list", list}
    };
    // Serializar el objeto JSON a una cadena de texto
    string jsonString = response.dump();
    // Enviar la cadena JSON al cliente
    send(clientsocket, jsonString.c_str(), jsonString.length(), 0);
}

void ServerSocket::create_list_from_file(){
    //Recorre los datos obtenidos de la carpeta y crea una lista enlazada
    Data* temp = carpeta_de_canciones;
    while (temp) {
        lista_enlazada.insert_lastdouble(*temp);
        temp = temp->siguiente;
    }
}
