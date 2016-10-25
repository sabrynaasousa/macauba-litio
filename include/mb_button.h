#ifndef MB_BUTTON_H
#define MB_BUTTON_H

#include <memory>
#include <iostream>
#include <ijengine/engine.h>
#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>
#include <ijengine/events_translator.h>
#include <ijengine/game_events_listener.h>

using namespace ijengine;
using std::shared_ptr;
using std::string;

class MBButton : public GameObject, public GameEventsListener {
    public:
        MBButton(string label, string cur_level, double b_x, double b_y, string img, double b_w, double b_h, bool murph = false);
        MBButton(string btn_text, string label, string cur_level, double b_x, double b_y, double b_w, double b_h, int font_size = 40, bool murph = false);
        MBButton(string btn_text, string btn_label, string cur_level, string img, double b_x, double b_y, double b_w, double b_h, bool murph = false);
        MBButton() {}
        ~MBButton();

        double w();
        double h();
        double x();
        double y();
        bool active();
        string level();
        string label();
        string texture();
        void set_texture(string btn_texture);
        void set_active(bool act);
        bool active_texture();
        void set_active_texture(bool active_texture);

        bool on_event(const GameEvent& event);

        typedef enum { CLICKING, NOT_CLICKING } ClickState;
        typedef enum { HOVERING, NOT_HOVERING } HoverState;

    protected:
        void update_self(unsigned now, unsigned last);
        void draw_self(Canvas *canvas, unsigned now, unsigned last);        

    private:
        static const unsigned GAME_MOUSE_PRESSED = 1 << 8;
        static const unsigned GAME_MOUSE_RELEASED = 1 << 20;
        ClickState m_click_state;
        HoverState m_hover_state;
        string m_label, m_texture_label;
        string m_img, m_action, m_level, m_text;
        double m_x, m_y, m_h, m_w;
        int m_font_size;
        shared_ptr<Texture> m_texture;
        bool m_active, m_active_texture;
        bool m_blackhole;
};

#endif
