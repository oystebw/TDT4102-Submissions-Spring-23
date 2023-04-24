#include "Tile.h"
#include "utilities.h"
#include <iostream>

using namespace TDT4102;

Tile::Tile(TDT4102::Point pos, int size,  int max_value, AnimationWindow& win) : pos{pos}, size{size}, max_value{max_value}, win{win}
{
	set_value(0);
}


void Tile::set_value(int value)
{
	Point pos_text{pos.x - 8 +  size/2, pos.y - 13 + size/2};

	if (value == 0) {
		// An empty tile
		win.draw_rectangle(pos, size, size, TDT4102::Color::gray, TDT4102::Color::black);
	} else {
		int current_step = std::log2(value) - 1;
		int max_step = std::log2(max_value) - 1;
		TDT4102::Color darker = lerp_rgb(Color::yellow, Color::dark_orange, current_step, max_step);
		win.draw_rectangle(pos, size, size, darker, TDT4102::Color::black);
		win.draw_text(pos_text, std::to_string(value));
	}

}

