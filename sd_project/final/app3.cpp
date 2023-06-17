#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#include"/usr/local/cs/cs251/react.h"
#include"State.h"

int _find_null(char mem[]){
  int output=0;
  string bait(mem);
  while (bait[output]!= '~'){output++;}
  return output;
}

// class State {
//   int num;

// public:
//   static const int offset;

//   State(istream &is) { is >> num; }
//   int get_num() const { return num; }
//   void write_to(ostream &os) const { os << num << endl; }
//   int size_in_bytes() const { ostringstream oss; write_to(oss); return oss.str().size(); }
//   void update() { if (_received_event() && 'a' == _global_mem[100]) ++num; }
// };

const int State::offset = 0;

void display(const State &state) {
  // string s = to_string(state.get_num());
  string color_1(_global_mem + 700, _find_null(_global_mem + 700));
  string color_2(_global_mem + 720, _find_null(_global_mem + 720));
  int i = 1 + state.size_in_bytes();
  //_put_tilde_terminated_string("TESSSSST", _global_mem + 300);

    // print out _global_mem from [4] to [30]


  if (state.get_keyword() == "Laundry")
  {_add_yaml("count.yaml", {{"machine0", (!state.get_building()[0]->return_availability()) ? "lightblue" : "red"}, {"machine1", (!state.get_building()[1]->return_availability()) ? "lightblue" : "red"}, {"machine2", (!state.get_building()[2]->return_availability()) ? "lightblue" : "red"}, {"machine3", (!state.get_building()[3]->return_availability()) ? "lightblue" : "red"}, {"machine4", (!state.get_building()[4]->return_availability()) ? "lightblue" : "red"}});
  }

   if (state.get_keyword() == "Scheduling")
  {_add_yaml("scheduling.yaml", {{"available_1_color", "lightgreen"}, {"available_2_color", "lightgreen"}});
  }

  if (state.get_keyword() == "Scheduled")
  {_add_yaml("scheduling.yaml", {{"available_1_color", color_1}, {"available_2_color", color_2}});
  }

  if (state.get_keyword() == "Scheduled2")
  {_add_yaml("scheduling.yaml", {{"available_2_color", "red"}, {"available_1_color", "lightgreen"}});
  }

   if (state.get_keyword() == "Schedule")
  {
    _add_yaml("schedule.yaml", {{"machine0", (!state.get_building()[0]->return_availability()) ? "lightblue" : "red"}, {"machine1", (!state.get_building()[1]->return_availability()) ? "lightblue" : "red"}, {"machine2", (!state.get_building()[2]->return_availability()) ? "lightblue" : "red"}, {"machine3", (!state.get_building()[3]->return_availability()) ? "lightblue" : "red"}, {"machine4", (!state.get_building()[4]->return_availability()) ? "lightblue" : "red"}});
  }
  //string d(_global_mem + 0, 100 - 0);
  //cout << "ddd"<< d <<endl;
  //cout<<"diff " << s << endl;
}

void _receive_and_send() {
  // initialization
  _read_event_info_file("event_info");
  if (_just_starting()) {
    _read_global_mem_from_file("startup_mem");
  }
  else {_read_global_mem_from_file("end_mem");}

  istringstream iss(_global_mem + State::offset);
  State state(iss);

    if (_just_starting()) {
    state.firsttime();
  }

  //state.get_building()[3]->get_time();
  //cout<<"Test 1: "<<state.get_building()[3]->return_availability();
  //cout<<endl<<state.get_building()[3]->return_time(cout);

  


  // event handling and display
  state.update();
  display(state);
  

  // write out the end state 
  ostringstream oss;
    state.write_to(oss);
  string s = oss.str();

 // _put_tilde_terminated_string("TESSSSST", _global_mem + 1000);
 // cout<<"Result is " << find_null(_global_mem+1000) <<endl;

 
 
  s.copy(_global_mem , s.length());
  _put_tilde_terminated_string("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", _global_mem + s.length());
    //cout<< s;
//  string d(_global_mem, 101);
//   cout << "ddd"<< d <<endl;

  _write_global_mem_to_file("end_mem");
 _write_global_yaml_to_file("react.yaml");
;
}

int main() {
  _receive_and_send();
}