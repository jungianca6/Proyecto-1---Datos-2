#include <iostream>
#include <gtk/gtk.h>
using namespace std;

static void button_clicked(GtkWidget *widget, gpointer data) {
    cout << "¡Botón clickeado!" << endl;
}

//Funcion que activa la ventana de la aplicacion
static void activate(GtkApplication *app){
    // Crea una ventana
    GtkWidget *window;
    window = gtk_window_new();
    //Titulo de la ventana
    gtk_window_set_title(GTK_WINDOW(window),"Ventana");
    //Tamaño de la ventana
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);
    //gtk_window_set_resizable(GTK_WINDOW(window),false);

    GtkWidget *button = gtk_button_new_with_label("Mi botón");
    GtkWidget *button2 = gtk_button_new_with_label("Mi botón2");
    GtkWidget *entry;

    g_signal_connect(button, "clicked", G_CALLBACK(button_clicked),NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(button_clicked),NULL);

    entry = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(entry),FALSE);


    //algo como los paneles de java swing
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL,10);
    GtkWidget *button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 50);

    // Añade el botón al contenedor
    gtk_box_append(GTK_BOX(button_box), button);
    gtk_box_append(GTK_BOX(button_box), button2);

    gtk_widget_set_size_request(button, 150, 50);
    gtk_widget_set_size_request(button2, 150, 50);

    // Agrega el contenedor de botones al contenedor principal de la ventana
    gtk_box_append(GTK_BOX(box), button_box);
    gtk_box_append(GTK_BOX(box),entry);

    // Añade el contenedor a la ventana
    gtk_window_set_child(GTK_WINDOW(window), box);

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

