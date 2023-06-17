#include"/usr/local/cs/cs251/react.h" 
#include"State.h"



// to be changed 
const int num_colors = 6;
const int colors[6][3] = { {140,81,10}, {216,179,101}, {246,232,195}, {199,234,229}, {90,180,172}, {1,102,94} };
const int magnification = 20;

void make_button(int i) //makes button
{
  // ...
  int r,g,b,r2,b2,g2;

  r = colors[i][0];
  g = colors[i][1];
  b = colors[i][2];

 r2 = r+50;
 g2 = g+50;
 b2 = b+50;

  
  
  _add_yaml("button.yaml", {{"id", i}, {"r", r}, {"g", g}, {"b", b}, {"r2", r2}, {"g2", g2}, {"b2", b2}});
  _write_global_yaml_to_file("react.yaml");

}

void render_grid_colors(const State &state) {
  const Grid &grid = state.get_grid();
  int index = state.offset_for_raw_colors();
  char *mem = _global_mem + index;
  GridLocation gl;
  for (gl.j = 0; gl.j < grid.get_height(); ++gl.j)
  for (gl.i = 0; gl.i < grid.get_width(); ++gl.i) {
    *mem++ = colors[ static_cast<int>(grid.get_color(gl)) ][0];
    *mem++ = colors[ static_cast<int>(grid.get_color(gl)) ][1];
    *mem++ = colors[ static_cast<int>(grid.get_color(gl)) ][2];
  }
}

//}

void display(const State &state) {
  _add_yaml("flood_fill.yaml", {{"top_index", state.offset_for_status_text()}, {"grid_width", 4},{"grid_height",4},{"magnification",10},{"total_width",40},{"total_height",40},{"grid_offset",state.offset_for_raw_colors()}}); // ...
  if (state.get_show_buttons()) {
    for (int i = 0; i < num_colors; ++i) make_button(i);
    //render_grid_colors(const State &state);

  } else {
    _add_yaml("new_game_button.yaml", {{"new_game_index", 1}});// ...
  }

  render_grid_colors(state);
}

// void render_grid_colors(const State &state) {
//   const Grid &grid = state.get_grid();
//   int index = state.offset_for_raw_colors();
//   char *mem = _global_mem + index;
//   GridLocation gl;
//   for (gl.j = 0; gl.j < grid.get_height(); ++gl.j)
//   for (gl.i = 0; gl.i < grid.get_width(); ++gl.i) {
//     *mem++ = colors[ static_cast<int>(grid.get_color(gl)) ][0];
//     *mem++ = colors[ static_cast<int>(grid.get_color(gl)) ][1];
//     *mem++ = colors[ static_cast<int>(grid.get_color(gl)) ][2];
//   }
// }
