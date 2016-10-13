#include "mb_menu.h"

MBMenu::MBMenu(const string &current_level, const string& next_level, const string audio_path, int){
    // m_current_level = current_level;
    // m_audio = audio_path;
    // m_next = next_level;
    // m_done = false;
    // m_state = NOTHING;
    // m_start = -1;
    // on_credit = false;

    // m_background[0] = resources::get_texture(m_current_level + "/menu-fundo.png");
    // m_background[1] = resources::get_texture(m_current_level + "/menu-titulo.png");

    // int n_levels = 6;
    // m_save = new TWSave(n_levels);

    // m_buttons.clear();

    // if(m_save->times_played(1) == 0){
    //     m_buttons.push_back(new TWButton("new-adventure", m_current_level, 50, 240, "menu-nova-aventura.png", 299, 34));
    //     m_buttons.push_back(new TWButton("options", m_current_level, 50, 284, "menu-opcoes.png", 139, 51));
    //     m_buttons.push_back(new TWButton("exit", m_current_level, 50, 345, "menu-sair.png", 86, 34));
    // }
    // else{
    //     m_buttons.push_back(new TWButton("new-adventure", m_current_level, 50, 220, "menu-nova-aventura.png", 299, 34));
    //     m_buttons.push_back(new TWButton("continue-adventure", m_current_level, 50, 264, "menu-continuar-aventura.png", 409, 35));
    //     m_buttons.push_back(new TWButton("options", m_current_level, 50, 309, "menu-opcoes.png", 139, 51));
    //     m_buttons.push_back(new TWButton("exit", m_current_level, 50, 370, "menu-sair.png", 86, 34));
    // }

    // m_buttons.push_back(new TWButton("credits", m_current_level, 680, 410, "creditos-botao.png", 142, 50));

    // for(auto btn : m_buttons){
    //     add_child(btn);
    // }

    event::register_listener(this);
}

MBMenu::MBMenu(int r, int g, int b, const string &current, const string &next, const string &audio_path){
    m_r = r;
    m_g = g;
    m_b = b;
    m_current_level = current;
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
    // if(label == "new-adventure"){
    //     m_next = "cutscene-intro";
    //     m_done = true;
    // }
    // if(label == "continue-adventure"){
    //     m_next = "limbo";
    //     m_done = true;
    // }
    // if(label == "options"){
    //     for(auto btn : m_buttons){
    //         btn->set_active(false);
    //     }

    //     m_buttons.push_back(new TWButton("back", m_current_level, 30, 410, "voltar-botao.png", 142, 50));
    //     m_buttons.push_back(new TWButton("volume", m_current_level, 150, 280, "opcoes/volume-botao.png", 189, 28));
    //     m_buttons.push_back(new TWButton("volume-bar", m_current_level, 370, 280, "opcoes/volume-barra.png", 225, 28));
    //     m_buttons.push_back(new TWButton("volume-ind", m_current_level, 575, 280, "opcoes/volume-indicador.png", 189, 28));

    //     for(auto btn : m_buttons){
    //         add_child(btn);
    //     }
    // }
    // if(label == "credits"){
    //     for(auto btn : m_buttons){
    //         btn->set_active(false);
    //     }

    //     m_credits = resources::get_texture(m_current_level + "/creditos.png");
    //     on_credit = true;

    //     m_buttons.push_back(new TWButton("back", m_current_level, 680, 410, "voltar-botao.png", 142, 50));
    //     for(auto btn : m_buttons){
    //         add_child(btn);
    //     }
    // }
    // if(label == "volume-bar"){
    //     auto indicator = m_buttons[m_buttons.size() - 1];
    //     auto bar = m_buttons[m_buttons.size() - 2];
    //     double percentage = bar->percentage();
    //     indicator->set_x(percentage - 14);
    //     double new_x = indicator->x();
    //     audio::set_audio_volume(1 - (575 - new_x)/225);
    // }
    // if(label == "back"){
    //     m_next = "menu";
    //     m_done = true;
    // }
    // if(label == "exit"){
    //     audio::play_sound_effect("res/effects/exit.wav");
    //     exit(0);
    // }
}

bool MBMenu::on_event(const GameEvent&){
    return false;
}

void MBMenu::update_self(unsigned, unsigned){

    // if(m_state == SELECTING){
    //     m_state = RUNNING;
    //     m_done = true;
    // }
}

void MBMenu::draw_self(Canvas *canvas, unsigned, unsigned){
    canvas->clear();
    canvas->set_clear_color(Color(m_r, m_g, m_b));

    if(m_background)
        canvas->draw(m_background.get(), Rectangle(0, 0, 852, 480), 0, 0);
}