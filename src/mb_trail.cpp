#include "mb_trail.h"
#include "mb_answer.h"

#include <ijengine/canvas.h>

MBTrail::MBTrail(std::string current_level, double p_x, double p_y){
	m_x = p_x;
	m_y = p_y;

	m_percentage = 0;

	MBAnswer *answer = new MBAnswer();

	//COLOCAR O TIPO DA PEÇA
	int type=0;

	n_frames = answer->n_frames(1); 
	for(int i = 1; i <= n_frames; i++){
		frames[i] = new MBFrame(current_level, i%4, p_x + 80 * i, p_y, answer->piece(atoi(current_level.c_str()), i, type));
		add_child(frames[i]);
	}
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
