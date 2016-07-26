#ifndef MB_LEVEL_H
#define MB_LEVEL_H

#include <ijengine/level.h>
#include <string>

using std::string;
using ijengine::Level;
using ijengine::Canvas;

class MBLevel : public Level{
	public:
		MBLevel(int r, int g, int b, const string &next = "", const string &audio_path = "");

		bool done() const;
		string next() const;
		string audio() const;

	protected:
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);

	private:
		int m_r, m_g, m_b;
		bool m_done;
		string m_next, m_audio_path;
		int m_start;
};

#endif
