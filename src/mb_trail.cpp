#include "mb_trail.h"

#include <ijengine/canvas.h>

MBTrail::MBTrail(std::string current_level, double p_x, double p_y){
	m_x = p_x;
	m_y = p_y;

	for(int i = 1; i <= 5; i++){
		MBFrame *frame = new MBFrame(current_level, p_x + 80 * i, p_y, 1);
		add_child(frame);
	}
}

void MBTrail::update_self(unsigned, unsigned){

}

void MBTrail::draw_self(Canvas *canvas, unsigned, unsigned){
}
