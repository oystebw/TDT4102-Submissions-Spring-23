#pragma once
#include "AnimationWindow.h"
#include "Tetromino.h"
#include "widgets/TextInput.h"
#include "widgets/Button.h"
#include <vector>
#include "Tetromino.h"

static volatile int g_Color = 1;

class TetrisWindow : public TDT4102::AnimationWindow {

public:

    TetrisWindow(TDT4102::Point topLeft, TDT4102::Point spawnPoint, int blockSize, int width, int height, std::string title);
    void run();
    
private:

    const int blockSize;
    const int width;
    const int height;

    Tetromino currentTetromino;
    std::vector<std::vector<TetrominoType>> gridMatrix;
    const TDT4102::Point spawnPoint;

    TDT4102::Color backgroundColor;

    void handleInput();
    void generateRandomTetromino();
    void drawCurrentTetromino();

    bool shouldStop();
    void fastenTetronimo();
    void drawGridMatrix();
    void drawLines();

    bool checkLeft();
    bool checkRight();

    void checkFullRows();
    void removeFullRow(int row);

    bool checkLost();

    TDT4102::Color getDisco();
};