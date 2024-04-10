#pragma once
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Piece.h"
#include <chrono>

class Game {
public:
    Game();
    void run();
    void update();
    void render();
    void handleInput();
    void printPiece(const Piece& piece);

private:
    Board board;
    Piece currentPiece;
    Piece nextPiece;
    bool isGameOver;
    int currentX, currentY;
    std::chrono::time_point<std::chrono::steady_clock> lastUpdate;
    int comboCount;
    int score;
};

#endif 

