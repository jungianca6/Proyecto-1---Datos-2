//
// Created by spaceba on 10/03/24.
//
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Cancion{
    string nombre;
    string artista;
    string album;
    int duracion_minutos;
    int duracion_segundos;
};

//Annade una cancion al final
void add_to_end(Cancion data, string filename){
    // Abrir el archivo en modo binario para escritura
    ofstream archivo(filename, ios::binary | ios::app);

    // Escribir los datos en el archivo binario
    archivo.write(reinterpret_cast<const char *>(&data), sizeof(data));

    // Cerrar el archivo al finalizar
    archivo.close();
}

//Obtiene la cancion deseada por el ID
Cancion search_id(string nombre, string filename){
    ifstream archivo(filename, ios::binary);

    // Variable para almacenar el struct leído del archivo
    Cancion cancion;

    // Leer el archivo hasta el final
    while (archivo.read(reinterpret_cast<char*>(&cancion), sizeof(cancion))) {
        // Verificar si el nombre coincide con el nombre buscado
        if (cancion.nombre == nombre) {
            // Cerrar el archivo al finalizar
            archivo.close();
            return cancion;
        }
    }

}

//Obtiene la lista de las canciones
Cancion* get_songs(string filename, Cancion* canciones){
    ifstream archivo(filename, ios::binary );

    archivo.seekg(0, ios::beg);


    // Variable para contar el número de personas leídas del archivo
    int visited_songs = 0;

    // Leer el archivo hasta el final y almacenar cada persona en el array
    while (archivo.read(reinterpret_cast<char*>(&canciones[visited_songs]), sizeof(Cancion))) {
        // Incrementar el contador de personas
        visited_songs++;
        // Dentro del bucle de lectura
        cout << "Canción encontrada: " << canciones[visited_songs].nombre << endl;

        // Verificar si se excede el tamaño máximo del array
        if (visited_songs >= 10) { // MAX_SONGS es el tamaño máximo del array
            cerr << "Se ha excedido el tamaño máximo de canciones." << endl;
            break;
        }

    }


    // Cerrar el archivo al finalizar la lectura
    archivo.close();

    return canciones;
}

//ELiminar cancion segun el ID
void delete_song(string filename, string song_name){
    Cancion canciones[100];
    ifstream archivo(filename, ios::binary);

    // Variable para contar el número de personas leídas del archivo
    int number_of_songs = 0;

    // Leer el archivo hasta el final y almacenar cada persona en el array
    while (archivo.read(reinterpret_cast<char*>(&canciones[number_of_songs]), sizeof(Cancion))) {
        // Incrementar el contador de personas
        number_of_songs++;

        // Verificar si se excede el tamaño máximo del array
        if (number_of_songs >= 100) {
            cerr << "Se ha alcanzado el límite máximo de personas" << endl;
            break;
        }
    }
    // Cerrar el archivo al finalizar la lectura
    archivo.close();

    ofstream escritura(filename, ios::binary);

    for(int i = 0; i < number_of_songs; i++){
        if (canciones[i].nombre != song_name){
            // Escribir los datos en el archivo binario
            escritura.write(reinterpret_cast<const char *>(&canciones[i]), sizeof(Cancion));
        }
    }
    escritura.close();
}

//Obtiene la cancion mediante un indice
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
