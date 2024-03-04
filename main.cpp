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

    void acceptConnections() {
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
            cout << "Votar por una cancion +1" << endl;
            //Envia la respuesta al cliente
            send_response(command, "OK", clientSocket);
            close(clientSocket);
        }
        if(command == "Vote-down"){
            //Es necesario el ID
            cout << "Votar por una cancion -1" << endl;
            //Envia la respuesta al cliente
            send_response(command, "OK", clientSocket);
            close(clientSocket);
        }

        cout << receivedJsonData << endl;
        // Cerrar el socket del cliente
        close(clientSocket);
        }

    }
    json receiveJsonData(int clientSocket) {
        char buffer[1024]; // Buffer para almacenar los datos recibidos
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
    void send_response(string command, string status, int clientsocket){
        json response = {
                {"command", command},
                {"status", status}
        };
        // Serializar el objeto JSON a una cadena de texto
        string jsonString = response.dump();
        // Enviar la cadena JSON al cliente
        send(clientsocket, jsonString.c_str(), jsonString.length(), 0);
    }

};

int main() {
    int portNumber = 12346; // Puerto en el que escuchará el servidor
    ServerSocket servidor = ServerSocket(portNumber);
    // Aceptar conexiones continuamente
    servidor.acceptConnections();

    return 0;
}
