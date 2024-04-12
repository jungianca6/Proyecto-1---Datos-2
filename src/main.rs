use fltk::{app, button, input, prelude::{WidgetBase, WidgetExt, GroupExt}, window};
use fltk::prelude::{InputExt, MenuExt};
use fltk_theme::{ColorTheme, color_themes};
use std::net::{TcpStream, Shutdown};
use std::io::{Read, Write};
use std::thread::sleep;
use serde_json::{json, Value};
use std::{fs, mem, time};
use std::thread;
use std::time::Duration;
use serde::{Deserialize, Serialize};
use std::fmt;
use std::fs::File;
use std::io::BufReader;
use std::sync::{Arc, mpsc};
use std::sync::mpsc::Sender;
use tokio::time::{sleep as tokio_sleep, interval};
use log::{info, warn, error};

extern crate ini;
use config::Config;
use fltk::button::Button;
use fltk::enums::Color;
use fltk::group::Pack;
use fltk::menu::Choice;
use fltk::window::Window;
use tokio::runtime::Runtime;

// Definir la estructura de datos para cada canción
#[derive(Debug, Serialize, Deserialize, Clone)]
struct Song {
    id: String,
    album: String,
    artista: String,
    duracion_minutos: u32,
    duracion_segundos: u32,
    nombre: String,
    votes: i32,
}

// Definir la estructura del nodo de la lista enlazada
#[derive(Debug)]
struct ListNode {
    song: Song,
    next: Option<Box<ListNode>>,
}

impl ListNode {
    fn new(song: Song) -> Self {
        ListNode {
            song: song,
            next: None,
        }
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
fn request_song_list() -> Vec<Song>{
        let mut settings = Config::default();
        settings.merge(config::File::with_name("/home/spaceba/CLionProjects/Client/src/config.ini")).unwrap();

        let ip = settings.get::<String>("Servidor.IP").unwrap();
        let puerto = settings.get::<i32>("Servidor.Puerto").unwrap();
        // Crea la dirección de conexión combinando la IP y el Puerto
        let direccion = format!("{}:{}", ip, puerto);

        let mut client = ClientSocket::new(&direccion);
        //Crea objeto JSON
        let data = json!({"command": "Get-Playlist"});
        //Envia JSON al servidor
        client.send_json(data).expect("Error al enviar JSON");
        //Recibir respuesta del servidor
        let received_message = client.receive_message().expect("Error al recibir mensaje");
        //Obtiene el mensaje contenido en la etiqueta lista
        let songs_list_str = received_message["list"].as_str().unwrap_or("Mensaje no encontrado");

        // Analizar el JSON recibido
        let songs: Vec<Song> = serde_json::from_str(&songs_list_str).unwrap();
        //Cerrar la conexión
        client.stream.shutdown(Shutdown::Both).expect("Error al cerrar conexión");
        //Cerrar la conexión
        mem::drop(client);
        //Devuelve la lista de canciones
        return songs
}

//Funcion que envia la votacion al servidor
fn vote_song(nombre: &str, command: &str){

        let mut settings = Config::default();
        settings.merge(config::File::with_name("/home/spaceba/CLionProjects/Client/src/config.ini")).unwrap();

        let ip = settings.get::<String>("Servidor.IP").unwrap();
        let puerto = settings.get::<i32>("Servidor.Puerto").unwrap();
        // Crea la dirección de conexión combinando la IP y el Puerto
        let direccion = format!("{}:{}", ip, puerto);

        let mut client = ClientSocket::new(&direccion);
        let data = json!({"command": command, "nombre": nombre});
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

fn request_songs() -> Vec<Song>{
    let hilo = thread::spawn(move || request_song_list());
    let canciones = hilo.join().unwrap(); // Espera a que el hilo termine y obtiene el resultado
    return canciones;
}

fn vote_up(variable: &str) {
    let variable_ref = variable.to_owned(); // Clonar el valor al que variable hace referencia
    let vote_up_thread = thread::spawn(move || vote_song(&variable_ref, "Vote-up"));
    vote_up_thread.join().unwrap();
}

fn vote_down(variable: &str) {
    let variable_ref = variable.to_owned(); // Clonar el valor al que variable hace referencia
    let vote_down_thread = thread::spawn(move || vote_song(&variable_ref, "Vote-down"));
    vote_down_thread.join().unwrap();
}

async fn periodic_task(interval_seconds: u64, sender: mpsc::Sender<Vec<Song>>) {
    let mut interval = interval(Duration::from_secs(interval_seconds));
    loop {
        interval.tick().await;
        println!("Realizando Polling....");
        // Simulación de obtención de la lista de canciones
        let songs_list = request_songs();
        // Enviar el resultado a través del canal
        sender.send(songs_list).unwrap();
    }
}


#[tokio::main]
async fn main() {
    let a = app::App::default().with_scheme(app::Scheme::Gtk);
    // Crear un Pack para organizar los elementos
    let theme = ColorTheme::new(color_themes::BLACK_THEME);
    theme.apply();
    let mut win = window::Window::default().with_size(400, 300)
        .with_label("Community Music Player :v");
    let mut vote_up_button = button::Button::new(50, 50, 120, 60, "Vote-up");
    let mut vote_down_button = button::Button::new(220, 50, 120, 60, "Vote-down");
    vote_up_button.set_color(vote_up_button.color().lighter());
    vote_down_button.set_color(vote_up_button.color().lighter());

    // Crear un menú desplegable
    let mut menu_button = Choice::new(150, 150, 200, 30, "Seleccionar opción");

    let mut settings = Config::default();
    settings.merge(config::File::with_name("/home/spaceba/CLionProjects/Client/src/config.ini")).unwrap();
    let cooldown = settings.get::<u64>("Servidor.Cooldown").unwrap();

    // Crear un canal para comunicarse entre los hilos
    let (sender, receiver) = mpsc::channel::<Vec<Song>>();

    // Clonar el sender para moverlo al contexto del hilo
    let sender_clone = sender.clone();

    // Ejecutar la tarea periódicamente en un hilo secundario
    tokio::spawn(async move {
        periodic_task(cooldown, sender_clone).await;

    });

    // Esperar a que se reciba el resultado del canal
    let songs_list = receiver.recv().unwrap();
    // Imprimir el contenido de songs_list
    println!("Lista de canciones recibida:");


    // Recibir actualizaciones de la lista de canciones y actualizar el menú desplegable
    for song in &songs_list {
        menu_button.add_choice(&song.nombre);

    }




    let menu_button_clone = menu_button.clone();
    vote_down_button.set_callback(move |_| {
        // Obtener el texto del elemento seleccionado utilizando el índice
        let selected_index = menu_button_clone.value();
        let selected_text = menu_button_clone.text(selected_index).unwrap_or_default();
        let variable = selected_text.as_str();
        vote_down(variable);
    });

    let menu_button_clone = menu_button.clone();
    vote_up_button.set_callback(move |_| {
        // Obtener el texto del elemento seleccionado utilizando el índice
        let selected_index = menu_button_clone.value();
        let selected_text = menu_button_clone.text(selected_index).unwrap_or_default();
        let variable = selected_text.as_str();
        vote_up(variable);
    });


    win.end();
    win.show();
    a.run().unwrap();



}