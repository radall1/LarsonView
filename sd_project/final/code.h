#ifndef __CODE_H__
#define __CODE_H__

#include<sstream>
#include<string>
#include<ctime>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<fstream>
using namespace std;
 
 
class Machine {
    protected:
   int machine_id;
   string machine_id_text;
   bool status;
   double time_left;
   int time_left_h;
   int time_left_m;
   string type;
   int* ptr;
 
   public:
   Machine(int m, string t){
       machine_id=m;
       machine_id_text="10022";
       status=0;
       time_left=0;
       type = t;
       }
   
   
   Machine(istream &is) {
    string keyword;
    is >> keyword;
   
    //cout<<stoi(keyword);
    if (keyword != "Washer" && keyword!="Dryer") {
        cerr << "Error in Machine constructor!" << endl;
       // exit(1);
    }
    is>>type;
    is >> machine_id;
    is >> machine_id_text;
    status = 0;
    time_left = 0;
    }

   void change_status(int t);
   void display_type();
   bool return_availability();
   void display_availability();
   Machine &operator=(const Machine &g);
   int return_time(ostream &os);
   string next_available_time();
   void change_availability();
   void change_time_left(double t);
   void write_history_global();
   void get_time();
   int washer();
   int dryer();
   void run();
   int return_id();
   void show_time(ostream &os);
   int return_time();
   void change_time_left_h(int t);
   void change_time_left_m(int t);
   int return_time_left_h();
   int return_time_left_m();
   string return_type();
   virtual void scheduled() = 0;

};

class timify {
    int hour;
    int minute;

    public:
    timify(int h, int m){
        if (m>60){
            int leftover = m-60;
            hour = h + 1;
            minute= leftover;
        }
        else {
            hour = h;
            minute =m;
    }
    }
    
    int return_hour(){
        return hour;
    }
    
    int return_minute(){
        return minute;
    }
    
    
};

class Washer : public Machine{

    public:
    Washer(istream &is) : Machine(is) { type="Washer";}

    virtual void scheduled();

};

class Dryer : public Machine{

    public:
    Dryer(istream &is) : Machine(is) {type="Dryer";}
    virtual void scheduled();
};

 
 void parse_arduino(istream &is, Machine* building[]);
 int count_lines(const char* text);

#endif




