#include "mb_toolbar.h"

#include <ijengine/canvas.h>

MBToolbar::MBToolbar(std::string current_level, int r, int g, int b, int w, int h)
	: m_r(r), m_g(g), m_b(b), m_rectangle(0, 430, w, h){

	for(int i=0; i<10; i++){
		m_pieces.push_back(new MBPiece(current_level, 50*(i+1), 400, i+1));
		add_child(m_pieces[i]);
	}

}

void MBToolbar::update_self(unsigned, unsigned){

}

void MBToolbar::draw_self(Canvas *canvas, unsigned, unsigned){
	canvas->set_draw_color(Color(m_r, m_g, m_b));
	canvas->draw(m_rectangle);
}
