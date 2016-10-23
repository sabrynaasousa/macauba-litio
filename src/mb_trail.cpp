#include "mb_trail.h"
#include "mb_answer.h"

#include <ijengine/canvas.h>

MBTrail::MBTrail(std::string current_level, vector<MBActivity *> activities, int number_of_activities, int id_initial_intermediary){
	if(TRAIL) printf("Construindo Trail\n");
	m_percentage = 0;
	m_face_texture[0] = resources::get_texture("sad.png");
	m_face_texture[1] = resources::get_texture("ok.png");
	m_face_texture[2] = resources::get_texture("happy.png");

	MBAnswer *answer = new MBAnswer();

	n_frames = answer->n_frames(atoi(current_level.c_str())); 

	int offset = 300;
	int id_frame = 0;

	if(id_initial_intermediary){
		int initial_intermediary_x = offset + INTERMEDIARY_OFFSET + ACTIVITY_DISTANCE * (-2);
		MBFrame * frame = new MBFrame(current_level, "intermediary", initial_intermediary_x, INTERMEDIARY_Y, id_initial_intermediary, id_frame++, 0);
		frames[INTERMEDIARY].push_back(frame);
		add_child(frame);
	}

	for(int i = 0; i < number_of_activities; ++i){
		MBActivity * activity = activities[i];

		int mask = 0;
		if(i > 0){
			if(activities[i-1]->id_intermediary()) mask += 1 << ACTIVITY;
		}else{
			if(id_initial_intermediary) mask += 1 << ACTIVITY;
		}

		mask += ((activity->id_in() != 0) << IN) + ((activity->id_intermediary()!= 0) << INTERMEDIARY) + ((activity->id_out1()!= 0) << OUT1) + ((activity->id_out2()!= 0) << OUT2);
		printf("Mask = %d\n", mask);

		if(activity->id_activity()){
			int activity_x = offset + ACTIVITY_DISTANCE * (i - 1);
			MBFrame * frame = new MBFrame(current_level, "activity", activity_x, ACTIVITY_Y, activity->id_activity(), id_frame++, mask);
			frames[ACTIVITY].push_back(frame);
			add_child(frame);
		}else{
			printf("Null activity\n");
			exit(-1);
		}

		if(activity->id_in()){
			int in_x = offset + ACTIVITY_DISTANCE * (i - 1);
			MBFrame * frame = new MBFrame(current_level, "in", in_x, IN_Y, activity->id_in(), id_frame++, mask);
			frames[IN].push_back(frame);
			add_child(frame);
		}

		if(activity->id_intermediary()){
			int intermediary_x = offset + INTERMEDIARY_OFFSET + ACTIVITY_DISTANCE * (i - 1);
			MBFrame * frame = new MBFrame(current_level, "intermediary", intermediary_x, INTERMEDIARY_Y, activity->id_intermediary(), id_frame++, mask);
			frames[INTERMEDIARY].push_back(frame);
			add_child(frame);
		}

		if(activity->id_out1()){
			int out1_x = offset + OUT1_OFFSET + ACTIVITY_DISTANCE * (i - 1);
			MBFrame * frame = new MBFrame(current_level, "out1", out1_x, OUT1_Y, activity->id_out1(), id_frame++, mask);
			frames[OUT1].push_back(frame);
			add_child(frame);
		}

		if(activity->id_out2()){
			int out2_x = offset + OUT2_OFFSET + ACTIVITY_DISTANCE * (i - 1);
			MBFrame * frame = new MBFrame(current_level, "out2", out2_x, OUT2_Y, activity->id_out2(), id_frame++, mask);
			frames[OUT2].push_back(frame);
			add_child(frame);
		}

		if(activity->id_treatment()){
			int treatment_x = offset + TREATMENT_OFFSET + ACTIVITY_DISTANCE * (i - 1);
			MBFrame * frame = new MBFrame(current_level, "treatment", treatment_x, TREATMENT_Y, activity->id_treatment(), id_frame++, mask);
			frames[TREATMENT].push_back(frame);
			add_child(frame);
		}
	}

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
	canvas->draw(m_face_texture[min((int)(m_percentage/(100.0/3)+1e-8), 2)].get(), Rectangle(0, 0, 60, 60), 1290, 80);

/*
	auto font = resources::get_font("Forelle.ttf", 40);
	canvas->set_font(font);

	canvas->set_draw_color(Color(0, 0, 0));
	canvas->draw(to_string(m_percentage) + " %", 800, 20);
*/
	if(TRAIL) printf("Saindo draw_self trail\n");
}
