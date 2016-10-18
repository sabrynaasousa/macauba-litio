#include "mb_button.h"
#include "mb_playable_level.h"
#include "mb_menu.h"
#include "mb_toolbar.h"

#include <ijengine/canvas.h>

MBButton::MBButton(string btn_label, string cur_level, double b_x, double b_y, string img, double b_w, double b_h) :
    m_click_state(NOT_CLICKING), m_hover_state(NOT_HOVERING), m_label(btn_label), m_img(img), m_level(cur_level),
    m_x(b_x), m_y(b_y), m_h(b_h), m_w(b_w), m_font_size(-1), m_active(true){
    
    m_texture_label = img;
    m_texture = resources::get_texture(cur_level + "/" + m_texture_label);
    m_active_texture = true;

    event::register_listener(this);
}

MBButton::MBButton(string btn_text, string btn_label, string cur_level, double b_x, double b_y, double b_w, double b_h, int font_size) :
    m_click_state(NOT_CLICKING), m_hover_state(NOT_HOVERING), m_label(btn_label), m_level(cur_level),
    m_x(b_x), m_y(b_y), m_h(b_h), m_w(b_w), m_font_size(font_size), m_active(true), m_active_texture(false) {

    m_text = btn_text;

    event::register_listener(this);
}

// button with text and background
MBButton::MBButton(string btn_text, string btn_label, string cur_level, string img, double b_x, double b_y, double b_w, double b_h) :
    m_click_state(NOT_CLICKING), m_hover_state(NOT_HOVERING), m_label(btn_label), m_img(img), m_level(cur_level),
    m_x(b_x), m_y(b_y), m_h(b_h), m_w(b_w), m_font_size(-1), m_active(true), m_active_texture(false) {

    m_text = btn_text;
    m_texture_label = img;
    m_texture = resources::get_texture(cur_level + "/" + m_texture_label);
    m_active_texture = true;

    event::register_listener(this);
}

MBButton::~MBButton(){
    event::unregister_listener(this);
}

double MBButton::x(){ return m_x; }
double MBButton::y(){ return m_y; }
double MBButton::w(){ return m_w; }
double MBButton::h(){ return m_h; }
bool MBButton::active(){ return m_active; }
string MBButton::level(){ return m_level; }
string MBButton::label(){ return m_label; }
string MBButton::texture(){ return m_texture_label; }
void MBButton::set_active(bool act){ m_active = act; }

void MBButton::set_texture(string btn_texture){
    m_texture = resources::get_texture(btn_texture);
}

bool MBButton::active_texture(){
    return m_active_texture;
}

void MBButton::set_active_texture(bool c_active_texture){
    m_active_texture = c_active_texture;
}

void MBButton::update_self(unsigned, unsigned){}

bool MBButton::on_event(const GameEvent& event){
    if(not m_active) return false;

    if(event.id() == GAME_MOUSE_PRESSED){
        double mouse_x = event.get_property<double>("x");
        double mouse_y = event.get_property<double>("y");

        int min_x = m_x, max_x = m_x + m_w;
        int min_y = m_y, max_y = m_y + m_h;

        if(mouse_x >= min_x && mouse_x <= max_x && mouse_y >= min_y && mouse_y <= max_y){
            m_click_state = CLICKING;
            return true;
        }
    }

    if(event.id() == GAME_MOUSE_RELEASED){
        double mouse_x = event.get_property<double>("x");
        double mouse_y = event.get_property<double>("y");

        int min_x = m_x, max_x = m_x + m_w;
        int min_y = m_y, max_y = m_y + m_h;

        if(mouse_x >= min_x && mouse_x <= max_x && mouse_y >= min_y && mouse_y <= max_y){
            if(m_click_state == CLICKING){
                auto p = this->parent();

                if(m_level == "1"){
                    auto parent_class = dynamic_cast <MBPlayableLevel *>(p);
                    parent_class -> do_action(m_label);
                }
                else if(m_level == "menu"){
                    auto parent_class = dynamic_cast <MBMenu *>(p);
                    parent_class -> do_action(m_label);
                }else if(m_level == "toolbar"){
                    auto parent_class = dynamic_cast <MBToolbar *>(p);
                    parent_class -> do_action(m_label);
                }
            }
        }
    }

    return false;
}

void MBButton::draw_self(Canvas *canvas, unsigned, unsigned){
    if(m_active){
        if(m_active_texture){
            canvas->draw(m_texture.get(), Rectangle(0, 0, m_w, m_h), m_x, m_y);
        }

        if(not m_text.empty()){
            int font_size = m_font_size == -1 ? 60 : m_font_size;
            auto font = resources::get_font("MonospaceBold.ttf", font_size);
            canvas->set_font(font);
            canvas->set_draw_color(Color(255, 255, 255));

            double len = 0.6 * m_label.size() * font_size - 1;
            canvas->draw(m_text, m_x + m_w/2 - len/2, m_y + 25);
        }
    }
}
