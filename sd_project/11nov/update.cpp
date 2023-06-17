#include<iostream>
#include<fstream>
#include<sstream>
#include"State.h"
#include"/usr/local/cs/cs251/react.h" 

//to be changed


const int grid_size = 3;
const int max_moves = 25;

void State::handle_button_event(int i) {
  // fill the grid, starting in the upper left, with value i
  grid.fill(GridLocation{0,0},i);


  // set the status_text appropriately with the number of moves.
  status_text = to_string(num_moves) + "/" + to_string(max_moves) + " moves";

  //status_text[0] = char(get_num_moves());

  if(grid.is_one_color()){
    status_text = "Correct!";
    show_buttons = false;
  }


  //     also check if the grid has just one color, which means
  //     the status_text has a special prefix
  // decide whether show_buttons should be true or false:
  //     if the grid has just one color, or if we've run out of moves,
  //     then we don't show the buttons.


  // check:  if num_moves >= max_moves
  //            set show_buttons to false
  if (num_moves >= max_moves){
    show_buttons = false;
  }
}

void State::update() {

  bool is_new_game = _received_event() && _event_id_is("new_game");
  if (_just_starting() || is_new_game) {

  //if ("NEW_GAME" == input) {
    show_buttons = true;
    num_moves = 0;
    //status_text = new char[num_moves];
    status_text = "0/25 moves.";
    grid.randomize();

    // set show_buttons to true and num_moves to zero
    // initialize the status_text
    // initialize the grid randomly
  } else {

    if(!_received_event()){
      return;
    }

    else if(_received_event()){

      for(int i = 0; i < 6; i++) {// loop to look at button id 
      if (_event_id_is("button_", i)) {
        num_moves++;
        handle_button_event(i);
    }
      }
    }
  }
}