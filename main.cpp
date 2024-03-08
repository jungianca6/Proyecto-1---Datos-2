#include <iostream>
#include <string>
#include "ServerSocket.h"

int main() {
    int portNumber = 12346; // Puerto en el que escuchará el servidor
    ServerSocket servidor = ServerSocket(portNumber);
    // Aceptar conexiones continuamente
    servidor.acceptConnections();

    return 0;
}
