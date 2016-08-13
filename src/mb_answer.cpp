#include "mb_answer.h"

#include <iostream>
#include <fstream>

using namespace std;

MBAnswer::MBAnswer(){
	answer = fopen("res/answer.dat", "rb");

	if(not answer){
		printf("Não foi possível abrir o arquivo gabarito.dat\n");
		exit(1);
	}

	fread(&n_levels, sizeof(int), 1, answer);

	int id_level = 1;
	while(fread(&n_frames, sizeof(int), 1, answer)>0){
		fread(m_level_answer[id_level++], sizeof(int), 3 * n_frames, answer);
	}

	fclose(answer);
}

int *MBAnswer::in_trail(int level){
	return m_level_answer[level][0];
}

int *MBAnswer::main_trail(int level){
	return m_level_answer[level][1];
}

int *MBAnswer::out_trail(int level){
	return m_level_answer[level][2];
}

MBAnswer::~MBAnswer(){
	fclose(answer);
	free(m_level_answer);
}
