#include "Game.h"
#include <list>
#include <random>

Game::Game(int board_size, int win_value)
	: board_size(board_size),
	  board(board_size * board_size),
	  win_value{win_value}
{
	srand(time(NULL));
	new_game();
}

// TASK
int Game::index(int x, int y) const
{
	// BEGIN: G1
	return (y * board_size + x);
	// END: G1
}

// TASK
int Game::at(int x, int y) const
{
	// BEGIN: G2
	return board[index(x, y)];
	// END: G2
};

// TASK
int& Game::at(int x, int y)
{
	// BEGIN: G3
	return board[index(x, y)];
	// END: G3
}

// TASK
void Game::new_game()
{
	// BEGIN: G4
	for(int& tile: board){
		tile = 0;
	}
	place_new_2();
	place_new_2();
	// END: G4
}

// TASK
// Prerequisites: board does have a free 0-spot
void Game::place_new_2()
{
	// BEGIN: G5
	int x;
	int y;
	bool success = false;

	while(!success){
		x = rand() % 4;
		y = rand() % 4;

		if(!at(x, y)){
			at(x, y) = 2;
			success = true;
		}
	}
	// END: G5
}

// TASK
void Game::flip()
{
	// BEGIN: G6
	int temp;
	for(int x{0}; x < board_size / 2; ++x){
		for(int y{0}; y < board_size; ++y){
			temp = at(x, y);
			at(x, y) = at(board_size - 1 - x, y);
			at(board_size - 1 - x, y) = temp;
		}
	}
	// END: G6
}

// TASK
void Game::transpose()
{
	// BEGIN: G7
	int temp;
	for(int y{0}; y < board_size; ++y){
		for(int x{0}; x <= y; ++x){
			temp = at(x, y);
			at(x, y) = at(y, x);
			at(y, x) = temp;
		}
	}
	// END: G7
}

// TASK
void Game::push_right()
{
	// BEGIN: G8
	bool done = false;

	while(!done){
		done = true;
		for(int y{0}; y < board_size; ++y){
			for(int x{1}; x < board_size; ++x){
				if(!at(x, y) && at(x - 1, y)){
					at(x, y) = at(x - 1, y);
					at(x - 1, y) = 0;
					done = false;
				}
			}
		}
	}
	// END: G8
}

// TASK
void Game::merge_right()
{
	// BEGIN: G9
	for(int y{0}; y < board_size; ++y){
		for(int x{board_size - 1}; x > 0; --x){
			if(at(x, y) == at(x - 1, y)){
				at(x, y) *= 2;
				at(x - 1, y) = 0;
				push_right();
			}
		}
	}
	// END: G9
}

// TASK
void Game::move_right()
{
	// BEGIN: G10
	push_right();
	merge_right();
	// END: G10
}

// TASK
void Game::move_down()
{
	// BEGIN: G11
	transpose();
	move_right();
	transpose();
	// END: G11
}

// TASK
void Game::move_left()
{
	// BEGIN: G12
	flip();
	move_right();
	flip();
 	// END: G12
}


// TASK
void Game::move_up()
{
	// BEGIN: G13
	transpose();
	move_left();
	transpose();
	// END: G13
}

// TASK
bool Game::free_spots() const
{
	// BEGIN: G14
	for(int tile: board){
		if(!tile){
			return true;
		}
	}
	return false;
	// END: G14
}

// TASK
void Game::tick()
{
	// BEGIN: G15
	if(!moved){
		return;
	}
	if(!free_spots()){
		return;
	}
	place_new_2();
	// END: G15
}

// TASK
bool Game::win() const
{
	// BEGIN: G16
	for(int tile: board){
		if(tile == 1024){
			return true;
		}
	}
	return false;
	// END: G16
}

// TASK
// Prerequisites: all tiles are non-zero
bool Game::legal_moves() const
{
	// BEGIN: G17
	for(int y{0}; y < board_size; ++y){
		for(int x{1}; x < board_size; ++x){
			if(at(x, y) == at(x - 1, y)){
				return true;
			}
		}
	}
	for(int y{1}; y < board_size; ++y){
		for(int x{0}; x < board_size; ++x){
			if(at(x, y) == at(x, y - 1)){
				return true;
			}
		}
	}
	return false;
 	// END: G17
}



/**** Provided code ****/

// API version of tile value - const external interface
int Game::value(int x, int y) const { return at(x, y); }

// This function keeps track of changes to the board
// and calls the move function requested by the player
void Game::move(Direction direction)
{
	// We have not moved any tiles yet
	moved = false;

	// Keep the old board matrix for comparison
	std::vector<int> old_board{board};

	if (status() == Status::playing) {
		switch (direction) {
		case Direction::up:
			move_up();
			break;
		case Direction::right:
			move_right();
			break;
		case Direction::down:
			move_down();
			break;
		case Direction::left:
			move_left();
			break;
		}
	}

	// Did we move anything?
	if (board != old_board) {
		moved = true;
	}

	tick();
}

// We use this to figure out if a game
// is won, game over or if the player still
// can play legal moves
Game::Status Game::status() const
{
	if (win()) {
		return Status::win;
	}

	if (free_spots() || legal_moves()) {
		return Status::playing;
	}

	return Status::game_over;
}

bool Game::game_over() const { return status() == Status::game_over; }

std::ostream& operator<<(std::ostream& os, const Game& g)
{
	for (int i = 0; i < g.board_size; ++i) {
		for (int j = 0; j < g.board_size; ++j) {
			std::cout << g.at(j, i) << " ";
		}
		std::cout << '\n';
	}

	return os;
}

// Debug methods - debug API
void Game::debug_all_twos()
{
	static const std::array<int, 16> debug_board_all_twos{
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

	std::copy(debug_board_all_twos.begin(),
	          debug_board_all_twos.end(),
	          board.begin());
	tick();
}

void Game::debug_increasing()
{
	static const std::array<int, 16> debug_board_increasing{
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

	std::copy(debug_board_increasing.begin(),
	          debug_board_increasing.end(),
	          board.begin());
	tick();
}

void Game::debug_push_merge()
{
	// clang-format off
	static const std::array<int, 16> debug_board_push_merge{
		2,0,2,0,
		0,2,2,4,
		0,2,2,2,
		8,8,8,8
	};
	// clang-format on

	std::copy(debug_board_push_merge.begin(),
	          debug_board_push_merge.end(),
	          board.begin());
	tick();
}

void Game::debug_flip() { flip(); }
void Game::debug_transpose() { transpose(); }
