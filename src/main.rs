
use fltk::{app, button, input, prelude::{WidgetBase, WidgetExt, GroupExt}, window};
use fltk::prelude::InputExt;
use fltk_theme::{ColorTheme, color_themes};


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
        text.set_value("Hola");
    });

    a.run().unwrap();
}