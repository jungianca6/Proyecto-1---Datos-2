use fltk::{app, button, input, prelude::{WidgetBase, WidgetExt, GroupExt}, window};
use fltk::prelude::InputExt;
use fltk_theme::{ColorTheme, color_themes};
use std::net::{TcpStream, Shutdown};
use std::io::{Read, Write};
use std::thread::sleep;
use serde_json::{json, Value};
use std::{mem, time};
use std::thread;
use std::time::Duration;
use serde::{Deserialize, Serialize};
use std::fmt;

#[derive(Serialize, Deserialize, Debug)]
struct Data {
    nombre: String,
    artista: String,
    duracion: i32,
    id: i32,
}
#[derive(Serialize, Deserialize, Debug)]
// Definición del nodo de la lista
struct Nodo {
    data: Data,
    siguiente: Option<Box<Nodo>>,
}

impl Nodo {
    fn nuevo(data: Data) -> Self {
        Nodo {
            data,
            siguiente: None,
        }
    }
}
// Definición de la lista doblemente enlazada
#[derive(Serialize, Deserialize, Debug)]
struct ListaDoblementeEnlazada {
    cabeza: Option<Nodo>,
}

impl ListaDoblementeEnlazada {
    fn nueva() -> Self {
        ListaDoblementeEnlazada {
            cabeza: None,
        }
    }
    fn insert_last(&mut self, data: Data) {
        let mut nuevo_nodo = Box::new(Nodo::nuevo(data));

        // Si la lista está vacía, el nuevo nodo será la cabeza
        if self.cabeza.is_none() {
            self.cabeza = Some(*nuevo_nodo);
            return;
        }
        // Si no, buscamos el último nodo y lo enlazamos con el nuevo nodo
        let mut actual = self.cabeza.as_mut().unwrap();
        while let Some(ref mut siguiente) = actual.siguiente {
            actual = siguiente;
        }
        actual.siguiente = Some(nuevo_nodo);
    }

    fn Print(&mut self){
        // Si no, buscamos el último nodo y lo enlazamos con el nuevo nodo
        let mut actual = self.cabeza.as_mut().unwrap();
        while let Some(ref mut siguiente) = actual.siguiente {
            println!("Nombre: {}", actual.data.nombre);
            println!("Artista: {}", actual.data.artista);
            println!("ID: {}", actual.data.id);
            println!("Duracion: {}", actual.data.duracion);
            actual = siguiente;
        }
        println!("Nombre: {}", actual.data.nombre);
        println!("Artista: {}", actual.data.artista);
        println!("ID: {}", actual.data.id);
        println!("Duracion: {}", actual.data.duracion);
    }


}


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
    pub fn receive_message(&mut self) -> Result<serde_json::Value, Box<dyn std::error::Error>> {
        //Declara el buffer donde se guardara el mensaje entrante del socket
        let mut buffer = [0; 4096];
        //Lee el mensaje proveniente del socket
        let bytes_read = self.stream.read(&mut buffer)?;

        // Convertir los bytes leídos en una cadena de texto (&str)
        let str_buffer = std::str::from_utf8(&buffer[..bytes_read]).expect("Error al convertir bytes a cadena");

        // Analizar los datos como JSON
        let json_data: serde_json::Value = serde_json::from_str(str_buffer).expect("Error al analizar los datos JSON");

        Ok(json_data)
    }
}

//Funcion que pide al servidor la lista de canciones
fn request_song_list(){
        let mut client = ClientSocket::new("127.0.0.1:12345");
        //Crea objeto JSON
        let data = json!({"command": "Get-Playlist"});
        //Envia JSON al servidor
        client.send_json(data).expect("Error al enviar JSON");
        //Recibir respuesta del servidor
        let received_message = client.receive_message().expect("Error al recibir mensaje");

        let songs_list = received_message["list"].as_str().unwrap_or("Mensaje no encontrado");
        let mut json_lista: crate::ListaDoblementeEnlazada = serde_json::from_str(&songs_list).expect("Error al deserializar JSON");
        json_lista.Print();




        println!("Mensaje recibido del servidor: {}", songs_list);



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

fn request_songs() {
    let hilo = thread::spawn(move || request_song_list());
    hilo.join();
}

fn vote_up(){
    let vote_up_thread = thread::spawn(move || vote_song("123456","Vote-up"));
    vote_up_thread.join();
}

fn vote_down(){
    let vote_down_thread = thread::spawn(move || vote_song("123456","Vote-down"));
    vote_down_thread.join();
}

fn main() {
    let a = app::App::default().with_scheme(app::Scheme::Gtk);
    let theme = ColorTheme::new(color_themes::BLACK_THEME);
    theme.apply();
    let mut win = window::Window::default().with_size(600, 400)
        .with_label("prueba");
    let mut request_songs_button = button::Button::new(160, 200, 80, 40, "Canciones");
    let mut vote_up_button = button::Button::new(250, 200, 80, 40, "Vote-up");
    let mut vote_down_button = button::Button::new(340, 200, 80, 40, "Vote-down");
    let mut text = input::Input::new(160, 100, 200, 50, "");
    request_songs_button.set_color(request_songs_button.color().lighter());
    vote_up_button.set_color(request_songs_button.color().lighter());
    vote_down_button.set_color(request_songs_button.color().lighter());

    win.end();
    win.show();

    vote_down_button.set_callback(move |_| {
        vote_down();
    });

    vote_up_button.set_callback(move |_| {
        vote_up();
    });

    request_songs_button.set_callback(move |_| {
        request_songs();
    });

    a.run().unwrap();
}