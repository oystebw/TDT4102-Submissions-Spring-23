#include "Tetromino.h"
#include <iostream>

TDT4102::Color tetrominoToColor(TetrominoType type){
    switch (type){
    case TetrominoType::J :
        return TDT4102::Color::blue; 
    case TetrominoType::I :
        return TDT4102::Color::aqua;
    case TetrominoType::Z :
        return TDT4102::Color::red;
    case TetrominoType::L :
        return TDT4102::Color::orange;
    case TetrominoType::S :
        return TDT4102::Color::lime;
    case TetrominoType::O :
        return TDT4102::Color::yellow;
    default:
        return TDT4102::Color::black;
    }
}

Tetromino::Tetromino(): topLeftCorner{TDT4102::Point({0,0})}, matrixSize{0}{}

Tetromino::Tetromino(TDT4102::Point startingPoint, TetrominoType tetType) : 
topLeftCorner{startingPoint}{
    matrixSize = initialMatrixMap.at(tetType).size();
    color = tetrominoToColor(tetType);

    for(int row{0}; row < matrixSize; ++row){
        std::vector<TetrominoType> temp;
        for(int col{0}; col < matrixSize; ++col){
            if(initialMatrixMap.at(tetType)[row][col]){
                temp.push_back(tetType);
            }
            else{
                temp.push_back(TetrominoType::NONE);
            }
        }
        blockMatrix.push_back(temp);
    }
}

void Tetromino::rotateCounterClockwise() {
    //Første rotasjon, med hensyn på diagonalen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < row; column++){
            std::swap(blockMatrix[row][column], blockMatrix[column][row]);
        }
    }

    //Andre rotasjon, med hensyn på den midtre raden
    for(int row = 0; row < matrixSize/2; row++){
        for(int column = 0; column < matrixSize; column++){
            std::swap(blockMatrix[row][column], blockMatrix[matrixSize-row-1][column]);
            
        }
    }
}

void Tetromino::rotateClockwise() {
    //Første rotasjon, med hensyn på diagonalen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < row; column++){
            std::swap(blockMatrix[row][column], blockMatrix[column][row]);
        }
    }
     
    //Andre rotasjon, med hensyn på den midtre kolonnen
    for(int row = 0; row < matrixSize; row++){
        for(int column = 0; column < matrixSize/2; column++){
            std::swap(blockMatrix[row][column], blockMatrix[row][matrixSize-column-1]);
        }
    }
}

void Tetromino::moveDown(){
    topLeftCorner.y++;
}

void Tetromino::moveLeft(){
    topLeftCorner.x--;
}

void Tetromino::moveRight(){
    topLeftCorner.x++;
}

bool Tetromino::blockExist(int row, int col){
    assert(row < matrixSize && col < matrixSize && row > -1 && col > -1);
    if(blockMatrix[row][col] == TetrominoType::NONE){
        return false;
    }
    return true;
}

TetrominoType Tetromino::getBlock(int row, int col){
    assert(row < matrixSize && col < matrixSize && row > -1 && col > -1);
    return blockMatrix[row][col];
}
