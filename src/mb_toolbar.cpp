#include "mb_toolbar.h"

#include <ijengine/canvas.h>

MBToolbar::MBToolbar(int r, int g, int b, int w, int h)
	: m_r(r), m_g(g), m_b(b), m_rectangle(0, 430, w, h){

}

void MBToolbar::update_self(unsigned, unsigned){

}

void MBToolbar::draw_self(Canvas *canvas, unsigned, unsigned){
	canvas->set_draw_color(Color(m_r, m_g, m_b));
	canvas->draw(m_rectangle);
}
