#ifndef MB_TRAIL_H
#define MB_TRAIL_H

#define TRAIL 0

#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#include "mb_frame.h"
#include "mb_activity.h"

#include <string>
#include <vector>

using namespace ijengine;

class MBTrail : public GameObject{
	public:
		typedef enum {OUT2 = 0, OUT1 = 1, INTERMEDIARY = 2, IN = 3, ACTIVITY = 4, TREATMENT = 5} Types;
		MBTrail(std::string current_level, vector<MBActivity *> activities, int number_of_activities);

	protected:
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);

	private:
        double m_x, m_y;
		double m_percentage;
		int n_frames;
		vector<MBFrame *> frames[6];
        shared_ptr<Texture> m_face_texture[5];
};

#endif
