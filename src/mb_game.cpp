#include "mb_game.h"

#include <ijengine/system_event.h>

MBGame::MBGame(const string &title, int w, int h)
	: m_game(title, w, h), m_engine(), m_level_factory(){

	event::register_translator(&m_translator);
	level::register_factory(&m_level_factory);

    physics::set_collision_mode(physics::Mode::ALL_TO_ALL, nullptr);
    resources::set_fonts_dir("res");
    resources::set_textures_dir("res");
}

MBGame::~MBGame(){
	level::unregister_factory();
	event::unregister_translator(&m_translator);
}

int MBGame::run(const string &level_id){
	return m_game.run(level_id);
}
