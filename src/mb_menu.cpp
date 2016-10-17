#include "mb_menu.h"

MBMenu::MBMenu(const string &current_level, const string& next_level, const string audio_path, int){
}

MBMenu::MBMenu(int r, int g, int b, const string &current, const string&, const string&){
	video::set_full_screen(1);

    m_r = r;
    m_g = g;
    m_b = b;
    m_current_level = current;
    m_start = -1;
    m_done = false;
    m_background = resources::get_texture("menu/background.png");

    m_buttons.clear();

    m_buttons.push_back(new MBButton("Iniciar", "iniciar", m_current_level, "btn_background.png", 433, 220, 500, 112));
    m_buttons.push_back(new MBButton("Opções", "opcoes", m_current_level, "btn_background.png", 433, m_buttons[0]->y() + m_buttons[0]->h() + 20, 500, 112));
    m_buttons.push_back(new MBButton("Créditos", "creditos", m_current_level, "btn_background.png", 433, m_buttons[1]->y() + m_buttons[1]->h() + 20, 500, 112));
    m_buttons.push_back(new MBButton("Sair", "sair", m_current_level, "btn_background.png", 433, m_buttons[2]->y() + m_buttons[2]->h() + 20, 500, 112));

    for(auto btn : m_buttons)
        add_child(btn);

    event::register_listener(this);
}


MBMenu::~MBMenu(){
    event::unregister_listener(this);
}

bool MBMenu::done() const{
    return m_done;
}

string MBMenu::next() const{
    return m_next;
}

string MBMenu::audio() const{
    return m_audio;
}

void MBMenu::do_action(string label){
    if(label == "iniciar"){
        m_next = "1";
        m_done = true;
    }
    if(label == "opcoes"){

    }
    if(label == "creditos"){

    }
    if(label == "sair"){
        exit(0);
    }
}

bool MBMenu::on_event(const GameEvent&){
    return false;
}

void MBMenu::update_self(unsigned, unsigned){
}

void MBMenu::draw_self(Canvas *canvas, unsigned, unsigned){
    canvas->clear();
    canvas->set_clear_color(Color(m_r, m_g, m_b));

    if(m_background)
        canvas->draw(m_background.get(), 0, 0);

    auto font = resources::get_font("Aller_Bd.ttf", 80);
    canvas->set_font(font);
    canvas->set_draw_color(Color(255, 255, 255));

    canvas->draw("Simuladores EA / GA", 350, 50);
}
