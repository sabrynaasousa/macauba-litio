#include "mb_level.h"
#include "mb_toolbar.h"
#include "mb_piece.h"
#include "mb_trail.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>

#include <ijengine/rectangle.h>

using namespace std;
using namespace ijengine;

MBLevel::MBLevel(int r, int g, int b, const string &current, const string &next_level, const string &audio_path)
	: m_r(r), m_g(g), m_b(b), m_done(false), m_current_level(current), m_next(next_level), m_audio_path(audio_path), m_start(-1){
	printf("Começou a construir\n");
	
	MBToolbar *toolbar = new MBToolbar(current, 255, 255, 0, 1600, 100);
	
	// auto font = resources::get_font("Forelle.ttf", 40);
	// auto m_m_texture = resources::get_texture(m_current_level + "/collectable.png");
	m_background = resources::get_texture("/background.png");
	printf("Foi\n");

	MBTrail *trail = new MBTrail(m_current_level, 50, 130);
	trail->set_priority(2);
	add_child(trail);

	toolbar->set_priority(2);
	add_child(toolbar);

	m_buttons.clear();
	//m_buttons.push_back(new MBButton("Pronto!", m_current_level, 250, 220, "menu-nova-aventura.png", 299, 34));

	// for(auto btn : m_buttons){
		// add_child(btn);
	// }

	event::register_listener(this);

	this->set_priority(10);


	video::set_full_screen(0);

	printf("Construiu level\n");
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

void MBLevel::do_action(string label){
	if(label == "Pronto!"){
		m_done = true;
	}
}

bool MBLevel::on_event(const GameEvent&){
	return false;
}

void MBLevel::update_self(unsigned now, unsigned){
	printf("Entrou update level\n");
	if(m_start == -1)
		m_start=now;
	printf("Saiu update level\n");
}

void MBLevel::draw_self(Canvas *canvas, unsigned, unsigned){
	canvas->clear();

	canvas->draw(m_background.get(), 0, 0);

	auto font = resources::get_font("Forelle.ttf", 40);
	canvas->set_font(font);

	canvas->set_draw_color(Color(0, 0, 0));
	canvas->draw("Barra de Ferramentas", 300, 480);
}
