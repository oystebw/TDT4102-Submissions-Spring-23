#include <iostream>

#include "Game_window.h"

int main()
{	
    using namespace TDT4102;

	constexpr int board_size = 4;
	constexpr int tile_size = 100;
	constexpr int win_value = 1024;
	const std::string window_title = "1024";

	Game_window game_window{board_size, win_value, tile_size, window_title};
	game_window.wait_for_close();

	return 0;
	
}
