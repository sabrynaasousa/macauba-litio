#ifndef MB_LEVEL_H
#define MB_LEVEL_H

#include <ijengine/level.h>
#include <string>

#include "mb_button.h"
#include "mb_activity.h"

using std::string;
using ijengine::Level;
using ijengine::Canvas;

class MBLevel : public Level, GameEventsListener{
	public:
		MBLevel(int r, int g, int b, const string &current, const string &next = "", const string &audio_path = "");

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
		int m_r, m_g, m_b;
		bool m_done;
		string m_next, m_audio_path, m_current_level;
		string m_level_name;
		int m_start;
		int n_activities, n_ins, n_intermediary, n_outs1, n_outs2, n_treatments;
		int n_trail_activities;
		vector<MBActivity *> m_activities;
		shared_ptr<Texture> m_background;
		vector< MBButton* > m_buttons;
};

#endif
