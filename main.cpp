#include <iostream>
#include <wx/wx.h>
#include <string>
#include "ServerSocket.h"
#include "thread"
#include "Circular List.cpp"
#include "BinaryListOperations.cpp"
#include "Metadata.cpp"
#include "DoubleList.h"

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
        caja->SetValue("Hola");
        cout<<"Presionado"<<endl;
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

    void activeServer() {
        int portNumber = 12346; // Puerto en el que escuchará el servidor
        ServerSocket servidor = ServerSocket(portNumber, lista_de_canciones);
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
    leerArchivosMP3("/home/dell/Escritorio/Musica", lista_canciones);

    //Recorre los datos obtenidos de la carpeta y crea una lista enlazada
    Data* temp = lista_canciones;
    while (temp) {
        lista_de_canciones.insert_lastdouble(*temp);
            temp = temp->siguiente;
    }
    lista_de_canciones.printListadouble();


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
