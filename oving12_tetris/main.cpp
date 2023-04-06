#include "TetrisWindow.h"

constexpr TDT4102::Point topLeft({50, 50});
constexpr int blockSize{30};
constexpr int width{15};
constexpr int height{25};
constexpr TDT4102::Point spawnPoint({(width / 2) - 1, 0});
std::string title{"Tetris"};

int main(){
	TetrisWindow win(topLeft, spawnPoint, blockSize, width, height, title);
	win.wait_for_close();
}
