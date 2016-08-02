#include "mb_level.h"
#include "mb_toolbar.h"
#include "mb_piece.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>

#include <ijengine/rectangle.h>

using namespace std;
using namespace ijengine;

MBLevel::MBLevel(int r, int g, int b, const string &current, const string &next_level, const string &audio_path)
	: m_r(r), m_g(g), m_b(b), m_done(false), m_current_level(current), m_next(next_level), m_audio_path(audio_path), m_start(-1){
	
	MBToolbar *toolbar = new MBToolbar(255, 255, 0, 1300, 100);
	
	// auto font = resources::get_font("Forelle.ttf", 40);
	// auto m_m_texture = resources::get_texture(m_current_level + "/collectable.png");
	printf("Foi\n");

	MBPiece *piece = new MBPiece(m_current_level, 200, 1);
	add_child(piece);

	toolbar->set_priority(2);
	
	video::set_full_screen(0);

	add_child(toolbar);
}

bool MBLevel::done() const{
	return m_done;
}

string MBLevel::next() const{
	return m_next;
}

string MBLevel::audio() const{
	return m_audio_path;
}

string MBLevel::current_level() const{
	return m_current_level;
}

void MBLevel::update_self(unsigned now, unsigned){
	if(m_start == -1)
		m_start=now;

	if(now - m_start > 10000)
		m_done = true;
}

void MBLevel::draw_self(Canvas *canvas, unsigned, unsigned){
	canvas->clear();

	auto font = resources::get_font("Forelle.ttf", 40);
	canvas->set_font(font);

	canvas->set_draw_color(Color(255, 255, 255));
	canvas->draw("Barra de Ferramentas", 213, 340);
}
