#ifndef MB_LEVEL_FACTORY_H
#define MB_LEVEL_FACTORY_H

#include <ijengine/level_factory.h>
#include "mb_playable_level.h"

using namespace ijengine;

class MBLevelFactory : public LevelFactory{
	public:
		Level *make_level(const string &level_id);
		void release(Level *level);
};

#endif
