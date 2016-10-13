#ifndef MB_LEVEL_H
#define MB_LEVEL_H

#include "mb_button.h"

#include <string>
#include <memory>
#include <ijengine/level.h>
#include <ijengine/texture.h>
#include <ijengine/events_translator.h>
#include <ijengine/game_events_listener.h>
#include <ijengine/game_object.h>

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/rectangle.h>

#include <deque>
#include <vector>

using namespace std;
using namespace ijengine;

class MBLevel : public Level, public GameEventsListener {
	public:
		~MBLevel(){}

	protected:
        typedef enum { ACTIVITY, IN, INTERMEDIARY, OUT1, OUT2, TREATMENT } Types;

        int m_r, m_g, m_b;
        bool m_done;
        string m_next, m_audio, m_audio_path, m_current_level;
        string m_level_name;
        int m_start;
        shared_ptr<Texture> m_background;
        vector< MBButton* > m_buttons;
};

#endif