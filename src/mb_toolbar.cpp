#include "mb_toolbar.h"

#include <ijengine/canvas.h>

MBToolbar::MBToolbar(std::string current_level, int r, int g, int b, int w, int h)
	: m_r(r), m_g(g), m_b(b), m_x(0), m_y(550), m_w(w), m_h(h){

	for(int i=0; i<10; i++){
		m_pieces.push_back(new MBPiece(current_level, 50*(i+1), 520, i+1));
		add_child(m_pieces[i]);
	}

}

void MBToolbar::update_self(unsigned, unsigned){

}

void MBToolbar::draw_self(Canvas *canvas, unsigned, unsigned){
	canvas->set_draw_color(Color(m_r, m_g, m_b));
	canvas->draw(Rectangle(m_x, m_y, m_w, m_h));
}
