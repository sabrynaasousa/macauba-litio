#include "mb_level.h"
#include "mb_level_factory.h"
#include "mb_menu.h"

Level * MBLevelFactory::make_level(const string &level_id){
    if(level_id == "menu")
        return new MBMenu(0, 142, 50, "menu", "", "");
	else if(level_id == "lt_1")
		return new MBPlayableLevel(255, 0, 0, "lt_1", "lt_2", "");
	else if(level_id == "mb_1")
		return new MBPlayableLevel(255, 0, 0, "mb_1", "mb_2", "");
	else
		return nullptr;
}

void MBLevelFactory::release(Level *level){
	delete level;
}
