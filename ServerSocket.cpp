//
// Created by spaceba on 8/03/24.
//

#include "ServerSocket.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;


int serverSocket;
int port;
struct sockaddr_in serverAddress;

void ServerSocket::acceptConnections() {
        while (true){
            struct sockaddr_in clientAddress;
            socklen_t clientAddrSize = sizeof(clientAddress);

            // Aceptar conexiones entrantes
            int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddrSize);
            if (clientSocket == -1) {
                cerr << "Error al aceptar la conexión entrante" << endl;
                exit(1);
            }
            // Mensaje de conexión
            cout << "Cliente conectado" << endl;


            // Recibir el JSON del cliente
            json receivedJsonData = receiveJsonData(clientSocket);
            string command = receivedJsonData["command"];


            // Acciones del servidor segun el comando que ingrese
            if(command == "Get-Playlist"){
                cout << "Obtener el playlist" << endl;
                //Envia la respuesta al cliente
                send_response(command, "OK", clientSocket);
                close(clientSocket);

            }
            if(command == "Vote-up"){
                //Es necesario el ID
                string id = receivedJsonData["id"];
                cout << "Votar por una cancion +1" << "id:" << id << endl;
                //Envia la respuesta al cliente
                send_response(command, "OK", clientSocket);
                close(clientSocket);
            }
            if(command == "Vote-down"){
                string id = receivedJsonData["id"];
                cout << "Votar por una cancion -1" << "id:" << id << endl;
                //Envia la respuesta al cliente
                send_response(command, "OK", clientSocket);
                close(clientSocket);
            }

            cout << receivedJsonData << endl;
            // Cerrar el socket del cliente
            close(clientSocket);
        }

    }
json ServerSocket::receiveJsonData(int clientSocket) {
        char buffer[4096]; // Buffer para almacenar los datos recibidos
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead == -1) {
            cerr << "Error al recibir datos del cliente" << endl;
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
