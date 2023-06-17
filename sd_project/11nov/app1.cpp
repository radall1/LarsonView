#include<iostream>
#include<fstream>
using namespace std;
#include"State.h"

void _main_loop_draft() {
  ifstream fs("initial_state");
  State state(fs);
  state.update("new");
  display_text(state, cout);
  
  string input;
  while(1) {
  cin >>input;
  if ("end" == input) break;

  state.update(input);
  display_text(state, cout);
  }
}

int main() {
  _main_loop_draft();
}
