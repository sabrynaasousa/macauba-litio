#ifndef MB_ANSWER_H
#define MB_ANSWER_H

#include <iostream>

using namespace std;

class MBAnswer{
	public:
		MBAnswer();
		~MBAnswer();

		int *in_trail(int level);
		int *main_trail(int level);
		int *out_trail(int level);

	private:
		int m_level_answer[30][5][100];
		int n_frames;
		int n_levels;

		FILE *answer;
};

#endif
