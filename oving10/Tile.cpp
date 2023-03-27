#include "Tile.h"

// For å sette labelfarge i henhold til hvor mange miner som er rundt
const map<int, Color> minesToColor{{1, Color::blue},
								   {2, Color::red},
								   {3, Color::dark_green},
								   {4, Color::dark_magenta},
								   {5, Color::dark_blue},
								   {6, Color::dark_cyan},
								   {7, Color::dark_red},
								   {8, Color::dark_yellow}};

// For å sette Tile-label i henhold til state
const map<Cell, string> cellToSymbol{{Cell::closed, ""},
									 {Cell::open, ""},
									 {Cell::flagged, "@<"}};

void Tile::open() {
	if (state == Cell::closed) {
		this->set();
		state = Cell::open;
		if (isMine) {
			set_label("X");
			set_label_color(Color::red);
		}
	}
}

void Tile::flag() {
	if (state == Cell::flagged) {
		state = Cell::closed;
		std::string s = cellToSymbol.at(state);
		set_label(s);
	}
	else {
		state = Cell::flagged;
		std::string s = cellToSymbol.at(state);
		set_label(s);
		set_label_color(Color::blue);
	}
}

void Tile::setAdjMines(int mines) {
	set_label(std::to_string(mines));
	Color c = minesToColor.at(mines);
	set_label_color(c);
}
