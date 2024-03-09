#include <iostream>

#include <wx/wx.h>

enum IDs{
    botonID =2,textoID=3
};

using namespace std;
class MainFrame : public wxFrame {
public:
    MainFrame(const wxString &title)
            : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition,
                      wxSize(800, 600)) {

        wxPanel *panel = new wxPanel(this, wxID_ANY);

        wxButton *button = new wxButton(panel, botonID, "Presione",
                                        wxPoint(150, 50), wxSize(100, 40));
        button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClick, this);

        wxStaticText *text = new wxStaticText(panel, wxID_ANY, "Pruebas",
                                              wxPoint(450, 150));
        text->SetForegroundColour(wxColour(0, 0, 0));

        caja = new wxTextCtrl(panel, textoID, "",
                                          wxPoint(350, 50), wxSize(200, -1));
    }

private:
    void OnButtonClick(wxCommandEvent &event) {
        caja->SetValue("Hola");
        cout<<"Presionado"<<endl;
    }
    wxTextCtrl *caja;
    wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MainFrame,wxFrame)
                EVT_BUTTON(botonID,MainFrame::OnButtonClick)
wxEND_EVENT_TABLE()

class MyApp: public wxApp{
public:
    virtual bool OnInit() override{
        MainFrame *frame = new MainFrame("Ventana sencilla");
        frame->Show(true);
        return true;
    }
};
wxIMPLEMENT_APP(MyApp);