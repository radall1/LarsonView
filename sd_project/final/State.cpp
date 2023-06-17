#include<sstream>
using namespace std;
#include"State.h"
#include"/usr/local/cs/cs251/react.h"

int* wash_or_dry(istream &is){
  int *arr= new int[5];
  string line;
  //  ofstream out_file{"intermediate.txt"};
int i=0;
  while (getline(is, line) && i<5) {
          //  out_file << line << "\n";
           if (line[0]=='W'){arr[i++]=1;}
          if (line[0]=='D'){arr[i++]=0;}
          // arr[i++]=line[0];
        }
// out_file.close();
 is.clear();
is.seekg(0);

return arr;
}

State::State(istream &is) { //ifstream
  int *arr;
  arr = wash_or_dry(is);
  
  for (int i=0; i<5; i++){  
    if (arr[i]){building[i]=new Washer(is);}
    if (!arr[i]){building[i]=new Dryer(is);}
    //building[i] = new Washer(is);
    }
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
      os << get_building()[i]->return_type()<<" " << get_building()[i]->return_type() << " " << get_building()[i]->return_id() << " " << get_building()[i]->return_id()+1 << endl;
    }

    for (int i=0; i<5; i++){
      if (get_building()[i]->return_availability()){
        os << "Laundry " << get_building()[i]->return_id() << " Occupied ";
        if (get_building()[i]->return_time(os)<10){
          os<<""<<get_building()[i]->return_time(os);}
        else{
          os<<get_building()[i]->return_time(os);
          }
        os << " mins " << hour << " " << minute <<endl;
      }
      
  
    }
   // os <<"Laundry 00 Occupied 100 mins 14 00\nLaundry 01 Occupied 40 mins 15 00\nLaundry 04 Occupied 60 mins 15 00";
}


void State::update() {
   _put_tilde_terminated_string("Legend~Out of Order~Vacant~Occupied~  Update~  Schedule~", _global_mem + 400);
  

   if (_received_event() && _event_id_is("button_", 1)) {
   for (int h=0; h<5; h++){
    // get_building()[h]->get_time();
    get_building()[h]->return_time();
   }
   keyword = "Laundry";}

   if (_received_event() && _event_id_is("return")) {
  
   keyword = "Laundry";}



  

for (int j =0; j<8; j++){

   if (_received_event() && _event_id_is("machine_", j)) {
    if (j>4) {keyword="Laundry";
    break;
    }
    if (!get_building()[j]->return_availability()) {
      keyword="Laundry";
    } else{
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;

    string current_h = to_string(hour);
    string current_m = to_string(minute);


    if (minute < 10){
      current_m = "0" + current_m;
    }
    if (hour < 10){
      current_h = "0" + current_m;
    }
    string current = current_h + ":" + current_m;
     _put_tilde_terminated_string(current, _global_mem + 530);


    current_h = to_string(hour+1);
    if (hour+1 < 10){
      current_h = "0" + current_m;
    }
    current = current_h + ":" + current_m;
    _put_tilde_terminated_string(current, _global_mem + 580);

    string constant = "Machine Number ";
    string variable = to_string(j);
    _put_tilde_terminated_string(constant+variable, _global_mem + 500);
    
    string future = get_building()[j]->next_available_time();
    _put_tilde_terminated_string(future, _global_mem + 560);

    _put_tilde_terminated_string("Occupied", _global_mem + 600);
    _put_tilde_terminated_string("Click to Schedule", _global_mem + 620);
    _put_tilde_terminated_string("Click to Schedule", _global_mem + 640);
    _put_tilde_terminated_string("lightgreen", _global_mem + 700);
    _put_tilde_terminated_string("lightgreen", _global_mem + 720);
  
    _put_tilde_terminated_string(" Back", _global_mem + 800);
    string type = get_building()[stoi(variable)]->return_type();
    _put_tilde_terminated_string(type, _global_mem + 1000);
    _put_tilde_terminated_string(variable, _global_mem + 1269);
   keyword = "Scheduling";}

}}

     if (_received_event() && _event_id_is("button_", 2)) {
   keyword = "Schedule";}
 if (_received_event() && _event_id_is("unavailable")) {
  keyword="Scheduling";
 }
      if (_received_event() && _event_id_is("available_", 1)) {
    // time_t ttime = time(0);
    // tm *local_time = localtime(&ttime);
    // int hour = local_time->tm_hour;
    // int minute = local_time->tm_min;

    // string current_h = to_string(hour);
    // string current_m = to_string(minute);


    // if (minute < 10){
    //   current_m = "0" + current_m;
    // }
    // if (hour < 10){
    //   current_h = "0" + current_m;
    // }
    // string current = current_h + ":" + current_m;
    //  _put_tilde_terminated_string(current, _global_mem + 530);


    // current_h = to_string(hour+1);
    // if (hour+1 < 10){
    //   current_h = "0" + current_m;
    // }
    // current = current_h + ":" + current_m;
    // _put_tilde_terminated_string(current, _global_mem + 580);

    // string constant = "Machine Number ";
    //string variable = to_string(j);
    //_put_tilde_terminated_string(constant+variable, _global_mem + 500);
    
   //string future = get_building()[j]->next_available_time();
    //_put_tilde_terminated_string(future, _global_mem + 560);

    //_put_tilde_terminated_string("Occupied", _global_mem + 600);
    _put_tilde_terminated_string("Scheduled", _global_mem + 620);

    //_put_tilde_terminated_string("Click to Schedule", _global_mem + 640);
    _put_tilde_terminated_string("red", _global_mem + 700);
   keyword = "Scheduled";
   

   string id(_global_mem+1269, _global_mem+1270);
   get_building()[stoi(id)]->scheduled();
   }

     if (_received_event() && _event_id_is("available_", 2)) {
    // time_t ttime = time(0);
    // tm *local_time = localtime(&ttime);
    // int hour = local_time->tm_hour;
    // int minute = local_time->tm_min;

    // string current_h = to_string(hour);
    // string current_m = to_string(minute);


    // if (minute < 10){
    //   current_m = "0" + current_m;
    // }
    // if (hour < 10){
    //   current_h = "0" + current_m;
    // }
    // string current = current_h + ":" + current_m;
    //  _put_tilde_terminated_string(current, _global_mem + 530);


    // current_h = to_string(hour+1);
    // if (hour+1 < 10){
    //   current_h = "0" + current_m;
    // }
    // current = current_h + ":" + current_m;
    // _put_tilde_terminated_string(current, _global_mem + 580);

    // string constant = "Machine Number ";
    //string variable = to_string(j);
    //_put_tilde_terminated_string(constant+variable, _global_mem + 500);
    
   //string future = get_building()[j]->next_available_time();
    //_put_tilde_terminated_string(future, _global_mem + 560);

    //_put_tilde_terminated_string("Occupied", _global_mem + 600);
    _put_tilde_terminated_string("Scheduled", _global_mem + 640);
    //_put_tilde_terminated_string("Click to Schedule", _global_mem + 640);
 _put_tilde_terminated_string("red", _global_mem + 720);
   keyword = "Scheduled";}
  
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