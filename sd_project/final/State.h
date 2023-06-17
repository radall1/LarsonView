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
    string keyword;
    

  public: 

    static const int offset;

    string get_screen_text() const {
        return screen_text;
    }

    string get_keyword() const {
        return keyword;
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
void firsttime(){
    keyword="Laundry";
     for (int h=0; h<5; h++){
    // get_building()[h]->get_time();
    get_building()[h]->return_time();
   }
   // for (int h=0; h<5; h++){
  ///   get_building()[h]->get_time();
   }

void update();
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