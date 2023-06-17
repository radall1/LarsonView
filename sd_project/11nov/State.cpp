#include<sstream>
using namespace std;
#include"State.h"
#include"/usr/local/cs/cs251/show_mem.h"

State::State(istream &is) { //ifstream
  for (int i=0; i<5; i++){  
    building[i] = new Machine(is);}
  parse_arduino(is, building);
}



void display_text(const State &state, ostream &os) {
  os << endl;
  os << "\t\t";
  //os << state.get_screen_text();
  
  if (state.get_again()==0){
    for (int h=0; h<5; h++){
    os << "* " << state.get_building()[h]->return_type() << " " << state.get_building()[h]->return_id() << endl;}
  os << "  Enter a number (0, 1, 2, 3, or 4): " ; 
  }
  else {
  
  for (int h=0; h<5; h++){
    os << "* " << state.get_building()[h]->return_type() << " " << state.get_building()[h]->return_id() << endl;}
  os << "  Enter a number (0, 1, 2, 3 or 4): " <<endl; 

   os << "The status of laundry machine with ID number " << state.get_number() << " is: ";
   state.get_building()[state.get_number()]->show_time(os);
   os << endl; 

   for (int h=0; h<5; h++){
    os << "* " << state.get_building()[h]->return_type() << " " << state.get_building()[h]->return_id() << endl;}
  os << "  Enter a number (0, 1, 2, 3, or 4): "; 
  }
           
}

void State::write_to(ostream &os) const {

  time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;

    for (int i=0; i<5; i++){
      os << "Laundry " << get_building()[i]->return_type() << " " << get_building()[i]->return_id() << " " << get_building()[i]->return_id()+1 << endl;
    }

    for (int i=0; i<5; i++){
      if (get_building()[i]->return_availability()){
        os << "Laundry " << get_building()[i]->return_id() << " Occupied ";
        os<<get_building()[i]->return_time(os);
        os << " mins " << hour << " " << minute <<endl;
      }
      
    }
   // os <<"Laundry 00 Occupied 100 mins 14 00\nLaundry 01 Occupied 40 mins 15 00\nLaundry 04 Occupied 60 mins 15 00";
}


void State::update(string input) {
  if (input=="new"){
    again=0;
  }
  else if (stoi(input)>=0 && stoi(input)<=5) {
    number=stoi(input);
    again=1;}
  
}

// int State::offset_for_num_moves() const {
//   return offset + 2;
// }

// int State::offset_for_status_text() const{
//   return (offset_for_num_moves() + to_string(num_moves).size()) + 1;
// }

// int State::offset_for_grid() const{
//     return (offset_for_status_text())+status_text.size();
// }

// int State::offset_for_raw_colors() const {
//   return offset_for_grid() + grid.size_in_bytes();
// }