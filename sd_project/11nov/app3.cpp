#include<iostream>
#include<fstream>
#include<sstream>
using namespace std;
#include"/usr/local/cs/cs251/react.h"
#include"State.h"

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
  int i = 1 + state.size_in_bytes();
  // _put_tilde_terminated_string(s, _global_mem + i);

    // print out _global_mem from [4] to [30]

   for (int h=0; h<5; h++){
     state.get_building()[h]->get_time();
     cout<<state.get_building()[h]->return_availability();
   }

  _add_yaml("count.yaml", {{"machine0", (!state.get_building()[0]->return_availability()) ? "lightblue" : "red"}, {"machine1", (!state.get_building()[1]->return_availability()) ? "lightblue" : "red"}, {"machine2", (!state.get_building()[2]->return_availability()) ? "lightblue" : "red"}, {"machine3", (!state.get_building()[3]->return_availability()) ? "lightblue" : "red"}, {"machine4", (!state.get_building()[4]->return_availability()) ? "lightblue" : "red"}});
  //string d(_global_mem + 0, 100 - 0);
  //cout << "ddd"<< d <<endl;
  //cout<<"diff " << s << endl;
}

void _receive_and_send() {
  // initialization
  _read_event_info_file("event_info");
  if (_just_starting()) _read_global_mem_from_file("startup_mem");
  else _read_global_mem_from_file("end_mem");

  istringstream iss(_global_mem + State::offset);
  State state(iss);

  

  // event handling and display
  state.update();
  display(state);

  // write out the end state 
  ostringstream oss;
  // state.write_to(oss);
  string s = oss.str();
  s.copy(_global_mem + state.offset, s.length());

  _write_global_mem_to_file("end_mem");
  _write_global_yaml_to_file("react.yaml");
  delete [] _global_mem;
}

int main() {
  _receive_and_send();
}