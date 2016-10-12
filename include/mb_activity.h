#ifndef MB_ACTIVITY_H
#define MB_ACTIVITY_H

#include <ijengine/engine.h>
#include <ijengine/collidable.h>
#include <ijengine/canvas.h>
#include <ijengine/texture.h>
#include <ijengine/game_object.h>
#include <ijengine/events_translator.h>
#include <ijengine/game_events_listener.h>

#include <string>
#include <list>

using std::shared_ptr;
using namespace ijengine;
using std::to_string;
using std::string;

class MBActivity {
public:
    MBActivity();
    MBActivity(int c_id_activity, int c_id_in, int c_id_intermediary, int c_id_out1, int c_id_out2, int c_id_treatment);
    int id_activity();
    int id_in();
    int id_intermediary();
    int id_out1();
    int id_out2();
    int id_treatment();
private:
    int m_id_activity, m_id_in, m_id_intermediary, m_id_out1, m_id_out2, m_id_treatment;
};

#endif
