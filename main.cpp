#include <iostream>
#include <wx/wx.h>
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "Circular List.cpp"
#include "DoubleList.h"
#include "PagedArray.h"
#include <sndfile.h>
#include <ogg/ogg.h>
#include <gst/gst.h>



int portNumber = 12346;
ServerSocket servidor = ServerSocket(portNumber);
PagedArray array_de_canciones;

enum IDs{
    botonID =2,textoID=3
};

using namespace std;
namespace fs = std::filesystem;namespace fs = std::filesystem;

//clase que crea la ventana
class MainFrame : public wxFrame {
public:
    bool active_playlist = false;

    MainFrame(const wxString &title)
            : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition,
                      wxSize(1200, 900)) {

        wxPanel *panel = new wxPanel(this, wxID_ANY);
        panel->SetBackgroundColour(wxColour(9,129, 53));


        wxButton *paginacion, *comunitario, *buscarCancion,*reproduccion,*pausa,
        *anterior,*siguiente,*eliminar;


        paginacion = new wxButton(panel, botonID, "Paginacion",
                                  wxPoint(150, 50), wxSize(150, 60));
        paginacion->Bind(wxEVT_BUTTON, &MainFrame::PaginacionActionButton, this);

        comunitario = new wxButton(panel, botonID, "Playlist comunitario",
                                   wxPoint(150, 250), wxSize(250, 60));
        comunitario->Bind(wxEVT_BUTTON, &MainFrame::ComunitarioActionButton, this);

        buscarCancion = new wxButton(panel, botonID, "Buscar",
                                     wxPoint(950, 110), wxSize(125, 30));

        reproduccion = new wxButton(panel, botonID, "Reproducir",
                                    wxPoint(300, 500), wxSize(125, 40));
        pausa= new wxButton(panel, botonID, "Pausar",
                            wxPoint(450, 500), wxSize(125, 40));
        anterior = new wxButton(panel, botonID, "Anterior",
                             wxPoint(300, 600), wxSize(125, 40));
        siguiente= new wxButton(panel, botonID, "Siguiente",
                               wxPoint(450, 600), wxSize(125, 40));
        eliminar= new wxButton(panel, botonID, "Eliminar canciones",
                               wxPoint(600, 600), wxSize(125, 40));

        wxSlider *volumen = new wxSlider(panel,wxID_ANY,50,0,100,
                                         wxPoint(650,500),wxSize(200,-1));



        wxStaticText *cancion, *busqueda, *volumencancion;
        cancion = new wxStaticText(panel, wxID_ANY, "Cancion",
                                   wxPoint(550, 20),wxSize(90,35),
                                   wxALIGN_CENTER);
        cancion->SetForegroundColour(wxColour(255,255,255));
        cancion->SetFont(GetFont().Scale(1.5));
        cancion->SetBackgroundColour(wxColour(0,0,0));

        busqueda = new wxStaticText(panel, wxID_ANY, "Busqueda",
                                    wxPoint(950, 20),wxSize(105,35),wxALIGN_CENTER);
        busqueda->SetForegroundColour(wxColour(255,255,255));
        busqueda->SetFont(GetFont().Scale(1.5));
        busqueda->SetBackgroundColour(wxColour(0,0,0));

        caja = new wxTextCtrl(panel, textoID, "",
                              wxPoint(500, 60), wxSize(200, -1));

        wxTextCtrl *buscar= new wxTextCtrl(panel, wxID_ANY, "",
                                           wxPoint(900, 60), wxSize(200, -1));

        /*wxImage image("/home/dell/Escritorio/play.png",wxBITMAP_TYPE_PNG);
        if (!image.IsOk()){
            wxMessageBox("mamaste");
            return;
        }

        wxBitmap bitmap(image);
        image.Rescale(100, 50);
        wxBitmapButton* boton = new wxBitmapButton(this,wxID_ANY,bitmap,wxPoint(150,750));*/
    }

private:
    void PaginacionActionButton(wxCommandEvent &event) {
        if (servidor.paginacion == true){
            servidor.paginacion = false;
            caja->SetValue("Paginacion desactivada");

        }else{
            servidor.paginacion = true;
            caja->SetValue("Paginacion Activada");
        }
    }
    void ComunitarioActionButton(wxCommandEvent &event) {
        if (!active_playlist){
            caja->SetValue("PLaylist Activada");
            // Crear un hilo que ejecute la función en segundo plano
            thread ServerThread(&MainFrame::activeServer, this);
            // Hacer que el hilo sea independiente del hilo principal (no bloquear)
            ServerThread.detach();
            active_playlist = true;
        }
        else {
            cout << "Servidor activo" << endl;
        }

    }

    void activeServer() {
        thread hilo(&ServerSocket::acceptConnections, &servidor);
        cout << "Servidor en escucha" << endl;
        hilo.join();

    }
    wxTextCtrl *caja;
    //wxDECLARE_EVENT_TABLE();
};

/*wxBEGIN_EVENT_TABLE(MainFrame,wxFrame)
                EVT_BUTTON(botonID,MainFrame::OnButtonClick)
wxEND_EVENT_TABLE()*/

class MyApp: public wxApp{
public:
    virtual bool OnInit() override{
        MainFrame *frame = new MainFrame("Spotify");
        frame->Show(true);
        return true;
    }
};


int main(int argc, char* argv[]) {

    //Lee las canciones de la carpeta y las guarda en la lista
    servidor.lista_enlazada.leerArchivosMP3("/home/spaceba/Music", servidor.carpeta_de_canciones);
    //Crea la lista con las canciones leidas del archivo
    servidor.create_list_from_file();
    //Escribe la lista en Disco
    servidor.lista_enlazada.List_to_Array();
    //Crea un array de cnaciones del tamanno de la cantidad de canciones de la carpeta
    Cancion* canciones = new Cancion[array_de_canciones.largo];

    array_de_canciones.get_songs(canciones);

    for (int i = 0; i < array_de_canciones.largo; ++i) {
        cout << "Canción #" << i+1 << ":" << endl;
        cout << "ID: " << canciones[i].id << endl;
        cout << "Nombre: " << canciones[i].nombre << endl;
        cout << "Artista: " << canciones[i].artista << endl;
        cout << "Duración Minutos: " << canciones[i].duracion_minutos << " minutos" << endl;
        cout << "Duración Segundos: " << canciones[i].duracion_segundos << endl;
        cout << "Votos: " << canciones[i].votes << endl;
        cout << endl;
    }

    //Cancion cancion_1 = array_de_canciones[2];
    //cout << cancion_1.nombre << endl;


    wxApp::SetInstance(new MyApp());
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();

    // Inicializar GStreamer
    gst_init(&argc, &argv);

    // Crear un nuevo pipeline
    GstElement *pipeline = gst_pipeline_new("audio-player");

    // Crear los elementos necesarios
    GstElement *source = gst_element_factory_make("filesrc", "file-source");
    GstElement *decoder = gst_element_factory_make("decodebin", "decoder");
    GstElement *sink = gst_element_factory_make("autoaudiosink", "audio-output");

    if (!pipeline || !source || !decoder || !sink) {
        std::cerr << "Error al crear los elementos." << std::endl;
        return -1;
    }

    // Establecer el archivo fuente
    g_object_set(source, "location",
                 "/home/spaceba/Music/Bad Bunny - Moscow Mule.mp3", NULL);

    // Añadir los elementos al pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, decoder, sink, NULL);

    // Conectar los elementos
    gst_element_link(source, decoder);
    gst_element_link(decoder, sink);

    // Iniciar la reproducción
    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
        std::cerr << "Error al iniciar la reproducción." << std::endl;
        return -1;
    }



    // Nombre del archivo binario en el que deseas escribir
    string filename = "/home/spaceba/CLionProjects/Server/archivo.bin";

    //add_to_end(cancion1, filename);
    //add_to_end(cancion2, filename);
    //add_to_end(cancion3, filename);

    //Cancion busqueda = search_by_index(3, filename);
    /*
    Cancion canciones[10];
    Cancion* lista = get_songs(filename, canciones);

    for (int i = 0; i < 3; ++i) {
        cout << "Canción #" << i+1 << ":" << endl;
        cout << "Nombre: " << lista[i].nombre << endl;
        cout << "Artista: " << lista[i].artista << endl;
        cout << "Duración Minutos: " << lista[i].duracion_minutos << " minutos" << endl;
        cout << "Duración Segundos: " << lista[i].duracion_segundos << endl;
        cout << endl;
    }
     */

    return 0;

}
