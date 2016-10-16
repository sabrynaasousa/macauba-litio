#include "mb_toolbar.h"
#include <ijengine/canvas.h>

MBToolbar::MBToolbar(std::string current_level, int r, int g, int b)
	: m_r(r), m_g(g), m_b(b), m_x(0), m_y(440){
    if(TOOLBAR) printf("Construindo toolbar\n");

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
        m_pieces.push_back(new MBPiece(current_level, 180 + 180 * i, 450, i + 1, "activity"));
        add_child(m_pieces.back());
    }
        

    for(int i = 0; i < 5; i++){
        m_pieces.push_back(new MBPiece(current_level, 10 + 70 * i, 630, i + 1, "out1"));
        add_child(m_pieces.back());
    }

    for(int i = 0; i < 5; i++){
        m_pieces.push_back(new MBPiece(current_level, 351 + 140 * i, 627, i + 1, "treatment"));
	    add_child(m_pieces.back());
	}

    m_background = resources::get_texture(current_level + "/toolbar.png");

    if(TOOLBAR) printf("Construiu toolbar\n");
}

void MBToolbar::update_self(unsigned, unsigned){
    if(TOOLBAR) printf("Updating toolbar\n");
}

void MBToolbar::draw_self(Canvas *canvas, unsigned, unsigned){
    if(TOOLBAR) printf("Entrando draw_self toolbar\n");
	canvas->set_draw_color(Color(m_r, m_g, m_b));
    canvas->draw(m_background.get(), m_x, m_y);
    if(TOOLBAR) printf("Saind draw_self toolbar\n");
}
