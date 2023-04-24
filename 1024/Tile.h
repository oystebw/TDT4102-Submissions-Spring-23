#pragma once
#include "AnimationWindow.h"
#include <string>
#include "widgets/Button.h" 


struct Tile {
	Tile(TDT4102::Point pos,  int size,  int max_value, TDT4102::AnimationWindow& win);
	void set_value(int value);

  private:
	TDT4102::AnimationWindow& win;
	TDT4102::Point pos;
	int size;
	int max_value;
};