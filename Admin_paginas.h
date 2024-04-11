//
// Created by spaceba on 6/04/24.
//

#ifndef PROYECTO_1_ADMIN_PAGINAS_H
#define PROYECTO_1_ADMIN_PAGINAS_H
#include "Pagina.h"
#include <iostream>
#include "Cancion.h"
#include "INIReader.h"
using namespace std;

class Admin_paginas {
public:
    // Cargar el archivo INI
    INIReader ini = INIReader("/home/spaceba/CLionProjects/Server/config.ini");
    string ini_total_de_canciones = ini.GetString("Cancion", "directorio", "/home/spaceba/Music");
    int total_de_canciones = cantidad_de_canciones(ini_total_de_canciones);
    int tamano_maximo_por_pagina; // Tamaño máximo de cada página en bytes
    Pagina* paginas; // Arreglo de páginas
    int* paginas_cargadas;
    int total_de_paginas_cargadas; // Número total de páginas
    int num_paginas = total_de_canciones/tamano_maximo_por_pagina;
    int contador_de_paginas_cargadas = 0;

    // Constructor
    Admin_paginas(int tamano_maximo, int cantidad_de_paginas) : tamano_maximo_por_pagina(tamano_maximo), total_de_paginas_cargadas(cantidad_de_paginas){
        paginas_cargadas = new int[total_de_paginas_cargadas]; // Inicializa el arreglo de páginas con el número total de páginas
        paginas = new Pagina[num_paginas];
        // Inicia en ceros el array de paginas cargadas
        for (int i = 0; i < total_de_paginas_cargadas; ++i) {
            paginas_cargadas[i] = 0;
        }
        // Crear páginas automáticamente con IDs y tamaño máximo de página
        for (int i = 0; i < num_paginas; ++i) {
            paginas[i].id = i + 1; // Asignar IDs empezando desde 1
            paginas[i].tamanoMaximo = tamano_maximo; // Asignar tamaño máximo de página
            paginas[i].cargada = false;
        }
    }
    // Destructor
    ~Admin_paginas() {
        delete[] paginas; // Libera la memoria del arreglo de páginas
    }

    int obtenerTamanoPaginaEnBytes(int pagina_index) const;

    void descargarPaginaContenido(int pagina_index);

    void cargarContenidoDesdeArchivo(Cancion *&canciones);

    int cantidad_de_canciones(const string& ruta_carpeta);
};

#endif //PROYECTO_1_ADMIN_PAGINAS_H
