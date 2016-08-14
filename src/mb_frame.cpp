#include "mb_frame.h"
#include "mb_piece.h"
#include "mb_answer.h"

MBFrame::MBFrame(){

}

MBFrame::MBFrame(std::string current_level, int type, double px, double py, int id_piece){
	m_correct_piece = id_piece;
    m_sprite_speed = 0;
    m_sprite_counter = 0;
    m_start = -1;
	m_is_right = false;
	m_type = type;

	if(type == 0){
		m_height = 72;
		m_width = 66;
	}else if(type == 1){
		m_height = 144;
		m_width = 173;
	}else if(type == 2){
		m_height = 65;
		m_width = 72;
	}else{
		m_height = 67;
		m_width = 143;
	}

    m_y = py;
    m_x = px;

	if(type == 0)
		m_texture = resources::get_texture("in.png");
	else if(type == 1)
		m_texture = resources::get_texture("main.png");
	else if(type == 2)
		m_texture = resources::get_texture("out.png");
	else
		m_texture = resources::get_texture("treatment.png");
		
    m_bounding_box = Rectangle(m_x, m_y, m_width, m_height);
    m_active = true;

    physics::register_object(this);
    event::register_listener(this);
}

MBFrame::~MBFrame(){
    event::unregister_listener(this);
    physics::unregister_object(this);
}

double MBFrame::x(){ return m_x; }
double MBFrame::y(){ return m_y; }
double MBFrame::height(){ return m_height; }
double MBFrame::width(){ return m_width; }
bool MBFrame::is_right() { return m_is_right; }
shared_ptr<Texture> MBFrame::texture(){ return m_texture; }

void MBFrame::set_x(double cx) { m_x = cx; }
void MBFrame::set_y(double cy) { m_y = cy; }
void MBFrame::set_height(double ch) { m_height = ch; }    
void MBFrame::set_right(){ m_is_right = true; }

void MBFrame::register_self(int current_x){
    m_x = current_x;
    m_bounding_box = Rectangle(current_x, m_y, m_width, m_height);
    m_active = true;
    physics::register_object(this);
}

bool MBFrame::on_event(const GameEvent& event){
    return false;
}

bool MBFrame::active() const{
    return m_active;
}

pair<double, double> MBFrame::direction() const{
    pair<double, double> p(0,0);
    return p;
}

const Rectangle& MBFrame::bounding_box() const{
    return m_bounding_box;
}

const list<Rectangle>& MBFrame::hit_boxes() const{
    return l;
}

void MBFrame::on_collision(const Collidable * piece, const Rectangle& rectangle, const unsigned, const unsigned){
	if(auto p = dynamic_cast<const MBPiece *>(piece)){
        //printf("(%f , %f) x (%f, %f)\n", m_x, m_y, p->x(), p->y());

        int id_piece = p->id();

        printf("Colidiu\n");
        //printf("%f x %f (%f, %f)\n", rectangle.area(), p->bounding_box().area(), rectangle.x(), rectangle.y());
        if(rectangle.area() == p->bounding_box().area() && not p->following()){

			if(id_piece == m_correct_piece){
				m_is_right = true;
			}else{
				m_is_right = false;
			}
        }else if(id_piece == m_correct_piece){
			m_is_right = false;
		}
    }
    // printf("MBFrame colidiu em %.2f,%.2f em %u-%u\n", where.x(), where.y(), now, last);
}

void MBFrame::update_self(unsigned now, unsigned) {
    if(m_start == -1){
        m_start = now;
    }

    m_bounding_box = Rectangle(m_x, m_y, m_width, m_height);
    l.clear();
    l.insert(l.begin(), m_bounding_box);

    m_start = now;
}

void MBFrame::draw_self(Canvas* canvas, unsigned, unsigned) {
    if(m_active)
		canvas->draw(m_texture.get(), Rectangle(m_width * ((int) m_sprite_counter), 0, m_width, m_height), m_x - m_width/2, m_y - m_height/2);
}
