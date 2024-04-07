//
// Created by spaceba on 6/04/24.
//

#include "Admin_paginas.h"


int tamano_maximo; // Tamaño máximo de cada página en bytes
Pagina* paginas; // Arreglo de páginas
int cantidad_de_paginas; // Número total de páginas


// Método para obtener el tamaño total del contenido de una página en bytes
int Admin_paginas::obtenerTamanoPaginaEnBytes(int pagina_index) const {
    return paginas[pagina_index].tamanoMaximo * sizeof(Cancion);
}

// Método para descargar el contenido de una página a un archivo binario y actualizar su estado de carga
void Admin_paginas::descargarPaginaContenido(int pagina_index) {
}



int Admin_paginas::cantidad_de_canciones(const string& ruta_carpeta) {
    int i = 0;
    for (const auto& entry : fs::directory_iterator(ruta_carpeta)) {
        if (entry.is_regular_file()) {
            string extension = entry.path().extension();
            if (extension == ".mp3" || extension == ".MP3") {
                i++;
            }
        }
    }
    return i;
}


