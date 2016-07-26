#include "mb_level.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>

using namespace std;
using namespace ijengine;

MBLevel::MBLevel(int r, int g, int b, const string &next_level, const string &audio_path)
	: m_r(r), m_g(g), m_b(b), m_done(false), m_next(next_level), m_audio_path(audio_path), m_start(-1){
	
	video::set_full_screen(0);
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

void MBLevel::update_self(unsigned now, unsigned){
	if(m_start == -1)
		m_start=now;

	if(now - m_start > 1000)
		m_done = true;
}

void MBLevel::draw_self(Canvas *canvas, unsigned, unsigned){
	auto font = resources::get_font("Forelle.ttf", 60);
	canvas->set_font(font);

	canvas->clear();
	canvas->draw("Teste de fonte", 300, 200);
}
