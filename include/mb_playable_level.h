#ifndef MB_PLAYABLE_LEVEL_H
#define MB_PLAYABLE_LEVEL_H

#define LEVEL 0

#include "mb_level.h"
#include "mb_activity.h"

class MBPlayableLevel : public MBLevel {
    public:
        MBPlayableLevel(int r, int g, int b, const string &current, const string &next = "", const string &audio_path = "");
        ~MBPlayableLevel();

        bool done() const;
        string next() const;
        string audio() const;
        string current_level() const;
        void do_action(string label);
        void show_confirmation_button(double percentage);
        void hide_confirmation_button();

        bool on_event(const GameEvent& event);

    protected:
        void update_self(unsigned now, unsigned last);
        void draw_self(Canvas *canvas, unsigned now, unsigned last);

    private:
        int n_activities, n_ins, n_intermediaries, n_outs1, n_outs2, n_treatments;
        int n_trail_activities, id_initial_intermediary;
        vector<MBActivity *> m_activities;
        double m_level_percentage;
};

#endif
