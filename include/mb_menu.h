#ifndef MB_MENU_H
#define MB_MENU_H

#include "mb_level.h"
#include "mb_button.h"

#include <ijengine/canvas.h>
#include <ijengine/engine.h>
#include <ijengine/keyboard_event.h>

#include <iostream>
#include <fstream>
#include <vector>


class MBMenu : public MBLevel {
    public:
        MBMenu(const string& current_level, const string& next_level = "", const string audio_path = "", int audio_duration = -1);
        MBMenu(int r, int g, int b, const string &current, const string &next = "", const string &audio_path = "");
        ~MBMenu();

        bool done() const;
        string next() const;
        string audio() const;
        void do_action(string label);

        bool on_event(const GameEvent& event);

    protected:
        void update_self(unsigned, unsigned last);
        void draw_self(Canvas *canvas, unsigned, unsigned last);
};

#endif
