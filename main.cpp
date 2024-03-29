#include <iostream>
#include <wx/wx.h>

enum IDs{
    botonID =2,textoID=3
};

#include "ServerSocket.h"
#include "thread"
#include "chrono"
#include <stdio.h>
#include <filesystem>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/mpegfile.h>
#include <taglib/mpegheader.h>
#include "Circular List.cpp"
#include "Double List.cpp"
#include "Metadata.cpp"
#include "BinaryListOperations.cpp"

// g++ obtener_metadatos_wav.cpp -o obtener_metadatos_wav -I/ruta/a/taglib/include/taglib -L/ruta/a/taglib/lib -ltag -Wl,-rpath=/ruta/a/taglib/lib

using namespace std;
using namespace TagLib;
namespace fs = std::filesystem;namespace fs = std::filesystem;

/*
class MainFrame : public wxFrame {
public:
    MainFrame(const wxString &title)
            : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition,
                      wxSize(1200, 900)) {

        wxPanel *panel = new wxPanel(this, wxID_ANY);
        panel->SetBackgroundColour(wxColour(9,129, 53));

        wxButton *paginacion, *comunitario, *buscarCancion,*reproduccion,*pausa;

        paginacion = new wxButton(panel, botonID, "Paginacion",
                                  wxPoint(150, 50), wxSize(150, 60));
        paginacion->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this);

        comunitario = new wxButton(panel, botonID, "Playlist comunitario",
                                   wxPoint(150, 250), wxSize(250, 60));

        buscarCancion = new wxButton(panel, botonID, "Buscar",
                                     wxPoint(950, 110), wxSize(125, 30));

        reproduccion = new wxButton(panel, botonID, "Reproducir",
                                    wxPoint(300, 600), wxSize(125, 40));
        pausa= new wxButton(panel, botonID, "Pausar",
                            wxPoint(450, 600), wxSize(125, 40));

        wxSlider *volumen = new wxSlider(panel,wxID_ANY,50,0,100,
                                         wxPoint(650,600),wxSize(200,-1));



        wxStaticText *cancion, *busqueda;
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

/*

    }


private:
    void OnButtonClick(wxCommandEvent &event) {
        caja->SetValue("Hola");
        cout<<"Presionado"<<endl;
    }
    wxTextCtrl *caja;
    //wxDECLARE_EVENT_TABLE();
};

/*wxBEGIN_EVENT_TABLE(MainFrame,wxFrame)
                EVT_BUTTON(botonID,MainFrame::OnButtonClick)
wxEND_EVENT_TABLE()*/

/*

class MyApp: public wxApp{
public:
    virtual bool OnInit() override{
        MainFrame *frame = new MainFrame("Spotify");
        frame->Show(true);
        return true;
    }
};

*/

int main(int argc, char* argv[]) {


    Data* lista_canciones = nullptr;
    string ruta_carpeta = "/home/darga19/Documents/Tec/Algoritmos y Estructuras de Datos II/Música proyecto I";
    leerArchivosMP3(ruta_carpeta, lista_canciones);

    print_lista(lista_canciones);

    // Ejemplo para usar el buscar_nodo(), en la lista de canciones
    /*
    Data* cancion_buscada = buscar_nodo(lista_canciones, "Nombre de la Canción");
    if (cancion_buscada) {
        cout << "Canción encontrada: " << cancion_buscada->nombre << endl;
    } else {
        cout << "La canción no se encontró en la lista." << endl;
    */


    wxApp::SetInstance(new MyApp());
    wxEntryStart(argc, argv);
    wxTheApp->OnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
    int portNumber = 12346; // Puerto en el que escuchará el servidor
    ServerSocket servidor = ServerSocket(portNumber);
    thread hilo(&ServerSocket::acceptConnections, &servidor);

    // Datos que deseas escribir en el archivo
    Cancion cancion = {"Creo-B", "Mario", 300,3};

    // Nombre del archivo binario en el que deseas escribir
    string filename = "/home/spaceba/CLionProjects/Server/archivo.bin";

    //add_to_end(cancion, filename);
    Cancion busqueda = search_by_index(3, filename);

    // Array para almacenar todas las personas del archivo, es static para que permanezca
    Cancion canciones[10];
    Cancion* lista = get_songs(filename, canciones);

    // Mostrar los datos de todas las personas almacenadas
    for (int i = 0; i < 10; ++i) {
        cout << "Persona " << i+1 << ":" << endl;
        cout << "Nombre: " << lista[i].nombre << endl;
        cout << "Edad: " << lista[i].artista << endl;
        cout << "Altura: " << lista[i].id << endl;
        cout << "Altura: " << lista[i].duracion << endl;
        cout << endl;
    }


/*
//g++ main.cpp -o main -I/usr/include/taglib/include/taglib -L/usr/include/taglib/lib -ltag -Wl,-rpath=usr/include/taglib/lib
    int opcion_menu=0;
    ListaDoble lista;
    string nombreCancion;
    string nodoBuscado;
    do{
        cout << "\n|---------------------------------------|";
        cout << "\n|        ° LISTA CIRCULAR DOBLE °       |";
        cout << "\n|--------------------|------------------|";
        cout << "\n| 1. Insertar final  | 5. Print         |";
        cout << "\n| 2. Insertar inicio | 6. Array         |";
        cout << "\n| 3. Buscar          |                  |";
        cout << "\n| 4. Eliminar        |                  |";
        cout << "\n|--------------------|------------------|";
        cout << "\n\n Escoja una Opcion: ";
        cin >> opcion_menu;
        switch(opcion_menu){
            case 1:
                cout << "\n Inserta un nodo en la lista (ultimo): ";
                cin >> nombreCancion;
                lista.insert_lastdouble(nombreCancion);
                break;
            case 2:
                cout << "\n Inserta un nodo en la lista (primero): ";
                cin >> nombreCancion;
                lista.insert_firstdouble(nombreCancion);
                break;
            case 3:
                cout << "\n Inserta el nodo que quieras buscar: ";
                cin >> nodoBuscado;
                lista.buscarNododouble(nodoBuscado);
                break;
            case 4:
                cout << "\n Inserta el nodo que quieras eliminar: ";
                cin >> nodoBuscado;
                lista.eliminarNododouble(nodoBuscado);
                break;
            case 5:
                cout << "\n Lista printeada:\n";
                lista.printListadouble();
                break;
            case 6:
                cout << "\n Convertido en array:\n";
                lista.convertArraydouble();
                break;
            default:
                cout << "\n Opcion no valida\n";
                break;
        }
    } while (opcion_menu != 7);
        //hilo.join();
*/
    return 0;
}