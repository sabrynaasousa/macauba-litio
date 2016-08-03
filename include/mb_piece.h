#ifndef MB_PIECE_H
#define MB_PIECE_H

#include <ijengine/engine.h>
#include <ijengine/collidable.h>
#include <ijengine/canvas.h>
#include <ijengine/texture.h>
#include <ijengine/game_object.h>
#include <ijengine/events_translator.h>
#include <ijengine/game_events_listener.h>

#include <string>
#include <list>

using std::shared_ptr;
using std::list;
using namespace ijengine;
using std::to_string;

class MBPiece : public GameObject, public Collidable, public GameEventsListener {
    public:
        MBPiece();
        MBPiece(std::string current_level, double px, double py, int piece_id);
        ~MBPiece();
        double x();
        double y();
        double height();
        double width();
        shared_ptr<Texture> texture();

        void set_x(double px);
        void set_y(double py);
        void set_height(double ph);
        void register_self(int current_x);

        bool on_event(const GameEvent& event);
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
        double m_height, m_width;
        double m_sprite_counter, m_sprite_speed;
        int m_start, m_id;
        Rectangle m_bounding_box;
        list<Rectangle> l;
        bool m_active, m_following;
        shared_ptr<Texture> m_texture;
};

#endif
