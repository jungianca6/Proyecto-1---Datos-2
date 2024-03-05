#include <iostream>
#include <gtk/gtk.h>
using namespace std;

static void activate(GtkApplication *app, gpointer user_data){
    GtkWidget *window;
    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window),"Ventana");
    gtk_widget_show(window);
    gtk_application_add_window(app, GTK_WINDOW(window));

    g_signal_connect(window, "destroy", G_CALLBACK(g_application_quit),NULL);

}

int main(int argc, char **argv) {

    gtk_init();
    GtkApplication *app = gtk_application_new("in.GVM", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate),NULL);
    
    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return status;

}

