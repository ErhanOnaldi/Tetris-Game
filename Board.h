#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include <array>
#include <iostream>

class Board {
public:
    Board();
    bool placePiece(const Piece& piece, int x, int y);
    int clearLines();
    void printBoard() const;
    void updateBoard(); 
    bool checkCollision(const Piece& piece, int x, int y) const;
    void placeTemporaryPiece(const Piece& piece, int x, int y);
    void removeTemporaryPiece(const Piece& piece, int x, int y);
    void shrinkBoard();

private:
    std::array<std::array<int, 10>, 20> grid;
    std::array<std::array<int, 10>, 20> previousGrid; 
    int width;
    int height;
};

#endif 

