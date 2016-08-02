#include "mb_piece.h"

MBPiece::MBPiece(){

}

MBPiece::MBPiece(std::string current_level, double ch, int piece_id){
    m_sprite_speed = 0;
    m_sprite_counter = 0;
    m_start = -1;
    m_id = piece_id;

    m_height = m_width = 30;
    m_y = 400;
    m_x = 50;

    m_texture = resources::get_texture(current_level + "/piece_" + to_string(m_id) + ".png");
    m_bounding_box = Rectangle(m_x, m_y, m_width, m_height);
    m_active = true;
    physics::register_object(this);
}

MBPiece::~MBPiece(){
    physics::unregister_object(this);
}

double MBPiece::x(){ return m_x; }
double MBPiece::y(){ return m_y; }
double MBPiece::height(){ return m_height; }
double MBPiece::width(){ return m_width; }
shared_ptr<Texture> MBPiece::texture(){ return m_texture; }

void MBPiece::set_x(double cx) { m_x = cx; }
void MBPiece::set_y(double cy) { m_y = cy; }
void MBPiece::set_height(double ch) { m_height = ch; }    

void MBPiece::register_self(int current_x){
    m_x = current_x;
    m_bounding_box = Rectangle(current_x, m_y, m_width, m_height);
    m_active = true;
    physics::register_object(this);
}

bool MBPiece::active() const{
    return m_active;
}

pair<double, double> MBPiece::direction() const{
    pair<double, double> p(0,0);
    return p;
}

const Rectangle& MBPiece::bounding_box() const{
    return m_bounding_box;
}

const list<Rectangle>& MBPiece::hit_boxes() const{
    return l;
}

void MBPiece::on_collision(const Collidable *, const Rectangle&, const unsigned, const unsigned){
    //printf("MBPiece colidiu em %.2f,%.2f em %u-%u\n", where.x(), where.y(), now, last);
    m_active = false;
}

void MBPiece::update_self(unsigned now, unsigned) {
    if(m_start == -1){
        m_start = now;
    }

    m_bounding_box = Rectangle(m_x, m_y, m_width, m_height);
    l.clear();
    l.insert(l.begin(), m_bounding_box);

    m_sprite_counter += (now - m_start) * m_sprite_speed;
    if(m_sprite_counter > 5.9){
        m_sprite_counter -= 5.9;
    }

    m_start = now;
}
void MBPiece::draw_self(Canvas* canvas, unsigned, unsigned) {
    if(m_active) canvas->draw(m_texture.get(), Rectangle(m_width * ((int) m_sprite_counter), 0, m_width, m_height), m_x, m_y);
}

