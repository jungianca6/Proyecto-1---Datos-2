//
// Created by spaceba on 6/04/24.
//

#ifndef PROYECTO_1_PAGED_ARRAY_H
#define PROYECTO_1_PAGED_ARRAY_H
#include "Admin_paginas.h"


class Paged_Array {
public:
    Admin_paginas *admin;

    Paged_Array(Admin_paginas* admin) : admin(admin) {}

    Cancion operator[](int index) {
        int pagina_index = index / admin->tamano_maximo_por_pagina; // Calcular el índice de la página
        int cancion_index = index % admin->tamano_maximo_por_pagina; // Calcular el índice de la canción dentro de la página

        Pagina& pagina = admin->paginas[pagina_index]; // Obtener la página correspondiente

        if(pagina.cargada){
            // Retornar la canción correspondiente
            return pagina.canciones[cancion_index];
        }
        if(!pagina.cargada && admin->contador_de_paginas_cargadas == admin->total_de_paginas_cargadas) {
            int id_descarga = admin->paginas_cargadas[0];

            for (int i=0; i < admin->num_paginas; i++){
                if(admin->paginas[i].id == id_descarga){
                    admin->paginas[i].descargarContenidoDesdeArchivo();
                    admin->paginas[i].cargada = false;
                    pagina.cargarContenidoDesdeArchivo();
                    pagina.cargada = true;
                    admin->paginas_cargadas[i] = pagina.id;
                    break;
                }
            }

            // Retornar la canción correspondiente
            return pagina.canciones[cancion_index];
        }

        // Verificar si la página está cargada en memoria
        if (!pagina.cargada && admin->contador_de_paginas_cargadas < admin->total_de_paginas_cargadas) {
            // Si la página no está cargada, cargar su contenido desde el archivo
            pagina.cargarContenidoDesdeArchivo();
            pagina.cargada = true; // Marcar la página como cargada
            admin->contador_de_paginas_cargadas++;
            for(int i=0 ; i < admin->total_de_paginas_cargadas; i++){
                if (admin->paginas_cargadas[i] == 0){
                    admin->paginas_cargadas[i] = pagina.id;
                    break;
                }
            }
        }

        // Retornar la canción correspondiente
        return pagina.canciones[cancion_index];
    }
};


#endif //PROYECTO_1_PAGED_ARRAY_H
