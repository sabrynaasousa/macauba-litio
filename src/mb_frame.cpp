#include "mb_frame.h"
#include "mb_piece.h"

MBFrame::MBFrame(){

}

MBFrame::MBFrame(std::string current_level, double px, double py, int id){
    m_sprite_speed = 0;
    m_sprite_counter = 0;
    m_start = -1;
    m_id = id;

    m_height = m_width = 60;
    m_y = py;
    m_x = px;

    m_texture = resources::get_texture("square.jpg");
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
shared_ptr<Texture> MBFrame::texture(){ return m_texture; }

void MBFrame::set_x(double cx) { m_x = cx; }
void MBFrame::set_y(double cy) { m_y = cy; }
void MBFrame::set_height(double ch) { m_height = ch; }    

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
        int id_piece = p->id();
        //printf("(%f , %f) x (%f, %f)\n", m_x, m_y, p->x(), p->y());

        printf("%f x %f (%f, %f)\n", rectangle.area(), p->bounding_box().area(), rectangle.x(), rectangle.y());
        if(/*id_piece == m_id &&*/ rectangle.area() == p->bounding_box().area() && not p->following()){
            printf("TO DENTRO\n");
        }
    }
    //printf("MBFrame colidiu em %.2f,%.2f em %u-%u\n", where.x(), where.y(), now, last);
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
		canvas->draw(m_texture.get(), Rectangle(m_width * ((int) m_sprite_counter), 0, m_width, m_height), m_x, m_y);
}

