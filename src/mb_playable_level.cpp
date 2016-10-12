#include "mb_playable_level.h"
#include "mb_toolbar.h"
#include "mb_piece.h"
#include "mb_trail.h"

#include <iostream>
#include <fstream>

MBPlayableLevel::MBPlayableLevel(int r, int g, int b, const string &current, const string &next_level, const string &audio_path){	
	
	m_r = r;
	m_g = g;
	m_b = b;
	m_done = false;
	m_next = next_level;
	m_audio_path = audio_path;
	m_current_level = current;
	m_start = -1;

	if(LEVEL) printf("Começou a construir level\n");
	
	MBToolbar *toolbar = new MBToolbar(current, 255, 255, 0);

	fstream level_design("res/" + m_current_level + "/level_design.txt");

	if(not level_design.is_open()){
		printf("Level design txt not available\n");
		exit(-1);
	}
	
	getline(level_design, m_level_name);
	printf("Level name = [%s]\n", m_level_name.c_str());

	level_design >> n_activities >> n_ins >> n_intermediary >> n_outs1 >> n_outs2 >> n_treatments;
	printf("Atividades: %d\nEntradas: %d\nIntermediarios: %d\nSaídas 1: %d\nSaídas 2: %d\nTratamentos: %d\n", n_activities, n_ins, n_intermediary, n_outs1, n_outs2, n_treatments);

	level_design >> n_trail_activities;
	printf("Atividades da trilha: %d\n", n_trail_activities);

	int id_activity, id_in, id_intermediary, id_out1, id_out2, id_treatment;
	for(int i = 0; i < n_trail_activities; ++i){
		level_design >> id_activity >> id_in >> id_intermediary >> id_out1 >> id_out2 >> id_treatment;
		MBActivity * activity = new MBActivity(id_activity, id_in, id_intermediary, id_out1, id_out2, id_treatment);
		printf("Ids %d: %d, %d, %d, %d, %d, %d\n", i, id_activity, id_in, id_intermediary, id_out1, id_out2, id_treatment);
		m_activities.push_back(activity);
	}

	//exit(0);

	// auto font = resources::get_font("Forelle.ttf", 40);
	// auto m_m_texture = resources::get_texture(m_current_level + "/collectable.png");
	m_background = resources::get_texture(m_current_level + "/background.png");

	MBTrail *trail = new MBTrail(m_current_level, m_activities, n_trail_activities);
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

	if(LEVEL) printf("Construiu level\n");
}

bool MBPlayableLevel::done() const{
	return m_done;
}

string MBPlayableLevel::next() const{
	return m_next;
}

string MBPlayableLevel::audio() const{
	return m_audio_path;
}

string MBPlayableLevel::current_level() const{
	return m_current_level;
}

void MBPlayableLevel::do_action(string label){
	if(label == "Pronto!"){
		m_done = true;
	}
}

bool MBPlayableLevel::on_event(const GameEvent&){
	return false;
}

void MBPlayableLevel::update_self(unsigned now, unsigned){
	if(LEVEL) printf("Entrou update level\n");
	if(m_start == -1)
		m_start=now;
	if(LEVEL) printf("Saiu update level\n");
}

void MBPlayableLevel::draw_self(Canvas *canvas, unsigned, unsigned){
	if(LEVEL) printf("Entrou draw_self level\n");
	canvas->clear();

	canvas->draw(m_background.get(), 0, 0);

	auto font = resources::get_font("Forelle.ttf", 40);
	canvas->set_font(font);

	canvas->set_draw_color(Color(0, 0, 0));
	canvas->draw(m_level_name, 512, 20);
	if(LEVEL) printf("Saiu draw_self level\n");
}
