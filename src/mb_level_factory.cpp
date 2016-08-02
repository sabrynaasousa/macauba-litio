#include "mb_level.h"
#include "mb_level_factory.h"

Level *MBLevelFactory::make_level(const string &level_id){
	if(level_id == "1")
		return new MBLevel(255, 0, 0, "1", "");
	else
		return nullptr;
}

void MBLevelFactory::release(Level *level){
	delete level;
}
