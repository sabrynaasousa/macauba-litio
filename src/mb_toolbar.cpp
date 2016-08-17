#include "mb_toolbar.h"

#include <ijengine/canvas.h>

MBToolbar::MBToolbar(std::string current_level, int r, int g, int b, int w, int h)
	: m_r(r), m_g(g), m_b(b), m_x(0), m_y(580), m_w(w), m_h(h){

    std::vector<std::string> vs {"in", "main", "out", "treatment"};

	int piece_id = 1;

	for(int i = 0; i < 4; i++){
		m_pieces.push_back(new MBPiece(current_level, 5 + 80 * i, 520, piece_id++, "in"));
		add_child(m_pieces[i]);
	}


/*	for(int i=0; i<4; i++){
		m_pieces.push_back(new MBPiece(current_level, 200*(i+1), 520, i, vs[i]));
		add_child(m_pieces[i]);
	}
*/
}

void MBToolbar::update_self(unsigned, unsigned){

}

void MBToolbar::draw_self(Canvas *canvas, unsigned, unsigned){
	canvas->set_draw_color(Color(m_r, m_g, m_b));
	canvas->draw(Rectangle(m_x, m_y, m_w, m_h));
}
