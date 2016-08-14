#ifndef MB_ANSWER_H
#define MB_ANSWER_H

#include <iostream>

using namespace std;

class MBAnswer{
	public:
		MBAnswer();
		~MBAnswer();

		int n_frames(int level);
		int piece(int level, int frame, int type);

	private:
		int m_level_answer[30][5][100];
		int m_frames[30];
		int n_levels;

		FILE *answer;
};

#endif
