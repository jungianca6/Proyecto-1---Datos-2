#ifndef PROYECTO_1_SERVERSOCKET_H
#define PROYECTO_1_SERVERSOCKET_H
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <nlohmann/json.hpp>
using namespace std;
using namespace nlohmann;

class ServerSocket {
private:
    int serverSocket;
    int port;
    struct sockaddr_in serverAddress;

public:
    ServerSocket(int portNumber) : port(portNumber) {
        // Crear un socket
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) {
            cerr << "Error al crear el socket" << endl;
            exit(1);
        }

        // Configurar la dirección del servidor
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        // Vincular el socket a la dirección y puerto
        if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
            std::cerr << "Error al vincular el socket" << std::endl;
            exit(1);
        }

        // Escuchar por conexiones entrantes
        if (listen(serverSocket, 5) == -1) {
            cerr << "Error al escuchar por conexiones entrantes" << endl;
            exit(1);
        }
    }

    json receiveJsonData(int clientSocket);

    void send_response(string command, string status, int clientsocket);

    void acceptConnections();

    void send_response(string command, string status, int clientsocket, string list);
};


#endif //PROYECTO_1_SERVERSOCKET_H