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

	string level_parsed = "";
	level_parsed += m_current_level[0];
	level_parsed += m_current_level[1];

	m_buttons.clear();
	m_buttons.push_back(new MBButton("Validar", "validar", "", "btn_background_" + level_parsed + ".png", 1150, 90, 100, 30, 20));
	m_buttons.push_back(new MBButton("Voltar", "voltar", m_current_level, 1250, 20, 100, 30, 20));
	m_buttons.push_back(new MBButton("Sim", "sim", "", "btn_background_" + level_parsed + ".png", 433, 220, 500, 112));
	m_buttons.push_back(new MBButton("Não", "nao", "", "btn_background_" + level_parsed + ".png", 433, m_buttons.back()->y() + m_buttons.back()->h() + 20, 500, 112));
	m_buttons.push_back(new MBButton("black-hole", "", 0, 0, "black-hole.png", 1366, 768, true));

	for(int i=0;i<m_buttons.size();i++){
        m_buttons[i]->set_priority(1000);
        add_child(m_buttons[i]);
        if(i > 1) m_buttons[i]->set_active(false);
	}

	m_buttons.back()->set_priority(900);
	m_buttons[0]->set_active(false);
	
	fstream level_design("res/" + m_current_level + "/level_design.txt");

	if(not level_design.is_open()){
		printf("Level design txt not available\n");
		exit(-1);
	}
	
	getline(level_design, m_level_name);
	printf("Level name = [%s]\n", m_level_name.c_str());

	map<string, vector<int> > ids;
	int id;

	level_design >> n_activities;
	for(int i = 0; i < n_activities; ++i){
		level_design >> id;
		ids["activity"].push_back(id);
	}

	level_design >> n_ins;
	for(int i = 0; i < n_ins; ++i){
		level_design >> id;
		ids["in"].push_back(id);
	}

	level_design >> n_intermediaries;
	for(int i = 0; i < n_intermediaries; ++i){
		level_design >> id;
		ids["intermediary"].push_back(id);
	}

	level_design >> n_outs1;
	for(int i = 0; i < n_outs1; ++i){
		level_design >> id;
		ids["out1"].push_back(id);
	}

	level_design >> n_outs2; 
	for(int i = 0; i < n_outs2; ++i){
		level_design >> id;
		ids["out2"].push_back(id);
	}

	level_design >> n_treatments;
	for(int i = 0; i < n_treatments; ++i){
		level_design >> id;
		ids["treatment"].push_back(id);
	}

	printf("Atividades: %d\nEntradas: %d\nIntermediarios: %d\nSaídas 1: %d\nSaídas 2: %d\nTratamentos: %d\n", n_activities, n_ins, n_intermediaries, n_outs1, n_outs2, n_treatments);

	MBToolbar *toolbar = new MBToolbar(current, 255, 255, 0, n_activities, n_ins, n_intermediaries, n_outs1, n_outs2, n_treatments, ids);

	level_design >> id_initial_intermediary;
	level_design >> n_trail_activities;
	printf("Atividades da trilha: %d\n", n_trail_activities);

	int id_activity, id_in, id_intermediary, id_out1, id_out2, id_treatment;
	for(int i = 0; i < n_trail_activities; ++i){
		level_design >> id_activity >> id_in >> id_intermediary >> id_out1 >> id_out2 >> id_treatment;
		MBActivity * activity = new MBActivity(id_activity, id_in, id_intermediary, id_out1, id_out2, id_treatment);
		printf("Ids %d: %d, %d, %d, %d, %d, %d\n", i, id_activity, id_in, id_intermediary, id_out1, id_out2, id_treatment);
		m_activities.push_back(activity);
	}

	m_background = resources::get_texture(m_current_level + "/background.png");

	MBTrail * trail = new MBTrail(m_current_level, m_activities, n_trail_activities, id_initial_intermediary);
	trail->set_priority(2);
	add_child(trail);

	toolbar->set_priority(2);
	add_child(toolbar);

	event::register_listener(this);

	this->set_priority(10);

	if(LEVEL) printf("Construiu level\n");
}

MBPlayableLevel::~MBPlayableLevel(){
	event::unregister_listener(this);
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
	if(label == "validar"){
		if(m_level_percentage < 100.0)
			m_next = "menu";

		printf("NEXT: %s\n", m_next.c_str());
		m_done = true;
	}
	else if(label == "voltar"){
		for(int i=1;i<m_buttons.size();i++)
			m_buttons[i]->set_active(true);
	}
	else if(label == "sim"){
		m_next = "menu";
		m_done = true;
	}
	else if(label == "nao"){
		for(int i=2;i<m_buttons.size();i++)
			m_buttons[i]->set_active(false);
	}
}

void MBPlayableLevel::show_confirmation_button(double percentage){
	// TODO mostrar mensagem de game over quando porcentagem menor que 100

	m_buttons[0]->set_active(true);
	m_level_percentage = percentage;
}

void MBPlayableLevel::hide_confirmation_button(){
	m_buttons[0]->set_active(false);
}

bool MBPlayableLevel::on_event(const GameEvent&){
	return false;
}

void MBPlayableLevel::update_self(unsigned now, unsigned){
	if(LEVEL) printf("Entrou update level\n");
	if(m_start == -1)
		m_start = now;
	if(LEVEL) printf("Saiu update level\n");
}

void MBPlayableLevel::draw_self(Canvas *canvas, unsigned, unsigned){
	if(LEVEL) printf("Entrou draw_self level\n");
	canvas->clear();

	canvas->draw(m_background.get(), 0, 0);

	int font_size = 40;
	auto font = resources::get_font("MonospaceBold.ttf", font_size);
	canvas->set_font(font);

	canvas->set_draw_color(Color(255, 255, 255));

	double len = 0.6 * m_level_name.size() * font_size - 1;
	canvas->draw(m_level_name, 683 - len/2 , 20);
	if(LEVEL) printf("Saiu draw_self level\n");
}
