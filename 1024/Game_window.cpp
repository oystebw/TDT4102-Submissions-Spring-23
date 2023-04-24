#include "Game_window.h"
#include <iostream>

using namespace std;
using namespace TDT4102;

// The game window spawns at the center of the screen
Game_window::Game_window(int board_size,
                         int win_value,
                         int tile_size,
                         const std::string& title)
	: AnimationWindow(50, 50,
             board_size * tile_size,
             board_size * tile_size,
             title),
	  game{board_size},
	  board_size{board_size},
	  tile_size{tile_size}
{
	upLast = false;
	rightLast = false;
	downLast = false;
	leftLast = false;

	this->keep_previous_frame(true);

	// Default font for the graphics in this window
	for (int y = 0; y < board_size; ++y) {
		tiles.emplace_back();
		for (int x = 0; x < board_size; ++x) {
			Point pos{x * tile_size, tile_size * y};
			tiles.back().emplace_back(std::make_unique<Tile>(pos, tile_size, win_value, *this));
		}
	}

	update();
	
	while(!this->should_close()){
		update();
		handle_input();
		next_frame();
	}
}

void Game_window::reset()
{
	game.new_game();
	update();
}

void Game_window::update_tiles()
{
	try {
		for (int y = 0; y < board_size; ++y) {
			for (int x = 0; x < board_size; ++x) {
				update_tile(x, y, game.value(x, y));
			}
		}
	} catch (std::out_of_range& e) {
		std::string error =
			"[Debug] We tried to read outside the playing board:\n" +
			std::string{e.what()};
		show_error_dialog(error);
		//fl_alert("%s", error.c_str());
	}

}
void Game_window::update()
{
	update_tiles();
	check_status();
}

void Game_window::debug_update() { update_tiles(); }

void Game_window::check_status()
{
	if (game.win() ) {
		show_info_dialog(
			"Congratulations, you won the game!");
		close();
	} else if (game.game_over()) {
		show_info_dialog("Game over!");
		close();
	}
}

void Game_window::update_tile(int x, int y, int value)
{
	Point pos{x,y};
	auto&& rect = tiles[y][x];
	rect->set_value(value);
}

// Capture key presses and pass to action functions
void Game_window::handle_arrow_key(Arrow_key key)
{
	switch (key) {
	case Arrow_key::up:
		game.move(Direction::up);
		break;
	case Arrow_key::right:
		game.move(Direction::right);
		break;
	case Arrow_key::down:
		game.move(Direction::down);
		break;
	case Arrow_key::left:
		game.move(Direction::left);
		break;
	}

	update();
}


// Capture key presses and pass to action functions
int Game_window::handle_input(){

	upPressed = is_key_down(KeyboardKey::UP);
	rightPressed = is_key_down(KeyboardKey::RIGHT);
	downPressed = is_key_down(KeyboardKey::DOWN);
	leftPressed = is_key_down(KeyboardKey::LEFT);


	if(upPressed && !upLast){
		handle_arrow_key(Arrow_key::up);
		upLast = true;
		return 1;
	} 
	if (rightPressed && !rightLast){
		handle_arrow_key(Arrow_key::right);
		rightLast = true;
		return 1;
	} 
	if (downPressed && !downLast){
		handle_arrow_key(Arrow_key::down);
		downLast = true;
		return 1;
	} 
	if (leftPressed && !leftLast){
		handle_arrow_key(Arrow_key::left);
		leftLast = true;
		return 1;
	}

	upLast = is_key_down(KeyboardKey::UP);
	rightLast = is_key_down(KeyboardKey::RIGHT);
	downLast = is_key_down(KeyboardKey::DOWN);
	leftLast = is_key_down(KeyboardKey::LEFT);

	// For convenience
	// Reset window
	if (is_key_down(KeyboardKey::R)){
		reset();
		return 1;
	}

	// All tiles = 2
	if (is_key_down(KeyboardKey::D)){
		insert_two_tiles();
		return 1;
	}

	// Tiles in increasing values
	if (is_key_down(KeyboardKey::I)){
		insert_increasing_tiles();
		return 1;
	}

	// Tiles for testing push and merge
	if (is_key_down(KeyboardKey::P)){
		insert_push_merge_tiles();
		return 1;
	}

	if (is_key_down(KeyboardKey::T)){
		debug_transpose_tiles();
		return 1;
	}
		
	if (is_key_down(KeyboardKey::F)){
		debug_flip_tiles();
		return 1;
	}

	// Quit
	if (is_key_down(KeyboardKey::Q)){
		close();
		return 1;
	}

	return 0;
}

void Game_window::insert_two_tiles()
{
	game.debug_all_twos();
	debug_update();
};

void Game_window::insert_increasing_tiles()
{
	game.debug_increasing();
	debug_update();
};

void Game_window::insert_push_merge_tiles()
{
	game.debug_push_merge();
	debug_update();
}

void Game_window::debug_transpose_tiles()
{
	game.debug_transpose();
	debug_update();
};
void Game_window::debug_flip_tiles()
{
	game.debug_flip();
	debug_update();
};