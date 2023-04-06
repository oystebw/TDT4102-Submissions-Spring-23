#pragma once
#include "AnimationWindow.h"
#include "Tile.h"

enum class MouseButton { left = FL_LEFT_MOUSE, right = FL_RIGHT_MOUSE }; 

// Minesweeper GUI
class MinesweeperWindow : public AnimationWindow {
public:
	// storrelsen til hver tile
	static constexpr int cellSize = 30;
	MinesweeperWindow(int x, int y, int width, int height, int mines, const string& title);
private:
	const int width;		// Bredde i antall tiles
	const int height;		// Høyde i antall tiles		
	const int mines;		// Antall miner
	vector<shared_ptr<Tile>> tiles; // Vektor som inneholder alle tiles
	int openedTiles = 0;
	const int mineFreeTiles;
	const int pad = 50;
	int placed{0};
	Fl_Output won;
	Fl_Output lost;
	Fl_Button quitBtn;
	Fl_Button restartBtn;
	
	static void cb_quit(Fl_Widget*, void* pw);
	static void cb_restart(Fl_Widget*, void* pw);
	void resetBoard();

	// hoyde og bredde i piksler
	int Height() const { return height * cellSize; } 
	int Width() const { return width * cellSize; }

	// Returnerer en vektor med nabotilene rundt en tile, der hver tile representeres som et punkt
	vector<Point> adjacentPoints(Point xy) const;
	// tell miner basert på en liste tiles
	int countMines(vector<Point> coords) const;

	// Sjekker at et punkt er på brettet
	bool inRange(Point xy) const { return xy.x >= 0 && xy.x< Width() && xy.y >= 0 && xy.y < Height(); }
	// Returnerer en tile gitt et punkt
	shared_ptr<Tile>& at(Point xy) { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }
	const shared_ptr<Tile>& at(Point xy) const { return tiles[xy.x / cellSize + (xy.y / cellSize) * width]; }

    // Åpne og flagge rute
	void openTile(Point xy);
	void flagTile(Point xy);

	// Callback funksjoner for de tile knappene
	static void cb_click(Fl_Widget*, void* pw) { static_cast<MinesweeperWindow*>(pw)->click(); };
	void click();

	// Logikk for tapt og vunnet spill
	void isWon();
	void isLost();
};
