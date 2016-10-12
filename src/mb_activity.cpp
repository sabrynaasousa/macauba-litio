#include "mb_activity.h"

MBActivity::MBActivity(){

}

MBActivity::MBActivity(int c_id_activity, int c_id_in, int c_id_intermediary, int c_id_out1, int c_id_out2, int c_id_treatment){
    m_id_activity = c_id_activity;
    m_id_in = c_id_in;
    m_id_intermediary = c_id_intermediary;
    m_id_out1 = c_id_out1;
    m_id_out2 = c_id_out2;
    m_id_treatment = c_id_treatment;
}

int MBActivity::id_activity(){
    return m_id_activity;
}

int MBActivity::MBActivity::id_in(){
    return m_id_in;
}

int MBActivity::id_intermediary(){
    return m_id_intermediary;
}
int MBActivity::id_out1(){
    return m_id_out1;
}

int MBActivity::id_out2(){
    return m_id_out2;
}

int MBActivity::id_treatment(){
    return m_id_treatment;
}