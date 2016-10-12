#ifndef MB_FRAME_H
#define MB_FRAME_H

#include <ijengine/engine.h>
#include <ijengine/collidable.h>
#include <ijengine/canvas.h>
#include <ijengine/texture.h>
#include <ijengine/game_object.h>
#include <ijengine/events_translator.h>
#include <ijengine/game_events_listener.h>

#include <string>
#include <list>

#include "mb_piece.h"

using std::shared_ptr;
using std::list;
using namespace ijengine;
using std::to_string;

class MBFrame : public GameObject, public Collidable, public GameEventsListener {
    public:
        MBFrame();
        MBFrame(std::string current_level, std::string type, double px, double py, int id_piece, int frame_id);
        ~MBFrame();
        double x() const;
        double y() const;
        int id() const;
        std::string type() const;
        const MBPiece * piece() const;
        double height();
        double width();
		bool is_right();
        shared_ptr<Texture> texture();
        double minimum_area() const;
		bool filled();

        void set_x(double px);
        void set_y(double py);
        void set_height(double ph);
		void set_right(bool is_r);
        void register_self(int current_x);
		void set_filled(bool is_filled);

        bool on_event(const GameEvent&);
        bool active() const;
        pair<double, double> direction() const;

        const Rectangle& bounding_box() const;
        const list<Rectangle>& hit_boxes() const;

        void on_collision(const Collidable *who, const Rectangle& where, const unsigned now, const unsigned last);

        typedef enum { CLICKING, NOT_CLICKING } ClickState;
        typedef enum { HOVERING, NOT_HOVERING } HoverState;

    protected:
        void update_self(unsigned now, unsigned last);
        void draw_self(Canvas *canvas, unsigned now, unsigned last);

    private:
        static const int INVALID = -10000000;
        static const int GAME_MOUSE_PRESSED = 1 << 8;
        static const int GAME_MOUSE_MOTION = 1 << 10;
        static const int GAME_MOUSE_RELEASED = 1 << 20;
        ClickState m_click_state;
        HoverState m_hover_state;
        double m_x, m_y;
        double m_height, m_width, m_minimum_area;
        double m_sprite_counter, m_sprite_speed;
		int m_correct_piece, m_id;
        int m_start;
		std::string m_type;
        Rectangle m_bounding_box;
        list<Rectangle> l;
        bool m_active, m_is_right, m_filled;
        const MBPiece * m_piece;
        shared_ptr<Texture> m_texture;
};

#endif
