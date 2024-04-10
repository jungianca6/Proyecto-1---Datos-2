#include <iostream>
#include <wx/wx.h>
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "Circular List.cpp"
#include "BinaryListOperations.cpp"
#include "Metadata.cpp"
#include "DoubleList.h"
#include <ogg/ogg.h>
#include <gst/gst.h>



//Lista de canciones recogidas de los archivos
Data* lista_canciones;
//Lista enlazada con los nodos
DoubleList lista_de_canciones;

enum IDs{
    botonID =2,textoID=3
};

using namespace std;
using namespace TagLib;
namespace fs = std::filesystem;namespace fs = std::filesystem;

//clase que crea la ventana
class MainFrame : public wxFrame {
private:
    GstElement *pipeline;
public:
    bool active_playlist = false;

    MainFrame(const wxString &title)
            : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition,
                      wxSize(1200, 900)) {

        wxPanel *panel = new wxPanel(this, wxID_ANY);
        panel->SetBackgroundColour(wxColour(9,129, 53));


        wxButton *paginacion, *comunitario, *buscarCancion,*reproduccion,*pausa,
        *anterior,*siguiente,*eliminar, *pruebacancion;

        wxString canciones[] ={"Cancion 1", "Cancion 2", "Cancion 3"};

        listaCanciones = new wxComboBox(panel, wxID_ANY, canciones[0],
                                                     wxPoint(450,250), wxSize(150,60), WXSIZEOF(canciones),
                                                     canciones,wxCB_READONLY);


        paginacion = new wxButton(panel, botonID, "Paginacion",
                                  wxPoint(150, 50), wxSize(150, 60));
        paginacion->Bind(wxEVT_BUTTON, &MainFrame::PaginacionActionButton, this);

        comunitario = new wxButton(panel, botonID, "Playlist comunitario",
                                   wxPoint(150, 250), wxSize(250, 60));
        comunitario->Bind(wxEVT_BUTTON, &MainFrame::ComunitarioActionButton, this);

        pruebacancion = new wxButton(panel, botonID, "Prueba cancion",
                                                  wxPoint(650, 250), wxSize(200, 35));
        pruebacancion->Bind(wxEVT_BUTTON, &MainFrame::escogerCancion,this);
        buscarCancion = new wxButton(panel, botonID, "Buscar",
                                     wxPoint(950, 110), wxSize(125, 30));

        reproduccion = new wxButton(panel, botonID, "Reproducir",
                                    wxPoint(300, 500), wxSize(125, 40));
        pausa= new wxButton(panel, botonID, "Pausar",
                            wxPoint(450, 500), wxSize(125, 40));
        pausa->Bind(wxEVT_BUTTON, &MainFrame::Pausa, this);
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
        prueba = new wxTextCtrl(panel, wxID_ANY,"",
                                wxPoint(450,350),wxSize(200,-1));

        wxTextCtrl *buscar= new wxTextCtrl(panel, wxID_ANY, "",
                                           wxPoint(900, 60), wxSize(200, -1));
    }

private:
    void PaginacionActionButton(wxCommandEvent &event) {
        caja->SetValue("Hola");
        cout << "Presionado" << endl;

        // Crear un nuevo pipeline si es necesario
        if (!pipeline) {
            pipeline = gst_pipeline_new("audio-player");

            // Crear los elementos necesarios
            GstElement *source = gst_element_factory_make("filesrc", "file-source");
            GstElement *parse = gst_element_factory_make("mpegaudioparse", "mp3-parser");
            GstElement *decoder = gst_element_factory_make("mpg123audiodec", "mp3-decoder");
            GstElement *volume = gst_element_factory_make("volume", "volume-name");
            GstElement *converter = gst_element_factory_make("audioconvert", "audio-converter");
            GstElement *resample = gst_element_factory_make("audioresample", "audio-resampler");
            GstElement *sink = gst_element_factory_make("autoaudiosink", "audio-output");

            if (!pipeline || !source || !parse || !decoder || !volume || !converter || !resample || !sink) {
                std::cerr << "Error al crear los elementos." << std::endl;
            } else {
                // Establecer el archivo fuente
                g_object_set(G_OBJECT(source), "location",
                             "/home/dell/Escritorio/Musica/Who Can It Be Now.mp3", NULL);
                cout << "Musica encontrada" << endl;

                // Añadir los elementos al pipeline
                gst_bin_add_many(GST_BIN(pipeline), source, parse, decoder, converter, resample, sink, NULL);

                cout << "Elementos añadidos" << endl;

                if (!gst_element_link_many(source, parse, decoder, converter, resample, sink, NULL)) {
                    std::cerr << "Error al enlazar los elementos." << std::endl;
                    gst_object_unref(pipeline);
                    pipeline = nullptr;  // Establecer pipeline a nullptr si hay un error
                } else {
                    // Iniciar la reproducción
                    GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
                    if (ret == GST_STATE_CHANGE_FAILURE) {
                        std::cerr << "Error al iniciar la reproducción." << std::endl;
                    } else {
                        cout << "Reproduccion" << endl;
                    }
                }
            }
        } else {
            // El pipeline ya está creado, así que solo reinicia la reproducción
            GstStateChangeReturn ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
            if (ret == GST_STATE_CHANGE_FAILURE) {
                std::cerr << "Error al reiniciar la reproducción." << std::endl;
            } else {
                cout << "Reproduccion reiniciada" << endl;
            }
        }
    }

    void Pausa (wxCommandEvent &event){
        gst_element_set_state(pipeline, GST_STATE_PAUSED);
    }
    void ComunitarioActionButton(wxCommandEvent &event) {
        if (!active_playlist){
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

    void escogerCancion (wxCommandEvent &event){
        prueba->SetValue(listaCanciones->GetStringSelection());
    }

    void activeServer() {
        int portNumber = 12346; // Puerto en el que escuchará el servidor
        ServerSocket servidor = ServerSocket(portNumber, &lista_de_canciones);
        thread hilo(&ServerSocket::acceptConnections, &servidor);
        cout << "Servidor en escucha" << endl;
        hilo.join();

    }
    wxTextCtrl *caja;
    wxTextCtrl *prueba;
    wxComboBox * listaCanciones;

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
    // Inicializar GStreamer
    gst_init(&argc, &argv);

    //Lee las canciones de la carpeta y las guarda en la lista
    leerArchivosMP3("/home/dell/Escritorio/Musica", lista_canciones);

    //Recorre los datos obtenidos de la carpeta y crea una lista enlazada
    Data* temp = lista_canciones;
    while (temp) {
        lista_de_canciones.insert_lastdouble(*temp);
            temp = temp->siguiente;
    }
    //lista_de_canciones.printListadouble();


    wxApp::SetInstance(new MyApp());
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();



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
