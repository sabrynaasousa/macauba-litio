#include "mb_menu.h"

MBMenu::MBMenu(const string&, const string&, const string, int){
}

MBMenu::MBMenu(int r, int g, int b, const string &current, const string&, const string&){
	video::set_full_screen(1);

    populate_label_map();

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

    m_buttons.push_back(new MBButton("Lítio", "litio", m_current_level, "btn_background.png", 433, 320, 500, 112));
    m_buttons.push_back(new MBButton("Macaúba", "macauba", m_current_level, "btn_background.png", 433, m_buttons[4]->y() + m_buttons[4]->h() + 20, 500, 112));
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

    if(label == "iniciar" || label == "opcoes"){
        m_buttons[6]->set_active(true);
    }

    if(label == "iniciar"){
        m_buttons[6]->set_active(true);
        m_placeholders.clear();
        m_placeholders.push_back("Escolha o ciclo de vida:");
    }
    else if(label == "creditos"){
        m_buttons[6]->set_active(true);
        m_placeholders.clear();
        m_placeholders.push_back("Igor Ribeiro Barbosa Duarte");
        m_placeholders.push_back("João Vitor Araujo Moura");
        m_placeholders.push_back("Vítor Barbosa de Araujo");
    }
    else if(label == "sair"){
        exit(0);
    }
    else if(label == "macauba"){
        m_next = "mb_1";
        m_done = true;
		return;
    }
    else if(label == "litio"){
        m_next = "lt_1";
        m_done = true;
		return;
    }
    else if(label == "voltar"){
        m_placeholders.clear();

        for(auto idx : label_buttons[idx_names["principal"]])
            m_buttons[idx]->set_active(true);
    }

    for(auto idx : label_buttons[idx_names[label]]){
        m_buttons[idx]->set_active(true);
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

    if(not m_placeholders.empty()){
        font = resources::get_font("MonospaceBold.ttf", 40);
        canvas->set_font(font);
        canvas->set_draw_color(Color(0, 0, 0));

        int tam = m_placeholders.size();
        for(int i=0;i<tam;i++)
            canvas->draw(m_placeholders[i], 400, 230 + 80 * i);
    }
}

void MBMenu::populate_label_map(){
    label_buttons[0].push_back(0);
    label_buttons[0].push_back(1);
    label_buttons[0].push_back(2);
    label_buttons[0].push_back(3);
    label_buttons[1].push_back(4);
    label_buttons[1].push_back(5);

    idx_names.insert(make_pair("principal", 0));
    idx_names.insert(make_pair("iniciar", 1));
    idx_names.insert(make_pair("opcoes", 2));
    idx_names.insert(make_pair("creditos", 3));
    idx_names.insert(make_pair("litio", 4));
    idx_names.insert(make_pair("macauba", 5));
}