#ifndef MB_TOOLBAR_H
#define MB_TOOLBAR_H

#include <ijengine/rectangle.h>
#include <ijengine/game_object.h>

#include "mb_piece.h"

using namespace ijengine;

class MBToolbar : public GameObject{
	public:
		MBToolbar(std::string current_level, int r, int g, int b, int w, int h);

	protected:
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);

	private:
		int m_r, m_g, m_b;
		Rectangle m_rectangle;
		vector <MBPiece *> m_pieces;
};

#endif
