#include <iostream>
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "chrono"

using namespace std;

int hola(){
    for(int i=0; i<100; i++){
        sleep(1);
        cout << "hola desde la otra funcion" + i << endl;
    };
    return 0;
}

int main() {
    int portNumber = 12346; // Puerto en el que escuchará el servidor
    ServerSocket servidor = ServerSocket(portNumber);
    thread hilo(&ServerSocket::acceptConnections, &servidor);
    hola();

    hilo.join();
    return 0;
}
