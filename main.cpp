#include <iostream>
#include <gtk/gtk.h>
using namespace std;
static void activate(GtkApplication *app, gpointer user_data){
    //gtk code comes here
}
int main(int argc, char **argv) {
    int ret;
    GtkApplication *app;

    app = gtk_application_new("in.GVM",G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);

    ret = g_application_run(G_APPLICATION(app), argc, argv);
    
    g_object_unref(app);
    return ret;

}

