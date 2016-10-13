#include "mb_button.h"
#include "mb_playable_level.h"
#include "mb_menu.h"

#include <ijengine/canvas.h>

MBButton::MBButton(string btn_label, string cur_level, double b_x, double b_y, string img, double b_w, double b_h) :
    m_click_state(NOT_CLICKING), m_hover_state(NOT_HOVERING), m_label(btn_label), m_img(img), m_level(cur_level),
    m_x(b_x), m_y(b_y), m_h(b_h), m_w(b_w) {
    
    m_texture_label = img;
    m_texture = resources::get_texture(cur_level + "/" + m_texture_label);

    event::register_listener(this);
}

MBButton::MBButton(string btn_text, string btn_label, string cur_level, double b_x, double b_y, double b_w, double b_h) :
    m_click_state(NOT_CLICKING), m_hover_state(NOT_HOVERING), m_label(btn_label), m_level(cur_level),
    m_x(b_x), m_y(b_y), m_h(b_h), m_w(b_w) {

    m_text = btn_text;

    event::register_listener(this);
}

MBButton::~MBButton(){
    event::unregister_listener(this);
}

double MBButton::x(){ return m_x; }
double MBButton::y(){ return m_y; }
double MBButton::w(){ return m_w; }
double MBButton::h(){ return m_h; }
string MBButton::level(){ return m_level; }
string MBButton::label(){ return m_label; }
string MBButton::texture(){ return m_texture_label; }

void MBButton::set_texture(string btn_texture){
    m_texture = resources::get_texture(m_level + "/" + btn_texture);
}

void MBButton::update_self(unsigned, unsigned){}

bool MBButton::on_event(const GameEvent& event){
    if(event.id() == GAME_MOUSE_CLICK){
        double mouse_x = event.get_property<double>("x");
        double mouse_y = event.get_property<double>("y");

        int min_x = m_x, max_x = m_x + m_w;
        int min_y = m_y, max_y = m_y + m_h;

        if(mouse_x >= min_x && mouse_x <= max_x && mouse_y >= min_y && mouse_y <= max_y){
            auto p = this->parent();

            if(m_level == "1"){
                auto parent_class = dynamic_cast <MBPlayableLevel *>(p);
                parent_class -> do_action(m_label);
            }
            else if(m_level == "menu"){
                auto parent_class = dynamic_cast <MBMenu *>(p);
                parent_class -> do_action(m_label);
            }
        }
    }

    return false;
}

void MBButton::draw_self(Canvas *canvas, unsigned, unsigned){
    if(m_text.empty()){
        canvas->draw(m_texture.get(), m_x, m_y);
    }
    else{
        canvas->draw(m_text, m_x, m_y);
    }
}
