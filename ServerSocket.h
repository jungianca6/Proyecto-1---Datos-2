//
// Created by spaceba on 8/03/24.
//

#ifndef PROYECTO_1_SERVERSOCKET_H
#define PROYECTO_1_SERVERSOCKET_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include "DoubleList.h"
#include "Paged_Array.h"
#include <arpa/inet.h> // Agregar esta línea
#include "INIReader.h"
#include <glog/logging.h> //sudo apt-get install libgoogle-glog-dev
using namespace std;
using namespace nlohmann;


class ServerSocket {
public:
    int serverSocket;
    int port;
    struct sockaddr_in serverAddress;
    string ipAddress; // Nueva variable para almacenar la IP
    DoubleList lista_enlazada;
    bool paginacion;
    Data* carpeta_de_canciones;
    bool active_playlist;


    //Constructor con el puerto
    ServerSocket(){
        // Cargar el archivo INI
        INIReader reader("/home/spaceba/CLionProjects/Server/config.ini");
        if (reader.ParseError() < 0) {
            std::cout << "Error al cargar el archivo INI" << std::endl;
        }
        active_playlist = false;
        // Leer valores del archivo INI y asignarlos a variables
        port = reader.GetInteger("Servidor", "portNumber", 123456);
        ipAddress = reader.Get("Servidor", "IP", "127.0.0.1");
        paginacion = false;
        // Crear un socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) {
            LOG(ERROR) << "Error al crear el socket";
            exit(1);
        }

        // Configurar la dirección del servidor
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(ipAddress.c_str()); // Utilizar la IP proporcionada
        serverAddress.sin_port = htons(port);

        // Vincular el socket a la dirección y puerto
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
            LOG(ERROR) << "Error al vincular el socket";
            exit(1);
        }

        // Escuchar por conexiones entrantes
        if (listen(serverSocket, 5) == -1) {
            LOG(ERROR) << "Error al escuchar por conexiones entrantes";
            exit(1);
        }
    }

    //Recibe los datos y los convierte a formato json
    json receiveJsonData(int clientSocket);
    //Envia la respuesta al cliente (exitoso o no)
    void send_response(string command, string status, int clientsocket);
    //Pone al servidor en modo de escucha
    void acceptConnections();
    //Envia la respuesta al cliente (lista de canciones)
    void send_response(string command, string status, int clientsocket, string list);
    //Construye una lista con las canciones de la carpeta de lectura
    void create_list_from_file();

};


#endif //PROYECTO_1_SERVERSOCKET_H
