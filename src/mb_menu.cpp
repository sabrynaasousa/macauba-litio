#include "mb_menu.h"

vector<int> label_buttons[] = { {0, 1, 2, 3}, {4, 5}, {}, {} };
map<string, int> idx_names = { {"principal",0}, {"iniciar", 1}, {"opcoes", 2}, {"creditos", 3} };

MBMenu::MBMenu(const string&, const string&, const string, int){
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

    m_buttons.push_back(new MBButton("Macaúba", "macauba", m_current_level, "btn_background.png", 433, 320, 500, 112));
    m_buttons.push_back(new MBButton("Lítio", "litio", m_current_level, "btn_background.png", 433, m_buttons[4]->y() + m_buttons[4]->h() + 20, 500, 112));
    m_buttons.push_back(new MBButton("Voltar", "voltar", m_current_level, "btn_background.png", 30, m_buttons[5]->y() + m_buttons[5]->h() + 40, 250, 112));

    int tam = m_buttons.size();
    for(int i=0;i<tam;i++){
        add_child(m_buttons[i]);
        if(i >= 4) m_buttons[i]->set_active(false);
    }

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
    for(auto btn : m_buttons){
        btn->set_active(false);
    }

    for(auto idx : label_buttons[idx_names[label]]){
        m_buttons[idx]->set_active(true);
    }

    if(label == "iniciar" || label == "opcoes" || label == "creditos"){
        m_buttons[6]->set_active(true);
    }

    if(label == "iniciar"){
        m_buttons[6]->set_active(true);
        m_placeholder = "Escolha o ciclo de vida:";
    }
    else if(label == "sair"){
        exit(0);
    }
    else if(label == "macauba"){
        m_next = "1";
        m_done = true;
    }
    else if(label == "litio"){

    }
    else if(label == "voltar"){
        for(auto idx : label_buttons[idx_names["principal"]])
            m_buttons[idx]->set_active(true);

        m_placeholder = "";
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

    auto font = resources::get_font("MonospaceBold.ttf", 80);
    canvas->set_font(font);
    canvas->set_draw_color(Color(255, 255, 255));

    canvas->draw("Simuladores EA / GA", 350, 50);

    if(not m_placeholder.empty()){
        font = resources::get_font("MonospaceBold.ttf", 40);
        canvas->set_font(font);
        canvas->set_draw_color(Color(0, 0, 0));
        canvas->draw(m_placeholder, 400, 230);
    }
}
