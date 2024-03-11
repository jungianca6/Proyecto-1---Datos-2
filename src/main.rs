use iced::{Element, Sandbox, Settings, Theme};
use iced::widget::{container, text_editor};
use iced::widget::Button;

fn main() ->iced::Result{
    Editor::run(Settings::default())
}
struct Editor{
    content: text_editor::Content
}
#[derive(Debug,Clone)]
enum Message{
    Edit(text_editor::Action)
}

impl Sandbox for Editor{
    type Message = Message;

    fn new() -> Self {
        Self{
            content: text_editor::Content::new(),
        }
    }
    //titulo ventana
    fn title(&self) -> String {
        String::from("Prueba")
    }
    //actualizacion de la interfaz
    fn update(&mut self, message: Message) {
        match message{
            Message::Edit(action) =>{
                self.content.edit(action)
            }
        }
    }
    //widgets
    fn view(&self) -> Element<'_, Message> {
        let input = text_editor(&self.content).on_edit(Message::Edit);
        container(input).padding(200).into()
    }
    fn theme(&self) -> Theme {
        Theme::Dark
    }
}