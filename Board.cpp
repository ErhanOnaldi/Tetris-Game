#include "Board.h"
#include <iostream>

Board::Board() {
    grid.fill({ {0} });
}

bool Board::placePiece(const Piece& piece, int x, int y) {
    if (checkCollision(piece, x, y)) {
        return false;
    }

    auto matrix = piece.getMatrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] != 0) {
                grid[y + i][x + j] = matrix[i][j];
            }
        }
    }
    return true;
}

void Board::updateBoard() {
    previousGrid = grid;
}



int Board::clearLines() {
    int clearedLineCount = 0;
    for (int y = 0; y < 20; ++y) {
        bool lineComplete = true;
        for (int x = 0; x < 10; ++x) {
            if (grid[y][x] == 0) {
                lineComplete = false;
                break;
            }
        }
        if (lineComplete) {
            for (int yy = y; yy > 0; --yy) {
                for (int x = 0; x < 10; ++x) {
                    grid[yy][x] = grid[yy - 1][x];
                }
            }
            grid[0].fill(0);
            y--;
            clearedLineCount++;
        }
    }
    return clearedLineCount;
}

void Board::placeTemporaryPiece(const Piece& piece, int x, int y) {
    auto matrix = piece.getMatrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] != 0 && y + i < 20 && x + j < 10) {
                grid[y + i][x + j] = matrix[i][j];
            }
        }
    }
}

void Board::removeTemporaryPiece(const Piece& piece, int x, int y) {
    auto matrix = piece.getMatrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] != 0 && y + i < 20 && x + j < 10) {
                grid[y + i][x + j] = 0;
            }
        }
    }
}

void Board::shrinkBoard() {
    
    width = std::max(4, width - 1); 
    height = std::max(4, height - 1); 

    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 10; ++x) {
            if (x >= width || y >= height) {
                grid[y][x] = 0;
            }
        }
    }
}


void Board::printBoard() const {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell ? "X" : ".");
        }
        std::cout << "\n";
    }
}


bool Board::checkCollision(const Piece& piece, int x, int y) const {
    auto matrix = piece.getMatrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix[i][j] != 0) {
                if (x + j < 0 || x + j >= 10 || y + i >= 20 || grid[y + i][x + j] != 0) {
                    return true;
                }
            }
        }
    }
    return false;
}

