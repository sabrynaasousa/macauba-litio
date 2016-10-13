#include "mb_menu.h"

MBMenu::MBMenu(const string &current_level, const string& next_level, const string audio_path, int){
}

MBMenu::MBMenu(int r, int g, int b, const string &current, const string&, const string&){
    m_r = r;
    m_g = g;
    m_b = b;
    m_current_level = current;
    m_start = -1;
    m_done = false;

    m_buttons.clear();

    m_buttons.push_back(new MBButton("Fase 1", "level-1", m_current_level, 50, 240, 299, 34));
    m_buttons.push_back(new MBButton("Sair", "exit", m_current_level, 1200, 650, 299, 34));

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
    if(label == "level-1"){
        m_next = "1";
        m_done = true;
    }
    if(label == "exit"){
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

    auto font = resources::get_font("Aller_Bd.ttf", 40);
    canvas->set_font(font);
    canvas->set_draw_color(Color(255, 255, 255));

    if(m_background)
        canvas->draw(m_background.get(), 0, 0);

    canvas->draw("Projeto EA / GA", 512, 20);
}