//
// Created by spaceba on 6/04/24.
//

#include "Pagina.h"

// Método para cargar el contenido de un archivo binario en las páginas
void Pagina::cargarContenidoDesdeArchivo() {
    ifstream archivo(filename_admin, ios::binary); // Abre el archivo en modo binario
    canciones = new Cancion[tamanoMaximo];

    // Mover el puntero a la posición deseada dentro del archivo
    archivo.seekg((id-1)*sizeof(Cancion)*tamanoMaximo, ios::beg);

    int i = 0;
    while (i < tamanoMaximo) {
        archivo.read(reinterpret_cast<char*>(&canciones[i]), sizeof(Cancion));
        i++;
    }
    cargada = true;

    archivo.close(); // Cierra el archivo
}

// Método para cargar el contenido de un archivo binario en las páginas
void Pagina::descargarContenidoDesdeArchivo() {
    // Abrir el archivo en modo binario para escritura
    ofstream archivo(filename_admin, ios::binary | ios::in | ios::out);

    // Mover el puntero a la posición deseada dentro del archivo
    archivo.seekp((id-1)*sizeof(Cancion)*tamanoMaximo, std::ios::beg);

    int i = 0;
    while(i < tamanoMaximo){
        // Escribir los datos en el archivo binario
        archivo.write(reinterpret_cast<const char *>(&canciones[i]), sizeof(Cancion));
        i++;
    }


    // Cerrar el archivo al finalizar
    archivo.close();

}

