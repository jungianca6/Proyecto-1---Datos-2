#include <iostream>
#include <wx/wx.h>
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "Circular List.cpp"
#include "DoubleList.h"
#include <gst/gst.h>
#include "Admin_paginas.h"
#include "Paged_Array.h"
#include <unistd.h> // Para sleep()
#include <glog/logging.h> //sudo apt-get install libgoogle-glog-dev

ServerSocket servidor = ServerSocket();

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
        panel->SetBackgroundColour(wxColour(100,100, 100));

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
        reproduccion->Bind(wxEVT_BUTTON, &MainFrame::ReproducirActionButton, this);

        pausa= new wxButton(panel, botonID, "Pausar",
                            wxPoint(450, 500), wxSize(125, 40));
        pausa->Bind(wxEVT_BUTTON, &MainFrame::PausarActionButton, this);
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
        if (servidor.paginacion == true){
            servidor.paginacion = false;
            servidor.lista_enlazada.create_list_from_file();
            caja->SetValue("Paginacion desactivada");
            LOG(INFO) << "Paginacion Desactivada";

        }else{
            servidor.lista_enlazada.List_to_Array();
            servidor.lista_enlazada.clear();
            servidor.paginacion = true;
            caja->SetValue("Paginacion Activada");
            LOG(INFO) << "Paginacion Activada";
        }

    }
    void ComunitarioActionButton(wxCommandEvent &event) {
        if (!servidor.active_playlist){
            // Crear un hilo que ejecute la función en segundo plano
            thread ServerThread(&MainFrame::activeServer, this);
            // Hacer que el hilo sea independiente del hilo principal (no bloquear)
            ServerThread.detach();
            servidor.active_playlist = true;
            LOG(INFO) << "Playlist comunitario activado";
        }
        else {
            servidor.active_playlist = false;
            LOG(INFO) << "Playlist comunitario desactivado";
            cout << "Servidor activo" << endl;
        }
    }
    void ReproducirActionButton(wxCommandEvent &event) {
        if (servidor.paginacion == true){
            servidor.lista_enlazada.play_song(true);
            LOG(INFO) << "Reproduciendo cancion";

        }else{
            servidor.lista_enlazada.play_song(false);
            LOG(INFO) << "Reproduciendo cancion";
        }
    }

    void escogerCancion (wxCommandEvent &event){
        prueba->SetValue(listaCanciones->GetStringSelection());
    }

    void activeServer() {
        thread hilo(&ServerSocket::acceptConnections, &servidor);
        LOG(INFO) << "Servidor en escucha.";
        cout << "Servidor en escucha" << endl;
        hilo.join();

    }
    void PausarActionButton(wxCommandEvent &event){
        servidor.lista_enlazada.Pausa();
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


// Función para obtener el consumo de memoria en tiempo real
size_t getMemoryUsage() {
    std::ifstream stat_stream("/proc/self/statm");
    size_t mem_usage = 0;
    if (stat_stream.is_open()) {
        stat_stream >> mem_usage;
        stat_stream.close();
    }
    return mem_usage * getpagesize();
}

// Función que se ejecutará en el hilo
void consumo() {
    while (true) {
        size_t memoria = getMemoryUsage();
        cout << "Consumo de memoria: " << memoria << " bytes" << endl;
        this_thread::sleep_for(chrono::seconds(1)); // Esperar 1 segundo
    }
}




int main(int argc, char* argv[]) {

    google::InitGoogleLogging(argv[0]);

    // Crear un hilo que ejecute la función 'consumo'
    std::thread consumoThread(consumo);

    //Lee las canciones de la carpeta y las guarda en la lista
    servidor.lista_enlazada.leerArchivosMP3("/home/dell/Escritorio/Musica", servidor.carpeta_de_canciones);
    LOG(INFO) << "Carpeta de canciones leida";
    //Crea la lista con las canciones leidas del archivo
    servidor.create_list_from_file();
    LOG(INFO) << "Lista creada.";

    // Inicializar GStreamer
    gst_init(&argc, &argv);

    wxApp::SetInstance(new MyApp());
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();


    // Esperar a que el hilo termine (esto nunca sucederá porque el hilo se ejecuta en bucle infinito)
    consumoThread.join();




    return 0;
}
