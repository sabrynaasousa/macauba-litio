#include "mb_frame.h"
#include "mb_piece.h"
#include "mb_answer.h"

MBFrame::MBFrame(){

}

MBFrame::MBFrame(std::string current_level, std::string frame_type, double px, double py, int id_piece, int frame_id){
	m_correct_piece = id_piece;
    m_sprite_speed = 0;
    m_sprite_counter = 0;
    m_start = -1;
	m_is_right = false;
	m_type = frame_type;
    m_id = frame_id;

	if(m_type == "in"){
		m_height = 72;
		m_width = 66;
        m_minimum_area = 2500;
	}else if(m_type == "main"){
		m_height = 144;
		m_width = 173;
        m_minimum_area = 16000;
	}else if(m_type == "out"){
		m_height = 65;
		m_width = 72;
        m_minimum_area = 2500;
	}else{
		m_height = 67;
		m_width = 143;
        m_minimum_area = 500;
	}

    m_y = py;
    m_x = px;

	m_texture = resources::get_texture(m_type + ".png");
		
    m_bounding_box = Rectangle(m_x, m_y, m_width, m_height);
    m_active = true;
    m_piece = nullptr;

    physics::register_object(this);
    event::register_listener(this);
}

MBFrame::~MBFrame(){
    event::unregister_listener(this);
    physics::unregister_object(this);
}

double MBFrame::x() const{ return m_x; }
double MBFrame::y() const{ return m_y; }
int MBFrame::id() const{ return m_id; }
string MBFrame::type() const{ return m_type; }
const MBPiece * MBFrame::piece() const{ return m_piece; }
double MBFrame::height(){ return m_height; }
double MBFrame::width(){ return m_width; }
bool MBFrame::is_right() { return m_is_right; }
shared_ptr<Texture> MBFrame::texture(){ return m_texture; }
double MBFrame::minimum_area() const{ return m_minimum_area; }

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
        if(rectangle.area() >= m_minimum_area && not p->following() && m_piece == nullptr && p->type() == m_type){
			if(id_piece == m_correct_piece){
				m_is_right = true;
			}else{
				m_is_right = false;
			}
            m_piece = p;
        }
    }
    // printf("MBFrame colidiu em %.2f,%.2f em %u-%u\n", where.x(), where.y(), now, last);
}

void MBFrame::update_self(unsigned now, unsigned) {
    printf("Entrou update frame\n");
    if(m_start == -1){
        m_start = now;
    }

    m_bounding_box = Rectangle(m_x + m_width/2, m_y + m_height/2, m_width, m_height);
    l.clear();

    if(m_type != "treatment"){
        l.insert(l.begin(), m_bounding_box);
    }else{
        l.insert(l.begin(), Rectangle(m_x + 35.0/2, m_y + 27.0/2, 35, 27));
        l.insert(l.begin(), Rectangle(m_x + 143.0/2, m_y + 40 + 40.0/2, 143, 40));
        l.insert(l.begin(), Rectangle(m_x + 103 + 40.0/2, m_y + 27.0/2, 40, 27));
    }

    if(m_piece != nullptr){
        if(m_piece->frame_id() != m_id){
            m_piece = nullptr;
        }
    }

    m_start = now;
    printf("Saiu update frame\n");
}

void MBFrame::draw_self(Canvas* canvas, unsigned, unsigned) {
    if(m_active)
		canvas->draw(m_texture.get(), Rectangle(m_width * ((int) m_sprite_counter), 0, m_width, m_height), m_x, m_y);
}
