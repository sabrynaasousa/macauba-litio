#ifndef MB_TOOLBAR_H
#define MB_TOOLBAR_H

#define TOOLBAR 0

#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#include "mb_piece.h"

using namespace ijengine;

class MBToolbar : public GameObject{
	public:
		MBToolbar(std::string current_level, int r, int g, int b);
        void set_following(bool following);
        bool get_following();

	protected:
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);

	private:
		int m_r, m_g, m_b;
		int m_w, m_h, m_x, m_y;
        bool m_following;
		vector <MBPiece *> m_pieces;
        shared_ptr<Texture> m_background;
};

#endif
