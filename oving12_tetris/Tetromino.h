#pragma once
#include "Point.h"
#include "Color.h"
#include <vector>
#include <map>
#include "std_lib_facilities.h"

enum class TetrominoType{J, L, T, S, Z, O, I, NONE};

const std::map<TetrominoType, std::vector<std::vector<int>>> initialMatrixMap {
    {
    TetrominoType::J,
        {
        {0, 0, 0},
        {1, 1, 1},
        {0, 0, 1}
        }
    },
    {
    TetrominoType::L,
        {
        {0, 0, 0},
        {1, 1, 1},
        {1, 0, 0}    
        }
    },
    {
    TetrominoType::T,
        {
        {0, 0, 0},
        {1, 1, 1},
        {0, 1, 0}    
        }
    },
    {
    TetrominoType::S,
        {
        {0, 0, 0},
        {0, 1, 1},
        {1, 1, 0}    
        }
    },
    {
    TetrominoType::Z,
        {
        {0, 0, 0},
        {1, 1, 0},
        {0, 1, 1}    
        }
    },
    {
    TetrominoType::O,
        {
        {1, 1},
        {1, 1}  
        }
    },
    {
    TetrominoType::I,
        {
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}    
        }
    }
};

TDT4102::Color tetrominoToColor(TetrominoType type);

class Tetromino {
public:
    static constexpr int blockSize {30};

    Tetromino();
    Tetromino(TDT4102::Point startingPoint, TetrominoType tetType);
    
    void rotateClockwise();
    void rotateCounterClockwise();

    void moveDown();
    void moveLeft();
    void moveRight();

    bool blockExist(int row, int col);
    TetrominoType getBlock(int row, int col);
    int getMatrixSize(){return matrixSize;}
    TDT4102::Point getPosition(){return topLeftCorner;}
    TDT4102::Color getColor(){return color;}

   
private: 
    int matrixSize;
    TDT4102::Point topLeftCorner;
    std::vector<std::vector<TetrominoType>> blockMatrix;
    TDT4102::Color color;
};  