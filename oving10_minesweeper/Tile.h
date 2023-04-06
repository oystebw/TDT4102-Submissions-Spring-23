#pragma once
#include "GUI.h"


// De forskjellige tilstandene en Tile kan være i
enum class Cell {closed, open, flagged}; 

class Tile : public Fl_Button {
	private:
		Cell state = Cell::closed;
		bool isMine = false;
	public:
		Tile(Point pos, int size) 
			:Fl_Button(pos.x, pos.y, size, size, "") {};

		void open();
		void flag();

		Cell getState() const {return state;};
		bool getIsMine() {return isMine;}
		
		void setIsMine(bool state) {isMine = state;}
		void setAdjMines(int mines);
		void set_label(string s) {this->copy_label(s.c_str());}
		void set_label_color(Color c) {this->labelcolor(c.as_int());}
};
