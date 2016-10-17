#include "mb_trail.h"
#include "mb_answer.h"

#include <ijengine/canvas.h>

MBTrail::MBTrail(std::string current_level, vector<MBActivity *> activities, int number_of_activities){
	if(TRAIL) printf("Construindo Trail\n");
	m_percentage = 0;
	m_face_texture[0] = resources::get_texture("sad.png");
	m_face_texture[1] = resources::get_texture("ok.png");
	m_face_texture[2] = resources::get_texture("happy.png");

	MBAnswer *answer = new MBAnswer();

	n_frames = answer->n_frames(atoi(current_level.c_str())); 

	int offset = 300;
	int id_frame = 0;

	for(int i = 0; i < number_of_activities; ++i){
		MBActivity * activity = activities[i];

		int mask = 0;
		if(i > 0){
			if(activities[i-1]->id_intermediary()) mask += 1 << ACTIVITY;
		}

		mask += (activity->id_in() << IN) + (activity->id_intermediary() << INTERMEDIARY) + (activity->id_out1() << OUT1) + (activity->id_out2() << OUT2);
		printf("Mask = %d\n", mask);

		if(activity->id_activity()){
			MBFrame * frame = new MBFrame(current_level, "activity", offset + 250 * (i - 1), 178, activity->id_activity(), id_frame++, mask);
			frames[ACTIVITY].push_back(frame);
			add_child(frame);
		}else{
			printf("Null activity\n");
			exit(-1);
		}

		if(activity->id_in()){
			MBFrame * frame = new MBFrame(current_level, "in", offset + 250 * (i - 1), 108, activity->id_in(), id_frame++, mask);
			frames[IN].push_back(frame);
			add_child(frame);
		}

		if(activity->id_intermediary()){
			//FIX MY POSITION
			MBFrame * frame = new MBFrame(current_level, "intermediary", offset + 210 + 250 * (i - 1), 210, activity->id_intermediary(), id_frame++, mask);
			frames[INTERMEDIARY].push_back(frame);
			add_child(frame);
		}

		if(activity->id_out1()){
			MBFrame * frame = new MBFrame(current_level, "out1", offset + 20 + 250 * (i - 1), 320, activity->id_out1(), id_frame++, mask);
			frames[OUT1].push_back(frame);
			add_child(frame);
		}

		if(activity->id_out2()){
			MBFrame * frame = new MBFrame(current_level, "out2", offset + 145 + 250 * (i - 1), 320, activity->id_out2(), id_frame++, mask);
			frames[OUT2].push_back(frame);
			add_child(frame);
		}

		if(activity->id_treatment()){
			MBFrame * frame = new MBFrame(current_level, "treatment", offset - 13 + 250 * (i - 1), 358, activity->id_treatment(), id_frame++, mask);
			frames[TREATMENT].push_back(frame);
			add_child(frame);
		}
	}

	// type = "in";
	// for(int i = 1; i <= n_frames; i++){
	// 	frames[1][i] = new MBFrame(current_level, type, p_x + 170 * (i - 1), 108, answer->piece(atoi(current_level.c_str()), i, 0), id_frame++);
	// 	add_child(frames[1][i]);
	// }

	// type = "main";
	// for(int i = 1; i <= n_frames; i++){
	// 	frames[2][i] = new MBFrame(current_level, type, p_x + 170 * (i - 1), 178, answer->piece(atoi(current_level.c_str()), i, 1), id_frame++);
	// 	add_child(frames[2][i]);
	// }

	// type = "out";
	// for(int i = 1; i <= n_frames; i++){
	// 	frames[3][i] = new MBFrame(current_level, type, p_x + 48 + 170 * (i - 1), 320, answer->piece(atoi(current_level.c_str()), i, 2), id_frame++);
	// 	add_child(frames[3][i]);
	// }


	// type = "treatment";
	// for(int i = 1; i <= n_frames; i++){
	// 	frames[4][i] = new MBFrame(current_level, type, p_x + 15 + 170 * (i - 1), 358, answer->piece(atoi(current_level.c_str()), i, 3), id_frame++);
	// 	add_child(frames[4][i]);
	// }
	if(TRAIL) printf("Construiu Trail\n");
}

void MBTrail::update_self(unsigned, unsigned){
	if(TRAIL) printf("Entrando update_self trail\n");
	int n_filled_frames = 0;
	int correct = 0;

	for(int type = 0; type <= 5; type++){
		for(auto frame : frames[type]){
			if(frame->is_right())
				correct++;

			if(frame->filled())
				n_filled_frames++;
		}
	}

	if(n_filled_frames)
		m_percentage = (double)correct/n_filled_frames * 100.0;
	else
		m_percentage = 0;
	if(TRAIL) printf("Saindo update_self trail\n");
}

void MBTrail::draw_self(Canvas *canvas, unsigned, unsigned){
	if(TRAIL) printf("Entrando draw_self trail\n");
	canvas->draw(m_face_texture[min((int)(m_percentage/(100.0/3)+1e-8), 2)].get(), Rectangle(0, 0, 60, 60), 930, 20);

/*
	auto font = resources::get_font("Forelle.ttf", 40);
	canvas->set_font(font);

	canvas->set_draw_color(Color(0, 0, 0));
	canvas->draw(to_string(m_percentage) + " %", 800, 20);
*/
	if(TRAIL) printf("Saindo draw_self trail\n");
}
