#include "mb_piece.h"
#include "mb_frame.h"
#include "mb_toolbar.h"

MBPiece::MBPiece(){

}

MBPiece::MBPiece(std::string current_level, double px, double py, int piece_id, std::string piece_type){
    if(PIECE) printf("Construindo piece\n");
    m_speed = 2;
    m_start = -1;
    m_id = piece_id;
    m_type = piece_type;
    m_last_following = -1;

    m_height = m_width = 30;
    m_y = m_original_y = py;
    m_x = m_original_x = px;
    m_frame_id = -1;
    m_moving = false;

    set_priority(1);
    if(piece_type == "activity"){
        m_height = 144;
        m_width = m_draw_width = 253;
        m_draw_height = 163;
    }

    else if(piece_type == "in"){
        m_height = 72;
        m_width = m_draw_width = 66;
        m_draw_height = 91;
    }

    else if(piece_type == "intermediary"){
        m_height = m_draw_height = 80;
        m_width = m_draw_width = 80;
    }

    else if(piece_type == "out1"){
        m_height = m_draw_height = 65;
        m_width = m_draw_width = 72;
    }

    else if(piece_type == "out2"){
        m_height = m_draw_height = 65;
        m_width = m_draw_width = 73;
    }

    else if(piece_type == "treatment"){
        m_height = m_draw_height = 67;
        m_width = m_draw_width = 143;
    }

    else{
        printf("Invalid piece type\n");
        exit(-1);
    }

    set_priority(1);

    m_texture[0] = resources::get_texture(current_level + "/" + m_type + "_" + to_string(m_id) + ".png");
    m_texture[1] = resources::get_texture(current_level + "/" + m_type + "_" + to_string(m_id) + "_placed.png");
    m_bounding_box = Rectangle(m_x, m_y, m_width, m_height);
    m_active = true;
    m_following = false;
    physics::register_object(this);
    event::register_listener(this);
    if(PIECE) printf("Construiu piece\n");
}

MBPiece::~MBPiece(){
    event::unregister_listener(this);
    physics::unregister_object(this);
}

bool MBPiece::following() const{ return m_following; }
double MBPiece::x() const{ return m_x; }
double MBPiece::y() const{ return m_y; }
std::string MBPiece::type() const{ return m_type; }
double MBPiece::height(){ return m_height; }
double MBPiece::width(){ return m_width; }
bool MBPiece::moving() const{ return m_moving; }
double MBPiece::last_following() const{ return m_last_following; }
int MBPiece::frame_id() const{ return m_frame_id; }
int MBPiece::id() const{ return m_id; }
shared_ptr<Texture> MBPiece::texture(){ return m_texture[0]; }

void MBPiece::set_x(double cx) { m_x = cx; }
void MBPiece::set_y(double cy) { m_y = cy; }
void MBPiece::set_height(double ch) { m_height = ch; }    

void MBPiece::register_self(int current_x){
    m_x = current_x;
    m_bounding_box = Rectangle(current_x, m_y, m_width, m_height);
    m_active = true;
    physics::register_object(this);
}

bool MBPiece::on_event(const GameEvent& event){
    if(not active()) return false;

    MBToolbar * p;
    if( !(p = dynamic_cast<MBToolbar *>( parent() ) ) ){
        printf("Invalid toolbar parent\n");
        exit(-5);
    }

    if(event.id() == GAME_MOUSE_PRESSED ) printf("Clicou %d %d\n", p->get_following(), m_following);
    if(event.id() == GAME_MOUSE_PRESSED && (p->get_following() == m_following)){
        double mouse_x = event.get_property<double>("x");
        double mouse_y = event.get_property<double>("y");
        if(mouse_x >= m_x && mouse_x <= m_x + m_width && mouse_y >= m_y && mouse_y <= m_y + m_height){
            m_following = !m_following;
            if(not m_following){
                m_last_following = m_start;
            }
            p->set_following(m_following);
            m_frame_id = -1;

            printf("Clicou na %d\n", m_id);
            return true;
        }else{
            printf("Nao clicou na %d\n", m_id);
        }
    }

    if(m_following){
        double mouse_x = event.get_property<double>("x");
        double mouse_y = event.get_property<double>("y");
        m_x = mouse_x - m_width/2;
        m_y = mouse_y - m_height/2;
        printf("%d\n", m_id);
        set_priority(30);

        return true;
    }else{
        set_priority(2);
    }
    //printf("Event x, y => [%f, %f]\n", event.get_property<double>("x"), event.get_property<double>("y"));

    return false;
}

void MBPiece::set_active(bool c_active){
    m_active = c_active;
}

bool MBPiece::active() const{
    return m_active or m_moving;
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

void MBPiece::on_collision(const Collidable *collidable, const Rectangle& r, const unsigned now, const unsigned){
    if(auto p = dynamic_cast<const MBFrame *>(collidable)){
        if(r.area() >= p->minimum_area() && not m_following && (now - m_last_following) < 20 && p->piece() == nullptr && m_type == p->type()){
            m_x = p->x();
            m_y = p->y();
            m_frame_id = p->id();
        }
        //printf("area do ret: %.2f\n", r.area());
    }
    //printf("MBPiece colidiu em %.2f,%.2f em %u-%u\n", where.x(), where.y(), now, last);
    
}

void MBPiece::update_self(unsigned now, unsigned) {
    if(PIECE) printf("Entrou update piece\n");
    if(m_start == -1){
        m_start = now;
    }

    //printf("%f, %f\n", m_x, m_y);
    m_bounding_box = Rectangle(m_x + m_width/2, m_y + m_height/2, m_width, m_height);
    l.clear();
    l.insert(l.begin(), m_bounding_box);

    if(not m_following && m_frame_id == -1){
        m_moving = false;

        if(abs(m_x - m_original_x) > 1){
            m_x += (now - m_start) * m_speed * (m_x - m_original_x > 0 ? -1 : 1);
            m_moving = true;
        }

        if(abs(m_y - m_original_y) > 1){
            m_y += (now - m_start) * m_speed * (m_y - m_original_y > 0 ? -1 : 1);
            m_moving = true;
        }
    }

    m_start = now;
    if(PIECE) printf("Saiu update piece\n");
}

void MBPiece::draw_self(Canvas* canvas, unsigned, unsigned) {
    if(PIECE) printf("Entrando draw_self piece\n");
    if(active()) canvas->draw(m_texture[m_frame_id != -1].get(), Rectangle(0, 0, m_draw_width, m_draw_height), m_x, m_y);
    if(PIECE) printf("Saindo draw self piece\n");
}
