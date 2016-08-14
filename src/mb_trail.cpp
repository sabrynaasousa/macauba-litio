#include "mb_trail.h"
#include "mb_answer.h"

#include <ijengine/canvas.h>

MBTrail::MBTrail(std::string current_level, double p_x, double p_y){
	m_x = p_x;
	m_y = p_y;

	m_percentage = 0;

	MBAnswer *answer = new MBAnswer();

	int type;
	n_frames = answer->n_frames(1); 

	type=0;
	n_frames = 1;
	frames[1] = new MBFrame(current_level, type, p_x + 80 * 1, 178 - 70, answer->piece(atoi(current_level.c_str()), 1, type));
	add_child(frames[1]);

	type=1;
	frames[2] = new MBFrame(current_level, type, p_x + 80 * 1, 178, answer->piece(atoi(current_level.c_str()), 1, type));
	add_child(frames[2]);

	type=2;
	frames[3] = new MBFrame(current_level, type, p_x + 80 * 1 + 48 , 178 + 142, answer->piece(atoi(current_level.c_str()), 1, type));
	add_child(frames[3]);

	type=3;
	frames[4] = new MBFrame(current_level, type, p_x + 80 * 1 + 15, 178 + 180, answer->piece(atoi(current_level.c_str()), 1, type));
	add_child(frames[4]);
	

/*
	type = 0;
	for(int i = 1; i <= n_frames; i++){
		frames[i] = new MBFrame(current_level, type, p_x + 80 * i, 106, answer->piece(atoi(current_level.c_str()), i, type));
		add_child(frames[i]);
	}*/
/*
	type = 1;
	for(int i = 1; i <= n_frames; i++){
		frames[i] = new MBFrame(current_level, type, p_x + 80 * i, 250, answer->piece(atoi(current_level.c_str()), i, type));
		add_child(frames[i]);
	}

	type = 2;
	for(int i = 1; i <= n_frames; i++){
		frames[i] = new MBFrame(current_level, type, p_x + 80 * i, 394, answer->piece(atoi(current_level.c_str()), i, type));
		add_child(frames[i]);
	}

	type = 3;
	for(int i = 1; i <= n_frames; i++){
		frames[i] = new MBFrame(current_level, type, p_x + 80 * i, 459, answer->piece(atoi(current_level.c_str()), i, type));
		add_child(frames[i]);
	}
*/
}

void MBTrail::update_self(unsigned, unsigned){
	int count=0;

	for(int i = 1; i <= n_frames; i++){
		if(frames[i]->is_right())
			count++;
	}

	m_percentage = (double)count/n_frames * 100.0;
}

void MBTrail::draw_self(Canvas *canvas, unsigned, unsigned){
	auto font = resources::get_font("Forelle.ttf", 40);
	canvas->set_font(font);

	canvas->draw("O gabarito é 6, 7, 8, 9, 10", 213, 20);

	canvas->set_draw_color(Color(255, 255, 255));
	canvas->draw(to_string(m_percentage) + " %", 213, 65);
}
