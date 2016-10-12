#include "mb_trail.h"
#include "mb_answer.h"

#include <ijengine/canvas.h>

MBTrail::MBTrail(std::string current_level, vector<MBActivity *> activities){
	m_percentage = 0;
	m_face_texture[0] = resources::get_texture("sad.png");
	m_face_texture[1] = resources::get_texture("ok.png");
	m_face_texture[2] = resources::get_texture("happy.png");

	MBAnswer *answer = new MBAnswer();

	string type;
	n_frames = answer->n_frames(atoi(current_level.c_str())); 

	int id_frame = 0;
	int p_x = 30;

	type = "in";
	for(int i = 1; i <= n_frames; i++){
		frames[1][i] = new MBFrame(current_level, type, p_x + 170 * (i - 1), 108, answer->piece(atoi(current_level.c_str()), i, 0), id_frame++);
		add_child(frames[1][i]);
	}

	type = "main";
	for(int i = 1; i <= n_frames; i++){
		frames[2][i] = new MBFrame(current_level, type, p_x + 170 * (i - 1), 178, answer->piece(atoi(current_level.c_str()), i, 1), id_frame++);
		add_child(frames[2][i]);
	}

	type = "out";
	for(int i = 1; i <= n_frames; i++){
		frames[3][i] = new MBFrame(current_level, type, p_x + 48 + 170 * (i - 1), 320, answer->piece(atoi(current_level.c_str()), i, 2), id_frame++);
		add_child(frames[3][i]);
	}


	type = "treatment";
	for(int i = 1; i <= n_frames; i++){
		frames[4][i] = new MBFrame(current_level, type, p_x + 15 + 170 * (i - 1), 358, answer->piece(atoi(current_level.c_str()), i, 3), id_frame++);
		add_child(frames[4][i]);
	}

}

void MBTrail::update_self(unsigned, unsigned){
	int n_filled_frames = 0;
	int correct = 0;

	for(int type = 1; type <= 4; type++){
		for(int i = 1; i <= n_frames; i++){
			if(frames[type][i]->is_right())
				correct++;

			if(frames[type][i]->filled())
				n_filled_frames++;
		}
	}

	if(n_filled_frames)
		m_percentage = (double)correct/n_filled_frames * 100.0;
	else
		m_percentage = 0;
}

void MBTrail::draw_self(Canvas *canvas, unsigned, unsigned){
	canvas->draw(m_face_texture[min((int)(m_percentage/(100.0/3)+1e-8), 2)].get(), Rectangle(0, 0, 60, 60), 930, 20);

/*
	auto font = resources::get_font("Forelle.ttf", 40);
	canvas->set_font(font);

	canvas->set_draw_color(Color(0, 0, 0));
	canvas->draw(to_string(m_percentage) + " %", 800, 20);
*/
}
