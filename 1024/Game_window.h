#pragma once
#include <memory>
#include <string>
#include <vector>
#include "widgets/TextInput.h"
#include "time.h"

#include "AnimationWindow.h"
#include "Game.h"
#include "Tile.h"

enum class Arrow_key {
	up,
	right,
	down,
	left
};

using namespace TDT4102;
using namespace std;

class Game_window : public TDT4102::AnimationWindow
{
  public:
	Game_window(int board_size,
	            int win_value,
	            int tile_size,
	            const std::string& title);

  private:
	
	bool upPressed;
	bool rightPressed;
	bool downPressed;
	bool leftPressed;

	bool upLast;
	bool rightLast;
	bool downLast;
	bool leftLast;
	
	// Modify the board
	void reset();
	void update();
	void update_tiles();
	void update_tile(int x, int y, int value);

	// Capture key presses and pass to action functions
	//int handle(int event) override;
	int handle_input();
	void handle_arrow_key(Arrow_key key);

	// For debugging under the exam
	void insert_two_tiles();
	void insert_increasing_tiles();
	void insert_push_merge_tiles();
	void debug_transpose_tiles();
	void debug_flip_tiles();
	void debug_update();

	// Misc
	void check_status();

	Game game;
	int board_size;
	int tile_size;
	std::vector<std::vector<std::unique_ptr<Tile>>> tiles;
};