#include "mb_toolbar.h"

#include <ijengine/canvas.h>

MBToolbar::MBToolbar(std::string current_level, int r, int g, int b, int w, int h)
	: m_r(r), m_g(g), m_b(b), m_w(w), m_h(h), m_x(0), m_y(580){

    std::vector<std::string> vs {"in", "main", "out", "treatment"};

	for(int i = 0; i < 5; i++){
        printf("%d %d\n", i%2, i < 1);
		if(i != 4)
            m_pieces.push_back(new MBPiece(current_level, 10 + 80 * (i%2), 450 + (i < 2 ? 1 : 0) * 80, i + 1, "in"));
        else
            m_pieces.push_back(new MBPiece(current_level, 10 + 80 * (i%2) + 30, 450 + (i < 2 ? 1 : 0) * 80, i + 1, "in"));
        
        printf("%f, %f\n", m_pieces.back()->x(), m_pieces.back()->y());
        add_child(m_pieces.back());
    }
    // int x;
    // scanf("%d", &x);

    for(int i = 0; i < 5; i++){
        m_pieces.push_back(new MBPiece(current_level, 180 + 180 * i, 450, i + 1, "main"));
        add_child(m_pieces.back());
    }
        

    for(int i = 0; i < 5; i++){
        m_pieces.push_back(new MBPiece(current_level, 10 + 70 * i, 630, i + 1, "out"));
        add_child(m_pieces.back());
    }

    for(int i = 0; i < 5; i++){
        m_pieces.push_back(new MBPiece(current_level, 351 + 140 * i, 627, i + 1, "treatment"));
	    add_child(m_pieces.back());
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
