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
		static const int ACTIVITY_DISTANCE = 249;
		static const int OUT1_OFFSET = 20;
		static const int OUT2_OFFSET = 145;
		static const int TREATMENT_OFFSET = OUT1_OFFSET - 33;
		static const int INTERMEDIARY_OFFSET = 211;

		static const int ACTIVITY_Y = 178;
		static const int IN_Y = ACTIVITY_Y - 70;
		static const int INTERMEDIARY_Y = ACTIVITY_Y + 32;
		static const int OUT1_Y = ACTIVITY_Y + 142;
		static const int OUT2_Y = OUT1_Y;
		static const int TREATMENT_Y = OUT1_Y + 38;
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
