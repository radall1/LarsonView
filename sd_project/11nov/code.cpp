#include"code.h"

 
void Machine::show_time(ostream &os){
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;

  //  if (((time_left_h-hour)*60 + (time_left_m-minute))>0 ) {os << "HHIIII";}

    if (((time_left_h-hour)*60 + (time_left_m-minute))>0 && status){
        time_left = (time_left_h-hour)*60 + (time_left_m-minute);
        os<<"It's occupied. It will be available in ";
    os<< (time_left_h-hour)*60 + (time_left_m-minute);
       os<<" minute(s)."<<endl;
    }
    else{
        time_left_h = time_left_m = time_left = 0;
   os<<"It's available. Hurry up!"<<endl;
    status=0;}
}

void Machine::get_time(){
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;

  //  if (((time_left_h-hour)*60 + (time_left_m-minute))>0 ) {os << "HHIIII";}
    if (((time_left_h-hour)*60 + (time_left_m-minute))>0 && status){
        time_left = (time_left_h-hour)*60 + (time_left_m-minute);
    status=1;
    }
    else{
        time_left_h = time_left_m = time_left = 0;
    status=0;}
}

int Machine::return_time(ostream &os){
    time_t ttime = time(0);
    tm *local_time = localtime(&ttime);
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;

    if (((time_left_h-hour)*60 + (time_left_m-minute))>0 && status){
      //  time_left = (time_left_h-hour)*60 + (time_left_m-minute);
      //  os<<"It's occupied. It will be available in ";
    return (time_left_h-hour)*60 + (time_left_m-minute);
      // os<<" minute(s)."<<endl;
    }
   // else{
   //     time_left_h = time_left_m = time_left = 0;
  // os<<"It's available. Hurry up!"<<endl;
    //status=0;}
}

Machine &Machine::operator=(const Machine &g){
    return *this;
}



void Machine::display_type(){
       cout<<type<<endl;}

int Machine::return_time(){
    return time_left;}

void Machine::change_time_left_h(int t){
    time_left_h=t;
}
void Machine::change_time_left_m(int t){
    time_left_m=t;
}

string Machine::return_type(){
       return type;}

int Machine::return_id(){
    return machine_id;
}
void Machine::change_availability(){
    if (status==1){status=0;}
    else if (status==0){status=1;}
}
void Machine::display_availability(){
       cout<<status<<endl;}

bool Machine::return_availability(){
       return status;}
 
void Machine::change_time_left(double t){
       time_left=t;}
 
void Machine::write_history_global(){
       time_t my_time = time(NULL);
       // ctime() used to give the present time
       ofstream fs(machine_id_text);
       fs << "Machine ID: " << machine_id << " Time/Date: " << ctime(&my_time);}
 
int Machine::washer(){
       string choice;
       int output=20;
       string additional;
       cout << "Enter your washer settings: Delicates or Eco-Friendly or Normal or Perm Press" << endl;
       cin >> choice;
      
      
       cout << "Do you have any additional settings (rinse/easy-iron)? Yes or No" << endl;
       cin >> additional;
 
       if (additional=="Yes"){output+=5;}
 
 
       if(choice == "Delicates"){
           output+=3;
       }
 
       if(choice == "Eco-Friendly"){
           output +=5;
       }
 
       if(choice == "Normal"){
           output+=6;
       }
 
       if(choice == "Perm Press"){
           output +=3;
       }
 
       cout<< "Time taken (By Washer): " << output << endl;
       return output;
 
   }
 
int Machine::dryer(){
       string settings;
       cout << "Enter your dryer settings : High Heat or Medium Heat or Low Heat" << endl;
       cin >> settings;
       int output=40;
 
 
       if(settings == "High Heat"){
           output+=5;
       }
 
       if(settings == "Medium Heat"){
           output +=6;
       }
 
       if(settings == "Low Heat"){
           output+=4;
       }
 
       cout<< "Time taken (by Dryer): " << output << endl;
 
       return output;
 
   }
 
void Machine::run(){

      string response;
           cout<< "Dryer or Washer or Both?" <<endl;
           cin>>response;
           if (response=="Dryer"){dryer();}
           if (response=="Washer"){washer();}
           if (response=="Both"){
            int w = washer();
              int d = dryer();
          
               cout << "Total Time Taken: "<< w +d << " minutes" << endl;
           }
    
   }

int count_lines(const char* text){
    ifstream is(text);
    string placeholder;
    int num_lines=0;
    while(getline(is, placeholder)){
        num_lines++;
    }
    return num_lines;
}
 
// void parse_arduino(istream &is, Machine* building[], const char* text){
   

//     string keyword;
//     is >> keyword;
//     if (keyword != "Laundry") {
//         cerr << "Error in Arduino Text!" << endl;
//         exit(1);
//     }
//     int id;
//     is>>id;
//     string waste;
//     is>>waste;
//     int left;
//     is >>left;
//     int hour;
//     int minute;

//     for (int i=0; i<count_lines(text); i++){
//        // if (id == building[i]->return_id()){         
//             building[id]->change_availability(); //expand on it
//             building[id]->change_time_left(left);
//             //new stuff
//             is >> waste;
//             int timeleft = building[id]->return_time();
//             is >> hour;
//             is >> minute;
//             minute += timeleft;
//             timify clean(hour, minute);
//             building[id]->change_time_left_h(clean.return_hour());
//             building[id]->change_time_left_m(clean.return_minute());

//             is>> waste;
//             is >> id;
//             is>>waste;
//             is>>left;
//         }
    
//     }

 
void parse_arduino(istream &is, Machine* building[]){
   

    string keyword;
    is >> keyword;
    if (keyword != "Laundry") {
        cerr << "Error in Arduino Text!" << endl;
        exit(1);
    }
    int id;
    is>>id;
    string waste;
    is>>waste;
    int left;
    is >>left;
    int hour;
    int minute;

    for (int i=0; i<5; i++){
        if (id == building[i]->return_id()){          
            building[id]->change_availability(); //expand on it
            building[id]->change_time_left(left);
            //new stuff
            is >> waste;
            int timeleft = building[id]->return_time();
            is >> hour;
            is >> minute;
            minute += timeleft;
            timify clean(hour, minute);
            building[id]->change_time_left_h(clean.return_hour());
            building[id]->change_time_left_m(clean.return_minute());

            is>> waste;
            is >> id;
            is>>waste;
            is>>left;
        } 
    
    }
}
    
int Machine::return_time_left_h(){
    return time_left_h;
}
int Machine::return_time_left_m(){
    return time_left_m;
}


 




