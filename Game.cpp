#include "Game.h"
#include <iostream>
#include <conio.h> 
#include <thread>

Game::Game() : currentPiece(PieceType::T), nextPiece(PieceType::I), isGameOver(false), currentX(5), currentY(0), comboCount(0), score(0){
    lastUpdate = std::chrono::steady_clock::now();
}

void Game::run() {
    while (!isGameOver) {
        auto currentTime = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = currentTime - lastUpdate;
        if (elapsed.count() > 0.5) {
            update();
            lastUpdate = currentTime;
        }
        handleInput();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Game::update() {
    currentY++;
    if (board.checkCollision(currentPiece, currentX, currentY)) {
        currentY--;
        board.placePiece(currentPiece, currentX, currentY);

        score += 10;

        currentPiece = nextPiece; 
        nextPiece = Piece(static_cast<PieceType>(rand() % 7)); 
        currentX = 5;
        currentY = 0;

        
        int clearedLines = board.clearLines();
        if (clearedLines > 0) {
            comboCount++;
            if (comboCount >= 2) { 
                board.shrinkBoard(); 
                comboCount = 0; 
            }
            score += score + 100;
        }
        else {
            comboCount = 0; 
        }

        if (board.checkCollision(currentPiece, currentX, currentY)) {
            isGameOver = true;
        }
    }
}



void Game::render() {
    system("cls"); 

    board.placeTemporaryPiece(currentPiece, currentX, currentY); 
    board.printBoard(); 
    board.removeTemporaryPiece(currentPiece, currentX, currentY); 

    
    std::cout << "Current Piece (Type " << static_cast<int>(currentPiece.getType()) << "):" << std::endl;
    printPiece(currentPiece);
    std::cout << "Next Piece (Type " << static_cast<int>(nextPiece.getType()) << "):" << std::endl;
    printPiece(nextPiece);

    
    std::cout << "Position: (" << currentX << ", " << currentY << ")" << std::endl;
    std::cout << "Score: " << score << std::endl;
    std::cout << "Combo Count: " << comboCount << std::endl; 
    std::cout << (isGameOver ? "Game Over!" : "Game Running...") << std::endl;
    board.updateBoard();
}

void Game::printPiece(const Piece& piece) {
    auto matrix = piece.getMatrix();
    for (const auto& row : matrix) {
        for (int cell : row) {
            std::cout << (cell ? 'X' : ' ');
        }
        std::cout << std::endl;
    }
}



void Game::handleInput() {
    if (_kbhit()) {
        char ch = _getch();
        switch (ch) {
        case 'a':  
            if (!board.checkCollision(currentPiece, currentX - 1, currentY)) {
                currentX--;
            }
            break;
        case 'd':  
            if (!board.checkCollision(currentPiece, currentX + 1, currentY)) {
                currentX++;
            }
            break;
        case 'w':  
        {
            Piece rotatedPiece = currentPiece;
            rotatedPiece.rotate();
            if (!board.checkCollision(rotatedPiece, currentX, currentY)) {
                currentPiece.rotate();
            }
        }
        break;
        case 's':  
            while (!board.checkCollision(currentPiece, currentX, currentY + 1)) {
                currentY++;
            }
            break;
            
        }
    }
}

