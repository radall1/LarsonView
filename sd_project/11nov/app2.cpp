#include<iostream>
#include<fstream>
using namespace std;
#include"State.h"

void _main_loop() {
  bool just_starting = true;
  while(1) {
    string input;
    if (!just_starting) {
      if ("end" == input) break;
    }

    ifstream fs;
    if (just_starting) fs.open("initial_state");
    else fs.open("curr_state");
    State state(fs);
    
    if (just_starting) {state.update("new");
    display_text(state, cout);}
    fs.close();
    cin >>input;
    
    state.update(input);
    display_text(state, cout);

    ofstream fs2("curr_state");
    state.write_to(fs2);

    just_starting = false;
  }
}

int main() {
  _main_loop();
}

