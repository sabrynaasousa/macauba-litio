#include "mb_toolbar.h"
#include "mb_button.h"
#include <ijengine/canvas.h>

MBToolbar::MBToolbar(std::string current_level, int r, int g, int b)
	: m_r(r), m_g(g), m_b(b), m_x(0), m_y(440), m_following(false), m_active_rectangle(0) {
    if(TOOLBAR) printf("Construindo toolbar\n");

    // TODO fixme
    goto eita;

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

    eita:
    int font_size = 20;

    m_buttons.push_back(new MBButton("Atividades", "atividades", "toolbar", 0, m_y + 0, 180, 66, font_size));
    m_buttons.push_back(new MBButton("Entradas", "entradas", "toolbar", 0, m_y + 66, 180, 66, font_size));
    m_buttons.push_back(new MBButton("Intermediários", "intermediarios", "toolbar", 0, m_y + 132, 180, 66, font_size));
    m_buttons.push_back(new MBButton("Saídas", "saidas", "toolbar", 0, m_y + 198, 180, 66, font_size));
    m_buttons.push_back(new MBButton("Tratamentos", "tratamentos", "toolbar", 0, m_y + 264, 180, 66, font_size));

    for(auto button : m_buttons){
        button->set_priority(20);
        add_child(button);
    }

    m_background = resources::get_texture(current_level + "/toolbar.png");
    m_rectangle = resources::get_texture("toolbar_rectangle.png");

    if(TOOLBAR) printf("Construiu toolbar\n");
}

void MBToolbar::do_action(string label){
    if(label == "atividades"){
        m_active_rectangle = 0;
    }else if(label == "entradas"){
        m_active_rectangle = 1;
    }else if(label == "intermediarios"){
        m_active_rectangle = 2;
    }else if(label == "saidas"){
        m_active_rectangle = 3;
    }else{
        m_active_rectangle = 4;
    }
}

void MBToolbar::update_self(unsigned, unsigned){
    if(TOOLBAR) printf("Updating toolbar\n");
}

void MBToolbar::draw_self(Canvas *canvas, unsigned, unsigned){
    if(TOOLBAR) printf("Entrando draw_self toolbar\n");
    canvas->draw(m_background.get(), m_x, m_y);
    for(int i = 0; i < 5; ++i){
        if(i != m_active_rectangle) canvas->draw(m_rectangle.get(), 0, m_y + 66 * i);
    }
    if(TOOLBAR) printf("Saind draw_self toolbar\n");
}

void MBToolbar::set_following(bool following){
    m_following = following;
}

bool MBToolbar::get_following(){
    return m_following;
}