#include <iostream>
#include <gtk/gtk.h>
using namespace std;

//Funcion que activa la ventana de la aplicacion
static void activate(GtkApplication *app){
    // Crea una ventana
    GtkWidget *window;
    window = gtk_window_new();
    //Titulo de la ventana
    gtk_window_set_title(GTK_WINDOW(window),"Ventana");
    //Tamaño de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 400);

    //Muestra la ventana
    gtk_widget_show(window);
    // Se agrega la ventana a la aplicación
    gtk_application_add_window(app, GTK_WINDOW(window));

    //Detiene la funcion al destruit la ventana
    g_signal_connect(window, "destroy", G_CALLBACK(g_application_quit),NULL);

}

int main(int argc, char **argv) {
    // Se inicializa GTK
    gtk_init();

    // Se crea una nueva instancia de GtkApplication, creando la aplicacion
    GtkApplication *app = gtk_application_new("in.GVM",
                                              G_APPLICATION_FLAGS_NONE);

    // Llama a la funcion que crea la ventana
    g_signal_connect(app, "activate", G_CALLBACK(activate),NULL);

    // Se ejecuta la aplicación
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    // Se libera la memoria de la aplicación
    g_object_unref(app);

    return status;
}

