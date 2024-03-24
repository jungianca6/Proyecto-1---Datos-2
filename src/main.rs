
use fltk::{app, button, input, prelude::{WidgetBase, WidgetExt, GroupExt}, window};
use fltk::prelude::InputExt;
use fltk_theme::{ColorTheme, color_themes};
use std::net::{TcpStream, Shutdown};
use std::io::{Read, Write};
use std::thread::sleep;
use serde_json::json;
use std::{mem, time};
use std::thread;
use std::time::Duration;


struct ClientSocket {
    stream: TcpStream,
}

impl ClientSocket{
    //Constructor del CLiente
    pub fn new(address: &str) -> Self{
        //Crea la conexion con la direccion especificada
        match TcpStream::connect(address) {
            //Si la coneccion es existosa crea una instancia del cliente
            Ok(stream) => ClientSocket { stream },
            //Detiene el programa si la conexion no es posible
            Err(e) => panic!("Error al conectar: {}", e),
        }
    }
    //Funcion que envia el mensaje json a traves del socket
    pub fn send_json(&mut self, data: serde_json::Value) -> std::io::Result<()> {
        //Declara una variable para guardar el resultado de la serializacion json
        let json_string = serde_json::to_string(&data).expect("Error al serializar JSON");
        //Envia el mensaje por el socket
        self.stream.write_all(json_string.as_bytes())?;
        Ok(())
    }
    //Funcion que recibe el mensaje a traves del socket
    pub fn receive_message(&mut self) -> std::io::Result<String> {
        //Declara el buffer donde se guardara el mensaje entrante del socket
        let mut buffer = [0; 4096];
        //Lee el mensaje proveniente del socket
        let bytes_read = self.stream.read(&mut buffer)?;
        //Convierte el mensaje recibido en un string
        let message = String::from_utf8_lossy(&buffer[..bytes_read]).to_string();
        Ok(message)
    }
}

//Funcion que pide al servidor la lista de canciones
fn request_song_list(){
        let mut client = ClientSocket::new("127.0.0.1:12346");
        //Crea objeto JSON
        let data = json!({"command": "Get-Playlist"});
        //Envia JSON al servidor
        client.send_json(data).expect("Error al enviar JSON");
        //Recibir respuesta del servidor
        let received_message = client.receive_message().expect("Error al recibir mensaje");
        println!("Mensaje recibido del servidor: {}", received_message);
        //Cerrar la conexión
        client.stream.shutdown(Shutdown::Both).expect("Error al cerrar conexión");
        //Cerrar la conexión
        mem::drop(client);
}

//Funcion que envia la votacion al servidor
fn vote_song(id: &str, command: &str){
        let mut client = ClientSocket::new("127.0.0.1:12346");
        let data = json!({"command": command, "id": id});
        //Envia JSON al servidor
        client.send_json(data).expect("Error al enviar JSON");
        //Recibir respuesta del servidor
        let received_message = client.receive_message().expect("Error al recibir mensaje");
        println!("Mensaje recibido del servidor: {}", received_message);
        //Cerrar la conexión
        client.stream.shutdown(Shutdown::Both).expect("Error al cerrar conexión");
        //ELimina la instancia del objeto
        mem::drop(client);
}

fn request_songs(){
    let delay = 1;
    println!("Llego aqui");
    //Crea una instancia del objeto cliente por la direccion especificada
    let hilo = thread::spawn(move || request_song_list());
    let hilo2 = thread::spawn(move || vote_song("123456","Vote-down"));
    hilo.join();
    hilo2.join();
}

fn main() {
    let a = app::App::default().with_scheme(app::Scheme::Gtk);
    let theme = ColorTheme::new(color_themes::BLACK_THEME);
    theme.apply();
    let mut win = window::Window::default().with_size(600, 400)
        .with_label("prueba");
    let mut btn = button::Button::new(160, 200, 80, 40, "Presione");
    let mut text = input::Input::new(160, 100, 200, 50, "");
    btn.set_color(btn.color().lighter());
    win.end();
    win.show();

    btn.set_callback(move |b| {
        request_songs();
        text.set_value("Peticion enviada");
    });

    a.run().unwrap();
}