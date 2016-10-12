#ifndef MB_PLAYABLE_LEVEL_H
#define MB_PLAYABLE_LEVEL_H

#define LEVEL 1

#include "mb_level.h"
#include "mb_activity.h"

class MBPlayableLevel : public MBLevel{
    public:
        MBPlayableLevel(int r, int g, int b, const string &current, const string &next = "", const string &audio_path = "");

        bool done() const;
        string next() const;
        string audio() const;
        string current_level() const;
        void do_action(string label);

        bool on_event(const GameEvent& event);

    protected:
        void update_self(unsigned now, unsigned last);
        void draw_self(Canvas *canvas, unsigned now, unsigned last);

    private:
        int n_activities, n_ins, n_intermediary, n_outs1, n_outs2, n_treatments;
        int n_trail_activities;
        vector<MBActivity *> m_activities;
};

#endif
