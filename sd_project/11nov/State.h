#ifndef __STATE_H__
#define __STATE_H__

#include<iostream>
using namespace std;
#include"code.h"

class State{

  
    
    Machine* building[5]; //changed from dynamic to static
    bool again;
    int number;
    string screen_text;
    

  public: 

    static const int offset;

    string get_screen_text() const {
        return screen_text;
    }

    Machine* const* get_building() const { 
       return building; 
    }

    bool get_again() const {
        return again;
    }

    int get_number() const {
        return number;
    }

    State(istream &is);
void update(string input);
void update(){
        // if(_received_event()){
        // if (_event_id_is("button_", 1)) {
        // cout<<"HAHAHA";
        // }
        // }
}
 void write_to(ostream &os) const;

 int size_in_bytes () const {
     ostringstream oss;
     write_to(oss);
     return oss.str().size();
 }

//    int offset_for_num_moves() const; // mayb we need it - lets find out
//   int offset_for_status_text() const;
//   int offset_for_grid() const;
//   int offset_for_raw_colors() const;


};

void display_text(const State &state, ostream &os);



#endif