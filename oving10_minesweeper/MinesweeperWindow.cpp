#include "MinesweeperWindow.h"

MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) :

	AnimationWindow{x, y, width * cellSize, (height + 1) * cellSize, title},
	width{width}, height{height}, mines{mines}, mineFreeTiles{(height * width) - mines},

	won{(cellSize * width) / 2, pad, 0, 0, 
	"You won!"}, 

	lost{(cellSize * width) / 2, pad, 0, 0, 
	"You lost!"}, 

	quitBtn(0, (cellSize * height) - pad, pad, pad, "Quit"),
	restartBtn((cellSize * width) - pad, (cellSize * height) - pad, pad, pad, "Restart")
{
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->callback(cb_click, this);
			add(tiles.back().get()); 
		}
	}

	// Legger til miner på tilfeldige posisjoner
	int randomTile;
	while (placed < mines) {
		randomTile = randint(0, (width * height) - 1);
		if (tiles.at(randomTile)->getIsMine()) {

		}
		else {
			tiles.at(randomTile)->setIsMine(true);
			placed++; 
		}
	}

	// Fjern window reskalering
	resizable(nullptr);
	size_range(x_max(), y_max(), x_max(), y_max());
}

vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}
	return points;
}

void MinesweeperWindow::openTile(Point xy) {
	if (at(xy)->getIsMine()) {
		at(xy)->open();
		isLost();
	}
	else {
		vector<Point> adjacent = adjacentPoints(xy);
		int adjacentMines = countMines(adjacent);
		if (adjacentMines > 0) {
			at(xy)->open();
			openedTiles++;
			at(xy)->setAdjMines(adjacentMines);
		}
		else {
			at(xy)->open();
			openedTiles++;
			for(int x{0}; x < adjacent.size(); x++) {
				if (at(adjacent[x])->getState() == Cell::open) {
				}
				else {
					openTile(adjacent[x]);
				}
			}
		}
		if (openedTiles == mineFreeTiles) {
			isWon();
		}
	}

}

void MinesweeperWindow::flagTile(Point xy) {
	// 2d)
	if (at(xy)->getState() == Cell::open) {
		return;
	}
	at(xy)->flag();
}

//Kaller openTile ved venstreklikk og flagTile ved høyreklikk/trykke med to fingre på mac
void MinesweeperWindow::click()
{
	Point xy{Fl::event_x(), Fl::event_y()};

	MouseButton mb = static_cast<MouseButton>(Fl::event_button());

	if (!inRange(xy)) {
		return;
	}

	switch (mb) {
	case MouseButton::left:
		openTile(xy);
		break;
	case MouseButton::right:
		flagTile(xy);
		break;
	}
}

int MinesweeperWindow::countMines(vector<Point> coords) const {
	int total{0};
	for (int x{0}; x < coords.size(); x++) {
		if (at(coords[x])->getIsMine()) {
			total++;
		}
	}
	return total;
}


void MinesweeperWindow::isLost() {
	add(lost);
	add(quitBtn);
	add(restartBtn);
	quitBtn.callback(cb_quit, this);
	restartBtn.callback(cb_restart, this);
}

void MinesweeperWindow::isWon() {
	add(won);
	add(quitBtn);
	add(restartBtn);
	quitBtn.callback(cb_quit, this);
	restartBtn.callback(cb_restart, this);
}

void MinesweeperWindow::cb_quit(Fl_Widget*, void* pw) {
	static_cast<MinesweeperWindow*>(pw)->hide();
}

void MinesweeperWindow::cb_restart(Fl_Widget*, void* pw) {
	static_cast<MinesweeperWindow*>(pw)->hide();
	Fl::background(200, 200, 200);
	int width = static_cast<MinesweeperWindow*>(pw)->width;
	int height = static_cast<MinesweeperWindow*>(pw)->height;
	int mines = static_cast<MinesweeperWindow*>(pw)->mines;
	Point startPoint{200, 300};
	MinesweeperWindow mw{startPoint.x, startPoint.y, width, height, mines, "Minesweeper" };
	gui_main();
}