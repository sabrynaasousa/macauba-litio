#ifndef MB_TRAIL_H
#define MB_TRAIL_H

#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#include "mb_frame.h"

#include <string>

using namespace ijengine;

class MBTrail : public GameObject{
	public:
		MBTrail(std::string current_level, double p_x, double p_y);

	protected:
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);

	private:
        double m_x, m_y;
		double m_percentage;
		int n_frames;
		MBFrame *frames[100][100];
        shared_ptr<Texture> m_face_texture[5];
};

#endif
