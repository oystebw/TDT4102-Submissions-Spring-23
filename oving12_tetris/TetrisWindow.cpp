#include "TetrisWindow.h"
#include <iostream>

TetrisWindow::TetrisWindow(TDT4102::Point topLeft, TDT4102::Point spawnPoint, int blockSize, int width, int height, std::string title): 
    AnimationWindow{topLeft.x, topLeft.y, blockSize * width, blockSize * height, title},
    blockSize{blockSize}, width{width}, height{height}, spawnPoint{spawnPoint}{
        
        //initialize 2x2 grid to correct size
        gridMatrix.resize(height);
        for(int row{0}; row < height; ++row){
            gridMatrix[row].resize(width);
            for(int col{0}; col < width; ++col){
                gridMatrix[row][col] = TetrominoType::NONE;
            }
        }
        
        generateRandomTetromino();
        run();
    }

void TetrisWindow::run() {
    unsigned int framesSinceLastTetronimoMove = 0;
    const unsigned int framesPerTetronimoMove = 20;

    while(!should_close()) { 
        framesSinceLastTetronimoMove++;
        if(framesSinceLastTetronimoMove >= framesPerTetronimoMove) {
            g_Color++;
            framesSinceLastTetronimoMove = 0;
            if(shouldStop()){
                fastenTetronimo();
                if(checkLost()){
                    close();
                }
                generateRandomTetromino();
                drawCurrentTetromino();
                drawGridMatrix();
                next_frame();
            }
            currentTetromino.moveDown();
            checkFullRows();
        }
        handleInput();
        checkFullRows();
        drawGridMatrix();
        drawCurrentTetromino();
        drawLines();
        
        next_frame();
    }
}


void TetrisWindow::handleInput() {

    static bool lastZKeyState = false;
    static bool lastUpKeyState = false;
    static bool lastLeftKeyState = false;
    static bool lastRightKeyState = false;
    static bool lastDownKeyState = false;
    static bool lastXKeyState = false;

    bool currentZKeyState = is_key_down(KeyboardKey::Z);
    bool currentUpKeyState = is_key_down(KeyboardKey::UP);
    bool currentLeftKeyState = is_key_down(KeyboardKey::LEFT);
    bool currentRightKeyState = is_key_down(KeyboardKey::RIGHT);
    bool currentDownKeyState = is_key_down(KeyboardKey::DOWN);
    bool currentXKeyState = is_key_down(KeyboardKey::X);

    
    if(currentZKeyState && !lastZKeyState) {
        currentTetromino.rotateClockwise();
    }

    if(currentUpKeyState && !lastUpKeyState) {
        currentTetromino.rotateCounterClockwise();
    }
    if(currentLeftKeyState && !lastLeftKeyState){
        if(checkLeft()){
            currentTetromino.moveLeft();
        }
    }
    if(currentRightKeyState && !lastRightKeyState){
        if(checkRight()){
            currentTetromino.moveRight();
        }
    }
    if(currentDownKeyState && !lastDownKeyState){
        if(shouldStop()){
            fastenTetronimo();
            generateRandomTetromino();
        }
        currentTetromino.moveDown();
    }
    if(currentXKeyState && !lastXKeyState){
        while(!shouldStop()){
            currentTetromino.moveDown();
        }
        fastenTetronimo();
        generateRandomTetromino();
    }

    lastZKeyState = currentZKeyState;
    lastUpKeyState = currentUpKeyState;
    lastLeftKeyState = currentLeftKeyState;
    lastRightKeyState = currentRightKeyState;
    lastDownKeyState = currentDownKeyState;
    lastXKeyState = currentXKeyState;
}

void TetrisWindow::generateRandomTetromino(){
    int random = randint(6);
    currentTetromino = Tetromino(spawnPoint, static_cast<TetrominoType>(random));
}

void TetrisWindow::drawCurrentTetromino(){
    const int size = currentTetromino.getMatrixSize();
    TDT4102::Point topLeft = currentTetromino.getPosition();

    for(int row{0}; row < size; ++row){
        for(int col{0}; col < size; ++col){
            if(currentTetromino.blockExist(row, col)){
                draw_rectangle({(topLeft.x + col) * blockSize, (topLeft.y + row) * blockSize},
                blockSize, blockSize, currentTetromino.getColor(), TDT4102::Color::black);
            }
        }
    }
}

bool TetrisWindow::shouldStop(){
    int size = currentTetromino.getMatrixSize();
    TDT4102::Point topLeft = currentTetromino.getPosition();

    for(int row{0}; row < size; ++row){
        for(int col{0}; col < size; ++col){
            if(currentTetromino.blockExist(row, col)){
                if(topLeft.y + row + 1 == height){
                return true;
                }
                if(gridMatrix[topLeft.y + row + 1][topLeft.x + col] != TetrominoType::NONE){
                return true;
                }
            }
        }
    }
    return false;
}

void TetrisWindow::fastenTetronimo(){
    int size = currentTetromino.getMatrixSize();
    TDT4102::Point topLeft = currentTetromino.getPosition();

    for(int row{0}; row < size; ++row){
        for(int col{0}; col < size; ++col){
            if(currentTetromino.blockExist(row, col)){
                gridMatrix[topLeft.y + row][topLeft.x + col] = currentTetromino.getBlock(row, col);
            }
        }
    }
}

void TetrisWindow::drawGridMatrix(){
    for(int row{0}; row < height; ++row){
        for(int col{0}; col < width; ++col){
            if(gridMatrix[row][col] != TetrominoType::NONE){
                draw_rectangle({col * blockSize, row * blockSize}, blockSize, blockSize,
                tetrominoToColor(gridMatrix[row][col]), TDT4102::Color::black);
            }
            else{
                draw_rectangle({col * blockSize, row * blockSize}, blockSize, blockSize, getDisco());
            }
        }
    }
}

bool TetrisWindow::checkLeft(){
    int size = currentTetromino.getMatrixSize();
    TDT4102::Point topLeft = currentTetromino.getPosition();

    for(int row{0}; row < size; ++row){
        for(int col{0}; col < size; ++col){
            if(currentTetromino.blockExist(row, col)){
                if(topLeft.x + col == 0){
                    return false;
                }
                if(gridMatrix[topLeft.y + row][topLeft.x + col - 1] != TetrominoType::NONE){
                    return false;
                }
            }
        }
    }
    return true;
}

bool TetrisWindow::checkRight(){
    int size = currentTetromino.getMatrixSize();
    TDT4102::Point topLeft = currentTetromino.getPosition();

    for(int row{0}; row < size; ++row){
        for(int col{0}; col < size; ++col){
            if(currentTetromino.blockExist(row, col)){
                if(topLeft.x + col == width - 1){
                    return false;
                }
                if(gridMatrix[topLeft.y + row][topLeft.x + col + 1] != TetrominoType::NONE){
                    return false;
                }
            }
        }
    }
    return true;
}

void TetrisWindow::checkFullRows(){
    for(int row{0}; row < height; ++row){
        for(int col{0}; col < width; ++col){
            if(gridMatrix[row][col] == TetrominoType::NONE){
                goto nextRow;
            }
        }
        removeFullRow(row);
        nextRow:;
    }
}

void TetrisWindow::removeFullRow(int row){
    for(int col{0}; col < width; ++col){
        gridMatrix[row][col] = TetrominoType::NONE;
    }
    for(; row > 0; row--){
        std::swap(gridMatrix[row], gridMatrix[row - 1]);
    }
}

bool TetrisWindow::checkLost(){
    for(int col{0}; col < width; ++col){
        if(gridMatrix[1][col] != TetrominoType::NONE){
            return true;
        }
    }
    return false;
}

void TetrisWindow::drawLines(){
    TDT4102::Point topLeft = currentTetromino.getPosition();
    int size = currentTetromino.getMatrixSize();

    for(int col{0}; col < size; ++col){
        for(int row{0}; row < size; ++row){
            if(currentTetromino.blockExist(row, col)){
                draw_line({(topLeft.x + col) * blockSize, (topLeft.y + row + 1) * blockSize}, {(topLeft.x + col) * blockSize, height * blockSize});
                goto next;
            }
        }
    }
    next:;
    for(int col{size - 1}; col > -1; col--){
        for(int row{0}; row < size; ++row){
            if(currentTetromino.blockExist(row, col)){
                draw_line({(topLeft.x + col + 1) * blockSize, (topLeft.y + row + 1) * blockSize}, {(topLeft.x + col + 1) * blockSize, height * blockSize});
                return;
            }
        }
    }
}

TDT4102::Color TetrisWindow::getDisco(){
    switch (g_Color % 7)
    {
        case 0:
        return TDT4102::Color::fuchsia;
        case 1:
        return TDT4102::Color::spring_green;
        case 2:
        return TDT4102::Color::slate_blue;
        case 3:
        return TDT4102::Color::peachpuff;
        case 4:
        return TDT4102::Color::olivedrab;
        case 5:
        return TDT4102::Color::light_salmon;
        case 6:
        return TDT4102::Color::lawn_green;

        default:
        return TDT4102::Color::black;
    }
}