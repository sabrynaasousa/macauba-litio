#include "mb_toolbar.h"
#include "mb_button.h"
#include <ijengine/canvas.h>

MBToolbar::MBToolbar(std::string current_level, int r, int g, int b, int n_activities, int n_ins, int n_intermediaries, int n_outs1, int n_outs2, int n_treatments, map<string, vector<int> > ids)
	: m_r(r), m_g(g), m_b(b), m_x(0), m_y(440), m_following(false), m_active_rectangle(0) {
    if(TOOLBAR) printf("Construindo toolbar\n");

    // TODO fixme
    goto eita;
    eita:
	for(int i = 0; i < n_ins; i++){
        m_pieces.push_back(new MBPiece(current_level, TOOLBAR_DISTANCE + 80 * (i%11), 445 + 100 * (i/11), ids["in"][i], "in"));        
        add_child(m_pieces.back());
    }
    // int x;
    // scanf("%d", &x);

    for(int i = 0; i < n_intermediaries; i++){
        m_pieces.push_back(new MBPiece(current_level, TOOLBAR_DISTANCE + 90 * (i%11), 445 + 90 * (i/11), ids["intermediary"][i], "intermediary"));
        add_child(m_pieces.back());
    }

    for(int i = 0; i < n_activities; i++){
        m_pieces.push_back(new MBPiece(current_level, TOOLBAR_DISTANCE + 280 * (i%4), 445 + 170 * (i/4), ids["activity"][i], "activity"));
        add_child(m_pieces.back());
    }
        

    for(int i = 0; i < n_outs1; i++){
        m_pieces.push_back(new MBPiece(current_level, TOOLBAR_DISTANCE + 90 * (i%11), 445 + 70 * (i/11), ids["out1"][i], "out1"));
        add_child(m_pieces.back());
    }

    //For das out2 fixme
    for(int i = 0; i < n_outs2; i++){
        m_pieces.push_back(new MBPiece(current_level, TOOLBAR_DISTANCE + 90 * (i%11), 585 + 70 * (i/11), ids["out2"][i], "out2"));
        add_child(m_pieces.back());
    }

    for(int i = 0; i < n_treatments; i++){
        m_pieces.push_back(new MBPiece(current_level, TOOLBAR_DISTANCE + 160 * (i%7), 445 + 72 * (i/7), ids["treatment"][i], "treatment"));
	    add_child(m_pieces.back());
	}

    int font_size = 20;

    m_buttons.push_back(new MBButton("Atividades", "atividades", "toolbar", 0, m_y + 0, 180, 66, font_size));
    m_buttons.push_back(new MBButton("Entradas", "entradas", "toolbar", 0, m_y + 66, 180, 66, font_size));
    m_buttons.push_back(new MBButton("Intermediários", "intermediarios", "toolbar", 0, m_y + 132, 180, 66, font_size));
    m_buttons.push_back(new MBButton("Saídas", "saidas", "toolbar", 0, m_y + 198, 180, 66, font_size));
    m_buttons.push_back(new MBButton("Tratamentos", "tratamentos", "toolbar", 0, m_y + 264, 180, 66, font_size));

    for(auto button : m_buttons){
        button->set_priority(20);
        button->set_texture(current_level + "/toolbar_rectangle.png");
        button->set_active_texture(true);
        add_child(button);
    }

    do_action("atividades");

    m_background = resources::get_texture(current_level + "/toolbar.png");

    if(TOOLBAR) printf("Construiu toolbar\n");
}

bool MBToolbar::equals(string type, string piece_type){
    printf("[%s] [%s]\n", type.c_str(), piece_type.c_str());
    return ((type == piece_type) or (type == "out" and (piece_type == "out1" or piece_type == "out2")));
}

void MBToolbar::do_action(string label){
    for(auto button : m_buttons){
        button->set_active_texture(label != button->label());
    }

    string type;
    if(label == "atividades"){
        type = "activity";
    }else if(label == "entradas"){
        type = "in";
    }else if(label == "intermediarios"){
        type = "intermediary";
    }else if(label == "saidas"){
        type = "out";
    }else if(label == "tratamentos"){
        type = "treatment";
    }

    for(auto piece : m_pieces){
        piece->set_active(equals(type, piece->type()));
        if(equals(type, piece->type())){
            printf("Piece %s ativada\n", piece->type().c_str());
        }else{
            printf("Piece %s desativada\n", piece->type().c_str());
        }
    }
}

void MBToolbar::update_self(unsigned, unsigned){
    if(TOOLBAR) printf("Updating toolbar\n");
}

void MBToolbar::draw_self(Canvas *canvas, unsigned, unsigned){
    if(TOOLBAR) printf("Entrando draw_self toolbar\n");
    canvas->draw(m_background.get(), m_x, m_y);
    //for(int i = 0; i < 5; ++i){
        //if(i != m_active_rectangle) canvas->draw(m_rectangle.get(), 0, m_y + 66 * i);
    //}
    if(TOOLBAR) printf("Saind draw_self toolbar\n");
}

void MBToolbar::set_following(bool following){
    m_following = following;
}

bool MBToolbar::get_following(){
    return m_following;
}